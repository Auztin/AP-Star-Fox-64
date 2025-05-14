regions = {
  "Solar": {
    "locations": {
      "Solar - Mission Complete": {
        "item": ["Nothing", "Solar - Yellow Path"],
        "group": "Mission Finished",
        "logic": "true",
      },
      "Solar - Medal": {
        "item": "Medal",
        "group": "Medals",
        "logic": "true",
      },
      "Solar - Checkpoint": {
        "item": "Solar - Checkpoint",
        "group": "Checkpoints",
        "logic": "true",
      },
    },
    "exits": {
      "Macbeth": {
        "type": "Level",
        "logic": "LevelAccess == 'shuffle_paths' and SolarYellowPath",
      },
    },
  },
}
