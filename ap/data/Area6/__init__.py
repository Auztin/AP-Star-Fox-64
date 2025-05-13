regions = {
  "Area 6": {
    "locations": {
      "Area 6 - Mission Complete": {
        "item": "Area 6 - Red Path",
        "logic": "true",
      },
      "Area 6 - Medal": {
        "item": "Medal",
        "group": "Medals",
        "logic": "true",
      },
      "Area 6 - Below Early Defense Station: Gold Ring": {
        "item": "Gold Ring",
        "group": "Freestanding Items",
        "logic": "true",
      },
      "Area 6 - Above Early Defense Station: Laser Upgrade": {
        "item": "Laser Upgrade",
        "group": "Freestanding Items",
        "logic": "true",
      },
      "Area 6 - Andross' Taunt: Gold Ring": {
        "item": "Laser Upgrade",
        "group": "Freestanding Items",
        "logic": "true",
      },
      "Area 6 - Checkpoint": {
        "item": "Area 6 - Checkpoint",
        "group": "Checkpoints",
        "logic": "true",
      },
      "Area 6 - Near Defense Station After Checkpoint: Gold Ring": {
        "item": "Gold Ring",
        "group": "Freestanding Items",
        "logic": "true",
      },
    },
    "exits": {
      "Venom 2": {
        "type": "Level",
        "logic": "Area6RedPath and (Medal, RequiredMedals)",
      },
    },
  },
}
