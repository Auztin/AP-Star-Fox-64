regions = {
  "Katina": {
    "locations": {
      "Katina - Mission Complete": {
        "item": ["Nothing", "Katina - Blue Path"],
        "group": "Mission Finished",
        "logic": "true",
      },
      "Katina - Mission Accomplished": {
        "item": ["Nothing", "Katina - Yellow Path"],
        "group": "Mission Finished",
        "logic": "true",
      },
      "Katina - Medal": {
        "item": "Medal",
        "group": "Medals",
        "logic": "true",
      },
    },
    "exits": {
      "Sector X": {
        "type": "Level",
        "logic": "LevelAccess == 'shuffle_paths' and KatinaBluePath",
      },
      "Solar": {
        "type": "Level",
        "logic": "LevelAccess == 'shuffle_paths' and KatinaYellowPath",
      },
    },
  },
}
