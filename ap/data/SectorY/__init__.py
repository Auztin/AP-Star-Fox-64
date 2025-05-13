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
        "logic": "SectorYYellowPath",
      },
      "Aquas": {
        "type": "Level",
        "logic": "SectorYRedPath",
      },
    },
  },
}
