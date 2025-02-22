import sys, typing, json, re, Options
sys.path.insert(0, "../ap")
from options import StarFox64OptionsList
from version import version
import data

options = {}
option_choices = {}
item_name_to_id = {}
item_alias_to_name = {}
item_alias_to_id = {"None":-1}
location_name_to_id = {"None":-1, "Goal Completed":0}

for idx, (name, cls) in enumerate(typing.get_type_hints(StarFox64OptionsList).items()):
  options[name] = idx
  if issubclass(cls, Options.Choice):
    option_choices[name] = {}
    for var, value in vars(cls).items():
      if var in ["__module__", "__doc__", "display_name", "default"]: continue
      option_choices[name][re.sub("^option_", "", var)] = value

last_id = 0
for item_name, item in data.items.items():
  last_id += 1
  item_name_to_id[item_name] = last_id
  item_alias_to_name[item["alias"]] = item_name
  item_alias_to_id[item["alias"]] = last_id

last_id = 0
for region_name, region in data.regions.items():
  for key, value in region.items():
    match key:
      case "locations":
        for location_name, location in value.items():
          last_id += 1
          location_name_to_id[location_name] = last_id

command_list = [
  "NONE",
  "HANDSHAKE",
  "PING",
  "PONG",
  "SEED",
  "OPTIONS",
  "LOCATIONS",
  "ITEMS",
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
  f.write(f"item_alias_to_name = {json.dumps(item_alias_to_name, indent=2)}\n\n")
  f.write(f"location_name_to_id = {json.dumps(location_name_to_id, indent=2)}\n\n")
  f.write(f"class AP_CMD:\n")
  for cmd, value in commands.items():
    f.write(f"  {cmd} = {value}\n")
  f.write("\n")
  f.write(f"class AP_STATE:\n")
  for state, value in states.items():
    f.write(f"  {state} = {value}\n")

def name_to_c(s):
  return re.sub("[^a-zA-Z0-9_]+", "_", s).upper()

def names_to_c(d):
  last = 0
  for key, value in d.items():
    last = value
    yield name_to_c(key), value
  yield "MAX", value+1

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
  for key, value in names_to_c(item_alias_to_id):
    f.write(f"  AP_ITEM_{key} = {value},\n")
  f.write("} ap_item_t;\n")

with open("../n64/src/ap/locations.h", "w") as f:
  c_header(f)
  f.write("typedef enum {\n")
  for key, value in names_to_c(location_name_to_id):
    f.write(f"  AP_LOCATION_{key} = {value},\n")
  f.write("} ap_location_t;\n")
  f.write(f"#define AP_LOCATION_MAX_BYTES ((AP_LOCATION_MAX-1)-(AP_LOCATION_MAX-1)%8+8)\n")

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
