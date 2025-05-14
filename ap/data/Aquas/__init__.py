regions = {
  "Aquas": {
    "locations": {
      "Aquas - Mission Complete": {
        "item": ["Zoness", "Aquas - Red Path"],
        "group": "Mission Finished",
        "logic": "true",
      },
      "Aquas - Medal": {
        "item": "Medal",
        "group": "Medals",
        "logic": "true",
      },
      "Aquas - Checkpoint": {
        "item": "Aquas - Checkpoint",
        "group": "Checkpoints",
        "logic": "true",
      },
    },
    "exits": {
      "Zoness": {
        "type": "Level",
        "logic": "LevelAccess == 'shuffle_paths' and AquasRedPath",
      },
    },
  },
}
