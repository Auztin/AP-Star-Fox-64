regions = {
  "Katina": {
    "locations": {
      "Katina - Mission Complete": {
        "item": "Katina - Blue Path",
        "logic": "true",
      },
      "Katina - Mission Accomplished": {
        "item": "Katina - Yellow Path",
        "logic": "true",
      },
      "Katina - Medal": {
        "item": "Medal",
        "logic": "true",
      },
    },
    "exits": {
      "Sector X": {
        "type": "Level",
        "logic": "KatinaBluePath",
      },
      "Solar": {
        "type": "Level",
        "logic": "KatinaYellowPath",
      },
    },
  },
}
