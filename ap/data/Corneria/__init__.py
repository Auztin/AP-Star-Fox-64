regions = {
  "Corneria": {
    "locations": {
      "Corneria - Mission Complete": {
        "item": ["Meteo", "Corneria - Blue Path"],
        "group": "Mission Finished",
        "logic": "true",
      },
      "Corneria - Mission Accomplished": {
        "item": ["Sector Y", "Corneria - Red Path"],
        "group": "Mission Finished",
        "logic": "true",
      },
      "Corneria - Medal": {
        "item": "Medal",
        "group": "Medals",
        "logic": "true",
      },
      "Corneria - Under Arch: Gold Ring": {
        "item": "Gold Ring",
        "group": "Freestanding Items",
        "logic": "true",
      },
      "Corneria - Behind Doors: Bomb": {
        "item": "Bomb",
        "group": "Freestanding Items",
        "logic": "true",
      },
      "Corneria - Center Of Corneria City: Silver Ring": {
        "item": "Silver Ring",
        "group": "Freestanding Items",
        "logic": "true",
      },
      "Corneria - Near First Ground Robot: Laser Upgrade": {
        "item": "Laser Upgrade",
        "group": "Freestanding Items",
        "logic": "true",
      },
      "Corneria - Under Highway Arch: Gold Ring": {
        "item": "Gold Ring",
        "group": "Freestanding Items",
        "logic": "true",
      },
      "Corneria - Behind Second Ground Robot: Bomb": {
        "item": "Bomb",
        "group": "Freestanding Items",
        "logic": "true",
      },
      "Corneria - Behind Doors Near Checkpoint: Gold Ring": {
        "item": "Gold Ring",
        "group": "Freestanding Items",
        "logic": "true",
      },
      "Corneria - Checkpoint": {
        "item": "Corneria - Checkpoint",
        "group": "Checkpoints",
        "logic": "true",
      },
      "Corneria - After Falco's G-Diffuser Issue: Laser Upgrade": {
        "item": "Laser Upgrade",
        "group": "Freestanding Items",
        "logic": "true",
      },
      "Corneria - After Falco's G-Diffuser Issue: Bomb": {
        "item": "Bomb",
        "group": "Freestanding Items",
        "logic": "true",
      },
      "Corneria - Water Section Last Arch: Gold Ring": {
        "item": "Gold Ring",
        "group": "Freestanding Items",
        "logic": "true",
      },
      "Corneria - Left Of Waterfall: Laser Upgrade": {
        "item": "Laser Upgrade",
        "group": "Freestanding Items",
        "logic": "true",
      },
      "Corneria - Before Mission Complete Boss, Lower: Gold Ring": {
        "item": "Gold Ring",
        "group": "Freestanding Items",
        "logic": "true",
      },
      "Corneria - Before Mission Complete Boss, Upper: Gold Ring": {
        "item": "Gold Ring",
        "group": "Freestanding Items",
        "logic": "true",
      },
    },
    "exits": {
      "Meteo": {
        "type": "Level",
        "logic": "LevelAccess == 'shuffle_paths' and CorneriaBluePath",
      },
      "Sector Y": {
        "type": "Level",
        "logic": "LevelAccess == 'shuffle_paths' and CorneriaRedPath",
      },
    },
  },
}
