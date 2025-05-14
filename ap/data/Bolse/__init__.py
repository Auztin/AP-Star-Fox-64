regions = {
  "Bolse": {
    "locations": {
      "Bolse - Mission Complete": {
        "item": ["Venom", "Bolse - Blue Path"],
        "group": "Mission Finished",
        "logic": "true",
      },
      "Bolse - Medal": {
        "item": "Medal",
        "group": "Medals",
        "logic": "true",
      },
    },
    "exits": {
      "Venom 1": {
        "type": "Level",
        "logic": """
          LevelAccess == 'shuffle_paths'
          and BolseBluePath and (VictoryCondition != "andross_or_robot_andross" or (Medal, RequiredMedals))
        """,
      },
    },
  },
}
