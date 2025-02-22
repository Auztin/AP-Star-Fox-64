regions = {
  "Sector X": {
    "locations": {
      "Sector X - Mission Complete": {
        "item": "SectorXBluePath",
        "logic": "true",
      },
      "Sector X - Mission Accomplished": {
        "item": "SectorXYellowPath",
        "logic": "true",
      },
      "Sector X - Warp": {
        "item": "SectorXWarpPath",
        "logic": "true",
      },
      "Sector X - Medal": {
        "item": "Medal",
        "logic": "true",
      },
    },
    "exits": {
      "Titania": {
        "type": "Level",
        "logic": "SectorXBluePath",
      },
      "Macbeth": {
        "type": "Level",
        "logic": "SectorXYellowPath",
      },
      "Sector Z": {
        "type": "Level",
        "logic": "SectorXWarpPath",
      },
    },
  },
}
