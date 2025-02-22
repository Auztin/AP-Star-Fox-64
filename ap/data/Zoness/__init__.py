regions = {
  "Zoness": {
    "locations": {
      "Zoness - Mission Complete": {
        "item": "ZonessYellowPath",
        "logic": "true",
      },
      "Zoness - Mission Accomplished": {
        "item": "ZonessRedPath",
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
