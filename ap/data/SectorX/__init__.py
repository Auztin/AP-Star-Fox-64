regions = {
  "Sector X": {
    "locations": {
      "Sector X - Mission Complete": {
        "item": "Sector X - Blue Path",
        "logic": "true",
      },
      "Sector X - Mission Accomplished": {
        "item": "Sector X - Yellow Path",
        "logic": "true",
      },
      "Sector X - Warp": {
        "item": "Sector X - Warp Path",
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
