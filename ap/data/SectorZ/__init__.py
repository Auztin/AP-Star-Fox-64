regions = {
  "Sector Z": {
    "locations": {
      "Sector Z - Mission Complete": {
        "item": "SectorZBluePath",
        "logic": "true",
      },
      "Sector Z - Mission Accomplished": {
        "item": "SectorZRedPath",
        "logic": "true",
      },
      "Sector Z - Medal": {
        "item": "Medal",
        "logic": "true",
      },
    },
    "exits": {
      "Bolse": {
        "type": "Level",
        "logic": "SectorZBluePath",
      },
      "Area 6": {
        "type": "Level",
        "logic": "SectorZRedPath",
      },
    },
  },
}
