regions = {
  "Zoness": {
    "locations": {
      "Zoness - Mission Complete": {
        "item": "Zoness - Yellow Path",
        "logic": "true",
      },
      "Zoness - Mission Accomplished": {
        "item": "Zoness - Red Path",
        "logic": "true",
      },
      "Zoness - Medal": {
        "item": "Medal",
        "logic": "true",
      },
    },
    "exits": {
      "Macbeth": {
        "type": "Level",
        "logic": "ZonessYellowPath",
      },
      "Sector Z": {
        "type": "Level",
        "logic": "ZonessRedPath",
      },
    },
  },
}
