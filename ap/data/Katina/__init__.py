regions = {
  "Katina": {
    "locations": {
      "Katina - Mission Complete": {
        "item": "KatinaBluePath",
        "logic": "true",
      },
      "Katina - Mission Accomplished": {
        "item": "KatinaYellowPath",
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
