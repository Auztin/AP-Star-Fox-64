regions = {
  "Bolse": {
    "locations": {
      "Bolse - Mission Complete": {
        "item": "Bolse - Blue Path",
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
          BolseBluePath and (VictoryCondition != "andross_or_robot_andross" or (Medal, RequiredMedals))
        """,
      },
    },
  },
}
