regions = {
  "Corneria": {
    "locations": {
      "Corneria - Mission Complete": {
        "item": "CorneriaBluePath",
        "logic": "true",
      },
      "Corneria - Mission Accomplished": {
        "item": "CorneriaRedPath",
        "logic": "true",
      },
      "Corneria - Medal": {
        "item": "Medal",
        "logic": "true",
      },
    },
    "exits": {
      "Meteo": {
        "type": "Level",
        "logic": "CorneriaBluePath",
      },
      "Sector Y": {
        "type": "Level",
        "logic": "CorneriaRedPath",
      },
    },
  },
}
