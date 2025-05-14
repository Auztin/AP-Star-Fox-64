regions = {
  "Sector X": {
    "locations": {
      "Sector X - Mission Complete": {
        "item": ["Titania", "Sector X - Blue Path"],
        "group": "Mission Finished",
        "logic": "true",
      },
      "Sector X - Mission Accomplished": {
        "item": ["Macbeth", "Sector X - Yellow Path"],
        "group": "Mission Finished",
        "logic": "true",
      },
      "Sector X - Warp": {
        "item": ["Sector Z", "Sector X - Warp Path"],
        "group": "Mission Finished",
        "logic": "true",
      },
      "Sector X - Medal": {
        "item": "Medal",
        "group": "Medals",
        "logic": "true",
      },
      "Sector X - In Debris Field, Left: Gold Ring": {
        "item": "Gold Ring",
        "group": "Freestanding Items",
        "logic": "true",
      },
      "Sector X - Checkpoint": {
        "item": "Sector X - Checkpoint",
        "group": "Checkpoints",
        "logic": "true",
      },
      "Sector X - Behind Enemy After Peppy Gets Chased, Right: Gold Ring": {
        "item": "Gold Ring" ,
        "group": "Freestanding Items",
        "logic": "true",
      },
      "Sector X - Left Path - Just After Fork, Through Bottom Slot: Laser Upgrade": {
        "item": "Laser Upgrade" ,
        "group": "Freestanding Items",
        "logic": "true",
      },
      "Sector X - Left Path - Closing Door Section: Gold Ring": {
        "item": "Gold Ring" ,
        "group": "Freestanding Items",
        "logic": "true",
      },
      "Sector X - Left Path - After Closing Door Section: Bomb": {
        "item": "Bomb" ,
        "group": "Freestanding Items",
        "logic": "true",
      },
      "Sector X - Left Path - Behind First Warp Gate: Gold Ring": {
        "item": "Gold Ring" ,
        "group": "Freestanding Items",
        "logic": "true",
      },
      "Sector X - Left Path - After First Warp Gate, Up High: Bomb": {
        "item": "Bomb" ,
        "group": "Freestanding Items",
        "logic": "true",
      },
      "Sector X - Left Path - Before Final Warp Gate: Gold Ring": {
        "item": "Gold Ring" ,
        "group": "Freestanding Items",
        "logic": "true",
      },
    },
    "exits": {
      "Titania": {
        "type": "Level",
        "logic": "LevelAccess == 'shuffle_paths' and SectorXBluePath",
      },
      "Macbeth": {
        "type": "Level",
        "logic": "LevelAccess == 'shuffle_paths' and SectorXYellowPath",
      },
      "Sector Z": {
        "type": "Level",
        "logic": "LevelAccess == 'shuffle_paths' and SectorXWarpPath",
      },
    },
  },
}
