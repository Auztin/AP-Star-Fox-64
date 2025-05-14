from BaseClasses import Item, ItemClassification
from . import data
from .ids import item_name_to_id

name_to_id = {}

for name, value in item_name_to_id.items():
  if value > 0:
    name_to_id[name] = value

class StarFox64Item(Item):
  pass

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
      if not world.options.shuffle_medals:
        item_id = None
    case "Level":
      if world.options.level_access != "shuffle_levels":
        item_id = None
    case "Path":
      if world.options.level_access != "shuffle_paths":
        item_id = None
    case "Checkpoint":
      if not world.options.shuffle_checkpoints:
        item_id = None
    case "Event":
      item_id = None
  return StarFox64Item(item_name, classification, item_id, world.player)
