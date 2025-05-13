import sys, typing, json, re, numbers, Options
sys.path.insert(0, "../ap")
from options import StarFox64OptionsList
from version import version
import data

options = {}
option_choices = {}
item_name_to_id = {"None":-1}
item_types = {}
item_type_set = set()
location_name_to_id = {"None":-1, "Goal Completed":0}
location_items = {}
location_groups = {}
location_group_set = set()

with open("../template.yaml", "w") as file:
  file.write("name: Player{NUMBER}\n")
  file.write("game: Star Fox 64\n")
  file.write("Star Fox 64:\n\n")
  for idx, (name, cls) in enumerate(typing.get_type_hints(StarFox64OptionsList).items()):
    for line in cls.__doc__.strip().split("\n"):
      file.write(f"  # {line.strip()}\n")
    cls_vars = vars(cls)
    default = 0
    if "default" in cls_vars: default = cls.default
    options[name] = idx
    if issubclass(cls, Options.Toggle):
      default = "false"
    if issubclass(cls, Options.DefaultOnToggle):
      default = "true"
    if issubclass(cls, Options.Choice):
      file.write(f"  # You can use the following numbers or names:\n")
      option_choices[name] = {}
      option_idx = 0
      for var, value in vars(cls).items():
        if var in ["__module__", "__doc__", "display_name", "default"]: continue
        option_name = re.sub("^option_", "", var)
        option_choices[name][option_name] = value
        if default == option_idx: default = option_name
        file.write(f"  # {option_idx} or {option_name}\n")
        option_idx += 1

    file.write(f"  {name}: {default}\n\n")

last_id = 0
for item_name, item in data.items.items():
  last_id += 1
  item_name_to_id[item_name] = last_id
  if "type" in item:
    item_types[item_name] = item["type"]
    item_type_set.add(item["type"])

last_id = 0
for region_name, region in data.regions.items():
  for key, value in region.items():
    match key:
      case "locations":
        for location_name, location in value.items():
          last_id += 1
          location_name_to_id[location_name] = last_id
          location_items[location_name] = location["item"]
          if "group" in location:
            location_groups[location_name] = location["group"]
            location_group_set.add(location["group"])

command_list = [
  "NONE",
  "HANDSHAKE",
  "PING",
  "PONG",
  "SEED",
  "OPTIONS",
  "READY",
  "LOCATIONS",
  "ITEMS",
  "DEATHLINK",
  "RINGLINK",
]
commands = {cmd: value for value, cmd in enumerate(command_list)}

states = {
  "DISCONNECTED": 0,
  "CONNECTING":   1,
  "CONNECTED":    2,
  "PINGED":       4,
}

with open("../ap/ids.py", "w") as f:
  f.write("# Automatically generated using enum_gen.py\n\n")
  f.write(f"option_name_to_id = {json.dumps(options, indent=2)}\n\n")
  f.write(f"item_name_to_id = {json.dumps(item_name_to_id, indent=2)}\n\n")
  f.write(f"location_name_to_id = {json.dumps(location_name_to_id, indent=2)}\n\n")
  f.write(f"class AP_CMD:\n")
  for cmd, value in commands.items():
    f.write(f"  {cmd} = {value}\n")
  f.write("\n")
  f.write(f"class AP_STATE:\n")
  for state, value in states.items():
    f.write(f"  {state} = {value}\n")

def name_to_c(s):
  s = re.sub("['\"]+", "", s)
  return re.sub("[^a-zA-Z0-9_]+", "_", s).upper()

def names_to_c(d):
  last = 0
  for key, value in d.items():
    last = value
    yield name_to_c(key), value
  if isinstance(value, numbers.Number): yield "MAX", value+1

def c_header(f):
  f.write("#pragma once\n\n")
  f.write("// Automatically generated using enum_gen.py\n\n")

with open("../n64/src/ap/version.h", "w") as f:
  c_header(f)
  f.write(
f"""\
#include "n64/types.h"

typedef union {{
  struct {{
    u16 major;
    u8  minor;
    u8  build;
  }};
  u32 as_int;
}} ap_version_t;
static const ap_version_t AP_VERSION = {{.major={version.major}, .minor={version.minor}, .build={version.build}}};
"""
  )

