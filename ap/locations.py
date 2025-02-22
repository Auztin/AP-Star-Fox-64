from BaseClasses import Location
from . import data
from .ids import location_name_to_id

name_to_id = {}

for name, value in location_name_to_id.items():
  if value > 0:
    name_to_id[name] = value

class StarFox64Location(Location):
  pass
