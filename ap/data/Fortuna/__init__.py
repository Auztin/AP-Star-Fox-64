regions = {
  "Fortuna": {
    "locations": {
      "Fortuna - Mission Complete": {
        "item": "FortunaBluePath",
        "logic": "true",
      },
      "Fortuna - Mission Accomplished": {
        "item": "FortunaYellowPath",
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
