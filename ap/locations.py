from BaseClasses import Location
from . import data
from .ids import location_name_to_id, group_locations

name_to_id = {}
groups = {}

for name, value in location_name_to_id.items():
  if value > 0:
    name_to_id[name] = value

for group_name, locations in group_locations.items():
  groups[group_name] = set(locations)

class StarFox64Location(Location):
  pass