with open("../n64/src/ap/options.h", "w") as f:
  c_header(f)
  f.write("typedef enum {\n")
  for key, value in names_to_c(options):
    f.write(f"  AP_OPTION_{key} = {value},\n")
  f.write("} ap_option_t;\n")
  for choice, names in option_choices.items():
    f.write("\ntypedef enum {\n")
    for key, value in names_to_c(names):
      f.write(f"  AP_OPTION_{name_to_c(choice)}_{key} = {value},\n")
    f.write(f"}} ap_option_{choice}_t;\n")

with open("../n64/src/ap/items.h", "w") as f:
  c_header(f)
  f.write("typedef enum {\n")
  for key, value in names_to_c(item_name_to_id):
    f.write(f"  AP_ITEM_{key} = {value},\n")
  f.write("} ap_item_t;\n\n")
  f.write("typedef enum {\n")
  f.write(f"  AP_ITEM_TYPE_NONE = -1,\n")
  for i, group in enumerate(item_type_set):
    f.write(f"  AP_ITEM_TYPE_{name_to_c(group)} = {i},\n")
  f.write("} ap_item_type_t;\n\n")
  f.write("ap_item_type_t ap_item_type(ap_item_t item);\n")

with open("../n64/src/ap/items.c", "w") as f:
  f.write("// Automatically generated using enum_gen.py\n\n")
  f.write("#include \"ap/items.h\"\n\n")
  f.write("ap_item_type_t ap_item_type(ap_item_t item) {\n")
  f.write("  switch (item) {\n")
  for key, value in names_to_c(item_types):
    f.write(f"    case AP_ITEM_{key}: return AP_ITEM_TYPE_{name_to_c(value)};\n")
  f.write(f"    default: return AP_ITEM_TYPE_NONE;\n")
  f.write("  }\n")
  f.write("}\n")

with open("../n64/src/ap/locations.h", "w") as f:
  c_header(f)
  f.write("#include \"ap/items.h\"\n\n")
  f.write("typedef enum {\n")
  for key, value in names_to_c(location_name_to_id):
    f.write(f"  AP_LOCATION_{key} = {value},\n")
  f.write("} ap_location_t;\n")
  f.write(f"#define AP_LOCATION_MAX_BYTES ((AP_LOCATION_MAX-1)-(AP_LOCATION_MAX-1)%8+8)\n\n")
  f.write("typedef enum {\n")
  f.write(f"  AP_LOCATION_GROUP_NONE = -1,\n")
  for i, group in enumerate(location_group_set):
    f.write(f"  AP_LOCATION_GROUP_{name_to_c(group)} = {i},\n")
  f.write("} ap_location_group_t;\n\n")
  f.write("ap_item_t ap_location_item(ap_location_t location);\n")
  f.write("ap_location_group_t ap_location_group(ap_location_t location);\n")

with open("../n64/src/ap/locations.c", "w") as f:
  f.write("// Automatically generated using enum_gen.py\n\n")
  f.write("#include \"ap/locations.h\"\n\n")
  f.write("ap_item_t ap_location_item(ap_location_t location) {\n")
  f.write("  switch (location) {\n")
  for key, value in names_to_c(location_items):
    f.write(f"    case AP_LOCATION_{key}: return AP_ITEM_{name_to_c(value)};\n")
  f.write(f"    default: return AP_ITEM_NONE;\n")
  f.write("  }\n")
  f.write("}\n\n")
  f.write("ap_location_group_t ap_location_group(ap_location_t location) {\n")
  f.write("  switch (location) {\n")
  for key, value in names_to_c(location_groups):
    f.write(f"    case AP_LOCATION_{key}: return AP_LOCATION_GROUP_{name_to_c(value)};\n")
  f.write(f"    default: return AP_LOCATION_GROUP_NONE;\n")
  f.write("  }\n")
  f.write("}\n")

with open("../n64/src/ap/commands.h", "w") as f:
  c_header(f)
  f.write("typedef enum {\n")
  for key, value in names_to_c(commands):
    f.write(f"  AP_CMD_{key} = {value},\n")
  f.write("} ap_cmd_t;\n")

with open("../n64/src/ap/states.h", "w") as f:
  c_header(f)
  f.write("typedef enum {\n")
  for key, value in names_to_c(states):
    f.write(f"  AP_STATE_{key} = {value},\n")
  f.write("} ap_state_t;\n")
