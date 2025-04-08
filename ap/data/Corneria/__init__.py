regions = {
  "Corneria": {
    "locations": {
      "Corneria - Mission Complete": {
        "item": "Corneria - Blue Path",
        "logic": "true",
      },
      "Corneria - Mission Accomplished": {
        "item": "Corneria - Red Path",
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
