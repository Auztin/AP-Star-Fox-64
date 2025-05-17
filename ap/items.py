from BaseClasses import Item, ItemClassification
from . import data
from .ids import item_name_to_id, group_items

name_to_id = {}
groups = {}

for name, value in item_name_to_id.items():
  if value > 0:
    name_to_id[name] = value

for group_name, items in group_items.items():
  groups[group_name] = set(items)

class StarFox64Item(Item):
  pass

def pick_name(world, item_name, group):
  match group:
    case "Mission Finished":
      item_name = item_name[world.options.level_access]
  return item_name

def is_event(world, item_type):
  match item_type:
    case "Medal":
      return not world.options.shuffle_medals
    case "Levels":
      return world.options.level_access != "shuffle_levels"
    case "Paths":
      return world.options.level_access != "shuffle_paths"
    case "Checkpoints":
      return not world.options.shuffle_checkpoints
    case "Events":
      return True
  return False

def create_item(world, item_name):
  item = data.items[item_name]
  item_id = name_to_id[item_name]
  item_type = item.get("type", item_name)
  classification = ItemClassification.filler

  match item["class"]:
    case "progression":
      classification = ItemClassification.progression
    case "useful":
      classification = ItemClassification.useful
    case "trap":
      classification = ItemClassification.trap
    case "progression_skip_balancing":
      classification = ItemClassification.progression_skip_balancing

  match item_type:
    case "Medal":
      if world.options.required_medals > 0:
        classification = ItemClassification.progression_skip_balancing

  if is_event(world, item_type): item_id = None
  return StarFox64Item(item_name, classification, item_id, world.player)
