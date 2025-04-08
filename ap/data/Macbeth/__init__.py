regions = {
  "Macbeth": {
    "locations": {
      "Macbeth - Mission Complete": {
        "item": "Macbeth - Blue Path",
        "logic": "true",
      },
      "Macbeth - Mission Accomplished": {
        "item": "Macbeth - Red Path",
        "logic": "true",
      },
      "Macbeth - Medal": {
        "item": "Medal",
        "logic": "true",
      },
    },
    "exits": {
      "Bolse": {
        "type": "Level",
        "logic": "MacbethBluePath",
      },
      "Area 6": {
        "type": "Level",
        "logic": "MacbethRedPath",
      },
    },
  },
}
