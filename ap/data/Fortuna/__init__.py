regions = {
  "Fortuna": {
    "locations": {
      "Fortuna - Mission Complete": {
        "item": "Fortuna - Blue Path",
        "logic": "true",
      },
      "Fortuna - Mission Accomplished": {
        "item": "Fortuna - Yellow Path",
        "logic": "true",
      },
      "Fortuna - Medal": {
        "item": "Medal",
        "logic": "true",
      },
    },
    "exits": {
      "Sector X": {
        "type": "Level",
        "logic": "FortunaBluePath",
      },
      "Solar": {
        "type": "Level",
        "logic": "FortunaYellowPath",
      },
    },
  },
}
