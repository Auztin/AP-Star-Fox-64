regions = {
  "Macbeth": {
    "locations": {
      "Macbeth - Mission Complete": {
        "item": ["Nothing", "Macbeth - Blue Path"],
        "group": "Mission Finished",
        "logic": "true",
      },
      "Macbeth - Mission Accomplished": {
        "item": ["Area 6", "Macbeth - Red Path"],
        "group": "Mission Finished",
        "logic": "true",
      },
      "Macbeth - Medal": {
        "item": "Medal",
        "group": "Medals",
        "logic": "true",
      },
      "Macbeth - Before Hill With Rolling Rocks: Bomb": {
        "item": "Bomb",
        "group": "Freestanding Items",
        "logic": "true",
      },
      "Macbeth - Above Rolling Rocks: Gold Ring": {
        "item": "Gold Ring",
        "group": "Freestanding Items",
        "logic": "true",
      },
      "Macbeth - On Tracks Before Bridge: Gold Ring": {
        "item": "Gold Ring",
        "group": "Freestanding Items",
        "logic": "true",
      },
      "Macbeth - On Tracks After Bridge: Gold Ring": {
        "item": "Gold Ring",
        "group": "Freestanding Items",
        "logic": "true",
      },
      "Macbeth - Checkpoint": {
        "item": "Macbeth - Checkpoint",
        "group": "Checkpoints",
        "logic": "true",
      },
      "Macbeth - After First Building: Silver Ring": {
        "item": "Silver Ring",
        "group": "Freestanding Items",
        "logic": "true",
      },
      "Macbeth - Before Buildings Three And Four: Silver Ring": {
        "item": "Silver Ring",
        "group": "Freestanding Items",
        "logic": "true",
      },
      "Macbeth - After Buildings Three And Four, Right: Silver Ring": {
        "item": "Silver Ring",
        "group": "Freestanding Items",
        "logic": "true",
      },
      "Macbeth - Before Building Five: Silver Ring": {
        "item": "Silver Ring",
        "group": "Freestanding Items",
        "logic": "true",
      },
      "Macbeth - After Building Five: Gold Ring": {
        "item": "Gold Ring",
        "group": "Freestanding Items",
        "logic": "true",
      },
      "Macbeth - Under Bridge After Checkpoint: Bomb": {
        "item": "Bomb",
        "group": "Freestanding Items",
        "logic": "true",
      },
      "Macbeth - First Building After Switcher: Gold Ring": {
        "item": "Gold Ring",
        "group": "Freestanding Items",
        "logic": "true",
      },
      "Macbeth - Second Building After Switcher: Silver Ring": {
        "item": "Silver Ring",
        "group": "Freestanding Items",
        "logic": "true",
      },
      "Macbeth - After Marker 100: Silver Ring": {
        "item": "Silver Ring",
        "group": "Freestanding Items",
        "logic": "true",
      },
      "Macbeth - Before Marker 300: Silver Ring": {
        "item": "Silver Ring",
        "group": "Freestanding Items",
        "logic": "true",
      },
    },
    "exits": {
      "Bolse": {
        "type": "Level",
        "logic": "LevelAccess == 'shuffle_paths' and MacbethBluePath",
      },
      "Area 6": {
        "type": "Level",
        "logic": "LevelAccess == 'shuffle_paths' and MacbethRedPath",
      },
    },
  },
}
