regions = {
  "Meteo": {
    "locations": {
      "Meteo - Mission Complete": {
        "item": "MeteoBluePath",
        "logic": "true",
      },
      "Meteo - Warp": {
        "item": "MeteoWarpPath",
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
