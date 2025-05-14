regions = {
  "Zoness": {
    "locations": {
      "Zoness - Mission Complete": {
        "item": ["Nothing", "Zoness - Yellow Path"],
        "group": "Mission Finished",
        "logic": "true",
      },
      "Zoness - Mission Accomplished": {
        "item": ["Nothing", "Zoness - Red Path"],
        "group": "Mission Finished",
        "logic": "true",
      },
      "Zoness - Medal": {
        "item": "Medal",
        "group": "Medals",
        "logic": "true",
      },
      "Zoness - Before Katt Appears, Top: Gold Ring": {
        "item": "Gold Ring",
        "group": "Freestanding Items",
        "logic": "true",
      },
      "Zoness - Before Katt Appears, Middle: Silver Ring": {
        "item": "Silver Ring",
        "group": "Freestanding Items",
        "logic": "true",
      },
      "Zoness - Before Katt Appears, Bottom: Bomb": {
        "item": "Bomb",
        "group": "Freestanding Items",
        "logic": "true",
      },
      "Zoness - Checkpoint": {
        "item": "Zoness - Checkpoint",
        "group": "Checkpoints",
        "logic": "true",
      },
      "Zoness - Aim For The Rudder, First Gate: Laser Upgrade": {
        "item": "Laser Upgrade",
        "group": "Freestanding Items",
        "logic": "true",
      },
      "Zoness - Aim For The Rudder, Second Gate, Left: Bomb": {
        "item": "Bomb",
        "group": "Freestanding Items",
        "logic": "true",
      },
      "Zoness - Aim For The Rudder, Third Gate: Silver Ring": {
        "item": "Silver Ring",
        "group": "Freestanding Items",
        "logic": "true",
      },
    },
    "exits": {
      "Macbeth": {
        "type": "Level",
        "logic": "LevelAccess == 'shuffle_paths' and ZonessYellowPath",
      },
      "Sector Z": {
        "type": "Level",
        "logic": "LevelAccess == 'shuffle_paths' and ZonessRedPath",
      },
    },
  },
}
