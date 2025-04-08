regions = {
  "Meteo": {
    "locations": {
      "Meteo - Mission Complete": {
        "item": "Meteo - Blue Path",
        "logic": "true",
      },
      "Meteo - Warp": {
        "item": "Meteo - Warp Path",
        "logic": "true",
      },
      "Meteo - Medal": {
        "item": "Medal",
        "logic": "true",
      },
    },
    "exits": {
      "Fortuna": {
        "type": "Level",
        "logic": "MeteoBluePath",
      },
      "Katina": {
        "type": "Level",
        "logic": "MeteoWarpPath",
      },
    },
  },
}
