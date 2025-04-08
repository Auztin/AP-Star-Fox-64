regions = {
  "Sector Z": {
    "locations": {
      "Sector Z - Mission Complete": {
        "item": "Sector Z - Blue Path",
        "logic": "true",
      },
      "Sector Z - Mission Accomplished": {
        "item": "Sector Z - Red Path",
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
