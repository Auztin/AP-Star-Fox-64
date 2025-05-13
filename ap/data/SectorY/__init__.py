regions = {
  "Sector Y": {
    "locations": {
      "Sector Y - Mission Complete": {
        "item": "Sector Y - Yellow Path",
        "logic": "true",
      },
      "Sector Y - Mission Accomplished": {
        "item": "Sector Y - Red Path",
        "logic": "true",
      },
      "Sector Y - Medal": {
        "item": "Medal",
        "group": "Medals",
        "logic": "true",
      },
    },
    "exits": {
      "Katina": {
        "type": "Level",
        "logic": "SectorYYellowPath",
      },
      "Aquas": {
        "type": "Level",
        "logic": "SectorYRedPath",
      },
    },
  },
}
