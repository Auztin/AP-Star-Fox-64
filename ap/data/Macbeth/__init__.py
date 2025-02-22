regions = {
  "Macbeth": {
    "locations": {
      "Macbeth - Mission Complete": {
        "item": "MacbethBluePath",
        "logic": "true",
      },
      "Macbeth - Mission Accomplished": {
        "item": "MacbethRedPath",
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
