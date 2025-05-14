regions = {
  "Sector Y": {
    "locations": {
      "Sector Y - Mission Complete": {
        "item": ["Nothing", "Sector Y - Yellow Path"],
        "group": "Mission Finished",
        "logic": "true",
      },
      "Sector Y - Mission Accomplished": {
        "item": ["Aquas", "Sector Y - Red Path"],
        "group": "Mission Finished",
        "logic": "true",
      },
      "Sector Y - Medal": {
        "item": "Medal",
        "group": "Medals",
        "logic": "true",
      },
      "Sector Y - Above Friendly Ship Near Start: Gold Ring": {
        "item": "Gold Ring",
        "group": "Freestanding Items",
        "logic": "true",
      },
      "Sector Y - Before Checkpoint: Gold Ring": {
        "item": "Gold Ring",
        "group": "Freestanding Items",
        "logic": "true",
      },
      "Sector Y - Checkpoint": {
        "item": "Sector Y - Checkpoint",
        "group": "Checkpoints",
        "logic": "true",
      },
      "Sector Y - Breaking Through The Enemy Fleet, Beginning: Gold Ring": {
        "item": "Gold Ring",
        "group": "Freestanding Items",
        "logic": "true",
      },
      "Sector Y - Breaking Through The Enemy Fleet, Middle: Gold Ring": {
        "item": "Gold Ring",
        "group": "Freestanding Items",
        "logic": "true",
      },
      "Sector Y - Breaking Through The Enemy Fleet, End: Gold Ring": {
        "item": "Gold Ring",
        "group": "Freestanding Items",
        "logic": "true",
      },
    },
    "exits": {
      "Katina": {
        "type": "Level",
        "logic": "LevelAccess == 'shuffle_paths' and SectorYYellowPath",
      },
      "Aquas": {
        "type": "Level",
        "logic": "LevelAccess == 'shuffle_paths' and SectorYRedPath",
      },
    },
  },
}
