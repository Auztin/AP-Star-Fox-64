regions = {
  "Meteo": {
    "locations": {
      "Meteo - Mission Complete": {
        "item": ["Fortuna", "Meteo - Blue Path"],
        "group": "Mission Finished",
        "logic": "true",
      },
      "Meteo - Warp": {
        "item": ["Katina", "Meteo - Warp Path"],
        "group": "Mission Finished",
        "logic": "true",
      },
      "Meteo - Medal": {
        "item": "Medal",
        "group": "Medals",
        "logic": "true",
      },
      "Meteo - After Starting Asteroids: Gold Ring": {
        "item": "Gold Ring",
        "group": "Freestanding Items",
        "logic": "true",
      },
      "Meteo - End Of First Tunnel, Top: Silver Ring": {
        "item": "Silver Ring",
        "group": "Freestanding Items",
        "logic": "true",
      },
      "Meteo - End Of First Tunnel, Middle: Gold Ring": {
        "item": "Gold Ring",
        "group": "Freestanding Items",
        "logic": "true",
      },
      "Meteo - End Of First Tunnel, Bottom: Bomb": {
        "item": "Bomb",
        "group": "Freestanding Items",
        "logic": "true",
      },
      "Meteo - Between Two Big Asteroids: Bomb": {
        "item": "Bomb",
        "group": "Freestanding Items",
        "logic": "true",
      },
      "Meteo - Checkpoint": {
        "item": "Meteo - Checkpoint",
        "group": "Checkpoints",
        "logic": "true",
      },
      "Meteo - Near Warp Rings: Gold Ring": {
        "item": "Gold Ring",
        "group": "Freestanding Items",
        "logic": "true",
      },
      "Meteo - Just Before Boss: Gold Ring": {
        "item": "Gold Ring",
        "group": "Freestanding Items",
        "logic": "true",
      },
    },
    "exits": {
      "Fortuna": {
        "type": "Level",
        "logic": "LevelAccess == 'shuffle_paths' and MeteoBluePath",
      },
      "Katina": {
        "type": "Level",
        "logic": "LevelAccess == 'shuffle_paths' and MeteoWarpPath",
      },
    },
  },
}
