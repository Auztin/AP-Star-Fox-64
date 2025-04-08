regions = {
  "Area 6": {
    "locations": {
      "Area 6 - Mission Complete": {
        "item": "Area 6 - Red Path",
        "logic": "true",
      },
      "Area 6 - Medal": {
        "item": "Medal",
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
