regions = {
  "Fortuna": {
    "locations": {
      "Fortuna - Mission Complete": {
        "item": ["Sector X", "Fortuna - Blue Path"],
        "group": "Mission Finished",
        "logic": "true",
      },
      "Fortuna - Mission Accomplished": {
        "item": ["Solar", "Fortuna - Yellow Path"],
        "group": "Mission Finished",
        "logic": "true",
      },
      "Fortuna - Medal": {
        "item": "Medal",
        "group": "Medals",
        "logic": "true",
      },
    },
    "exits": {
      "Sector X": {
        "type": "Level",
        "logic": "LevelAccess == 'shuffle_paths' and FortunaBluePath",
      },
      "Solar": {
        "type": "Level",
        "logic": "LevelAccess == 'shuffle_paths' and FortunaYellowPath",
      },
    },
  },
}
