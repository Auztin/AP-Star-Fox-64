import ast, re, typing

from Options import Choice

from . import items

class StarFox64Rules(ast.NodeTransformer):

  def __init__(self, world):
    self.world = world
    self.player = ast.Constant(value=world.player)
    self.options = {}
    for option_name, option_class in typing.get_type_hints(type(world.options)).items():
      option = getattr(world.options, option_name)
      value = option.value
      if isinstance(option, Choice):
        value = option.current_key
      self.options[option_class.__name__] = value
    self.items = {}
    for item_name, item_id in items.name_to_id.items():
      self.items[re.sub("[^a-zA-Z0-9]+", "", item_name)] = item_name

  def parse(self, logic, file):
    self.file = file
    node = self.visit(ast.parse(f"lambda state: ({logic})", mode="eval"))
    node = ast.fix_missing_locations(node)
    return eval(compile(node, file, "eval"))

  def make_attr(self, value, attr):
    return ast.Attribute(
      value=ast.Name(id=value, ctx=ast.Load()),
      attr=attr,
      ctx=ast.Load()
    )

  def make_call(self, func, args):
    args.insert(1, self.player)
    return ast.Call(
      func=self.make_attr("state", func),
      args=args,
      keywords=[]
    )

  def get_item(self, alias):
    return ast.Constant(value=self.items[alias])

  def visit_Compare(self, node):
    self.generic_visit(node)
    if (isinstance(node.left, ast.Constant)):
      for child_node in node.comparators:
        if (not isinstance(child_node, ast.Constant)):
          return node
      return ast.Constant(value=eval(compile(ast.fix_missing_locations(ast.Expression(body=node)), "<string>", "eval")))
    return node

  def visit_Name(self, node):
    match node.id:
      case "true": return ast.Constant(value=True)
      case "false": return ast.Constant(value=False)
    if node.id in self.items: return self.make_call("has", [self.get_item(node.id)])
    if node.id in self.options: return ast.Constant(value=self.options[node.id])
    raise NameError(f"{self.file}: name '{node.id}' is not defined")

  def visit_Tuple(self, node):
    assert len(node.elts) == 2, f"{self.file}: Tuples must have exactly 2 elements."
    item, count = node.elts
    count = self.visit(count)
    assert isinstance(item, ast.Name), f"{self.file}: The first element of a Tuple must be an ast.Name."
    assert item.id in self.items, f"{self.file}: The first element of a Tuple must be a collectable."
    if isinstance(count, ast.Constant) and count.value == 0: return ast.Constant(value=True)
    return self.make_call("has", [self.get_item(item.id), count])

  def visit_BoolOp(self, node):
    self.generic_visit(node)
    opIsAnd = isinstance(node.op, ast.And)
    values = []
    grouped = {}
    for child_node in node.values:
      if isinstance(child_node, ast.Constant):
        if opIsAnd:
          if child_node.value: continue
          else: return child_node
        else:
          if child_node.value: return child_node
          else: continue
      elif (
        isinstance(child_node, ast.Call) and isinstance(child_node.func, ast.Attribute)
        and isinstance(child_node.func.value, ast.Name) and child_node.func.value.id == "state"
        and child_node.func.attr == "has" and len(child_node.args)
        and isinstance(child_node.args[0], ast.Constant)
      ):
        item = child_node.args[0].value
        if (item not in grouped): grouped[item] = 1
        if (len(child_node.args) == 3 and isinstance(child_node.args[2], ast.Constant)):
          count = child_node.args[2].value
          if (grouped[item] < count): grouped[item] = count
      else: values.append(child_node)

    if (len(grouped)):
      has_func = "has"
      grouped_keys = []
      grouped_values = []
      for item, count in grouped.items():
        if (count > 1):
          if (opIsAnd): has_func = "has_all_counts"
          else: has_func = "has_any_count"
        grouped_keys.append(ast.Constant(value=item))
        grouped_values.append(ast.Constant(value=count))
      if (has_func == "has"):
        if (len(grouped_keys) == 1):
          values.append(self.make_call("has", [grouped_keys[0]]))
        else:
          values.append(self.make_call("has_all" if opIsAnd else "has_any", [ast.Tuple(elts=grouped_keys, ctx=ast.Load())]))
      else:
        values.append(self.make_call(has_func, [ast.Dict(keys=grouped_keys, values=grouped_values)]))

    node.values = values
    match len(node.values):
      case 0:
        return ast.Constant(value=opIsAnd)
      case 1:
        return node.values[0]
    return node

  def visit_Call(self, node):
    if (isinstance(node.func, ast.Name)):
      match node.func.id:
        case "any_except":
          assert len(node.args >= 2), f"{self.file}: any_except requires at least 2 arguments."
          except_list = []
          for idx, arg in enumerate(node.args):
            arg = self.visit(arg)
            if (idx == 0):
              node = arg
              continue
            assert isinstance(arg, ast.Call), f"{self.file}: any_except invalid arg: {idx}"
            args = arg.args[0]
            elts = [args]
            if (isinstance(args, ast.Tuple)): elts = args.elts
            for elt in elts:
              assert isinstance(elt, ast.Constant), f"{self.file}: any_except invalid arg: {idx}"
              except_list.append(elt.value)
          assert isinstance(node, ast.Call) or isinstance(node.args[0], ast.Tuple), f"{self.file}: any_except requires arg 1 to be a list of items."
          node.args[0].elts = list(filter(lambda elt: elt.value not in except_list, node.args[0].elts))
          return node
        case "count":
          assert len(node.args) == 1, f"{self.file}: count requires exactly 1 argument."
          item = self.visit(node.args[0])
          assert isinstance(item, ast.Call), f"{self.file}: count invalid arg."
          node.func = self.make_attr("state", "count")
          node.args = [item.args[0], self.player]
          return node
        case "can_reach":
          node.args.insert(1, self.player)
    self.generic_visit(node)
    return node
