regions = {
  "Menu": {
    "locations": {
      "Starting Level": {
        "item": "Corneria",
        "logic": "LevelAccess == 'shuffle_levels'",
      },
    },
    "exits": {
      "Corneria": {
        "type": "Level",
        "logic": "LevelAccess == 'shuffle_paths' or (LevelAccess == 'shuffle_levels' and Corneria)",
      },
      "Meteo": {
        "type": "Level",
        "logic": "LevelAccess == 'shuffle_levels' and Meteo",
      },
      "Sector X": {
        "type": "Level",
        "logic": "LevelAccess == 'shuffle_levels' and SectorX",
      },
      "Area 6": {
        "type": "Level",
        "logic": "LevelAccess == 'shuffle_levels' and Area6",
      },
      "Sector Y": {
        "type": "Level",
        "logic": "LevelAccess == 'shuffle_levels' and SectorY",
      },
      "Venom 1": {
        "type": "Level",
        "logic": """
          LevelAccess == 'shuffle_levels' and Venom
          and (VictoryCondition != "andross_or_robot_andross" or (Medal, RequiredMedals))
        """,
      },
      "Venom 2": {
        "type": "Level",
        "logic": "LevelAccess == 'shuffle_levels' and Venom and (Medal, RequiredMedals)",
      },
      "Solar": {
        "type": "Level",
        "logic": "LevelAccess == 'shuffle_levels' and Solar",
      },
      "Zoness": {
        "type": "Level",
        "logic": "LevelAccess == 'shuffle_levels' and Zoness",
      },
      "Macbeth": {
        "type": "Level",
        "logic": "LevelAccess == 'shuffle_levels' and Macbeth",
      },
      "Titania": {
        "type": "Level",
        "logic": "LevelAccess == 'shuffle_levels' and Titania",
      },
      "Aquas": {
        "type": "Level",
        "logic": "LevelAccess == 'shuffle_levels' and Aquas",
      },
      "Fortuna": {
        "type": "Level",
        "logic": "LevelAccess == 'shuffle_levels' and Fortuna",
      },
      "Katina": {
        "type": "Level",
        "logic": "LevelAccess == 'shuffle_levels' and Katina",
      },
      "Bolse": {
        "type": "Level",
        "logic": "LevelAccess == 'shuffle_levels' and Bolse",
      },
      "Sector Z": {
        "type": "Level",
        "logic": "LevelAccess == 'shuffle_levels' and SectorZ",
      },
    },
  },
}
