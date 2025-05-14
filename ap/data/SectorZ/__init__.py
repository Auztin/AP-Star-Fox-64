regions = {
  "Sector Z": {
    "locations": {
      "Sector Z - Mission Complete": {
        "item": ["Nothing", "Sector Z - Blue Path"],
        "group": "Mission Finished",
        "logic": "true",
      },
      "Sector Z - Mission Accomplished": {
        "item": ["Nothing", "Sector Z - Red Path"],
        "group": "Mission Finished",
        "logic": "true",
      },
      "Sector Z - Medal": {
        "item": "Medal",
        "group": "Medals",
        "logic": "true",
      },
    },
    "exits": {
      "Bolse": {
        "type": "Level",
        "logic": "LevelAccess == 'shuffle_paths' and SectorZBluePath",
      },
      "Area 6": {
        "type": "Level",
        "logic": "LevelAccess == 'shuffle_paths' and SectorZRedPath",
      },
    },
  },
}
