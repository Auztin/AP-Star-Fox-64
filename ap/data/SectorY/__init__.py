regions = {
  "Sector Y": {
    "locations": {
      "Sector Y - Mission Complete": {
        "item": "SectorYYellowPath",
        "logic": "true",
      },
      "Sector Y - Mission Accomplished": {
        "item": "SectorYRedPath",
        "logic": "true",
      },
      "Sector Y - Medal": {
        "item": "Medal",
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
