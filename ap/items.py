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

  match item["type"]:
    case "Medal":
      if world.options.required_medals > 0:
        classification = ItemClassification.progression_skip_balancing
      if not world.options.shuffle_medals:
        item_id = None
    case "Path":
      if not world.options.shuffle_paths:
        item_id = None
    case "Victory":
      item_id = None
  return StarFox64Item(item_name, classification, item_id, world.player)
