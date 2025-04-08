# Automatically generated using enum_gen.py

option_name_to_id = {
  "deathlink": 0,
  "victory_condition": 1,
  "required_medals": 2,
  "shuffle_medals": 3,
  "shuffle_paths": 4,
  "accomplished_sends_complete": 5
}

item_name_to_id = {
  "Death Link": 1,
  "Medal": 2,
  "Aquas - Red Path": 3,
  "Area 6 - Red Path": 4,
  "Bolse - Blue Path": 5,
  "Corneria - Blue Path": 6,
  "Corneria - Red Path": 7,
  "Fortuna - Blue Path": 8,
  "Fortuna - Yellow Path": 9,
  "Katina - Blue Path": 10,
  "Katina - Yellow Path": 11,
  "Macbeth - Blue Path": 12,
  "Macbeth - Red Path": 13,
  "Meteo - Blue Path": 14,
  "Meteo - Warp Path": 15,
  "Sector X - Blue Path": 16,
  "Sector X - Yellow Path": 17,
  "Sector X - Warp Path": 18,
  "Sector Y - Yellow Path": 19,
  "Sector Y - Red Path": 20,
  "Sector Z - Blue Path": 21,
  "Sector Z - Red Path": 22,
  "Solar - Yellow Path": 23,
  "Titania - Blue Path": 24,
  "Zoness - Yellow Path": 25,
  "Zoness - Red Path": 26,
  "Defeated Robot Andross": 27,
  "Defeated Andross": 28
}

item_alias_to_name = {
  "DeathLink": "Death Link",
  "Medal": "Medal",
  "AquasRedPath": "Aquas - Red Path",
  "Area6RedPath": "Area 6 - Red Path",
  "BolseBluePath": "Bolse - Blue Path",
  "CorneriaBluePath": "Corneria - Blue Path",
  "CorneriaRedPath": "Corneria - Red Path",
  "FortunaBluePath": "Fortuna - Blue Path",
  "FortunaYellowPath": "Fortuna - Yellow Path",
  "KatinaBluePath": "Katina - Blue Path",
  "KatinaYellowPath": "Katina - Yellow Path",
  "MacbethBluePath": "Macbeth - Blue Path",
  "MacbethRedPath": "Macbeth - Red Path",
  "MeteoBluePath": "Meteo - Blue Path",
  "MeteoWarpPath": "Meteo - Warp Path",
  "SectorXBluePath": "Sector X - Blue Path",
  "SectorXYellowPath": "Sector X - Yellow Path",
  "SectorXWarpPath": "Sector X - Warp Path",
  "SectorYYellowPath": "Sector Y - Yellow Path",
  "SectorYRedPath": "Sector Y - Red Path",
  "SectorZBluePath": "Sector Z - Blue Path",
  "SectorZRedPath": "Sector Z - Red Path",
  "SolarYellowPath": "Solar - Yellow Path",
  "TitaniaBluePath": "Titania - Blue Path",
  "ZonessYellowPath": "Zoness - Yellow Path",
  "ZonessRedPath": "Zoness - Red Path",
  "DefeatedRobotAndross": "Defeated Robot Andross",
  "DefeatedAndross": "Defeated Andross"
}

location_name_to_id = {
  "None": -1,
  "Goal Completed": 0,
  "Death Link": 1,
  "Aquas - Mission Complete": 2,
  "Aquas - Medal": 3,
  "Area 6 - Mission Complete": 4,
  "Area 6 - Medal": 5,
  "Bolse - Mission Complete": 6,
  "Bolse - Medal": 7,
  "Corneria - Mission Complete": 8,
  "Corneria - Mission Accomplished": 9,
  "Corneria - Medal": 10,
  "Fortuna - Mission Complete": 11,
  "Fortuna - Mission Accomplished": 12,
  "Fortuna - Medal": 13,
  "Katina - Mission Complete": 14,
  "Katina - Mission Accomplished": 15,
  "Katina - Medal": 16,
  "Macbeth - Mission Complete": 17,
  "Macbeth - Mission Accomplished": 18,
  "Macbeth - Medal": 19,
  "Meteo - Mission Complete": 20,
  "Meteo - Warp": 21,
  "Meteo - Medal": 22,
  "Sector X - Mission Complete": 23,
  "Sector X - Mission Accomplished": 24,
  "Sector X - Warp": 25,
  "Sector X - Medal": 26,
  "Sector Y - Mission Complete": 27,
  "Sector Y - Mission Accomplished": 28,
  "Sector Y - Medal": 29,
  "Sector Z - Mission Complete": 30,
  "Sector Z - Mission Accomplished": 31,
  "Sector Z - Medal": 32,
  "Solar - Mission Complete": 33,
  "Solar - Medal": 34,
  "Titania - Mission Complete": 35,
  "Titania - Medal": 36,
  "Venom - Medal": 37,
  "Venom - Defeat Robot Andross": 38,
  "Venom - Defeat Andross": 39,
  "Zoness - Mission Complete": 40,
  "Zoness - Mission Accomplished": 41,
  "Zoness - Medal": 42
}

class AP_CMD:
  NONE = 0
  HANDSHAKE = 1
  PING = 2
  PONG = 3
  SEED = 4
  OPTIONS = 5
  LOCATIONS = 6
  ITEMS = 7

class AP_STATE:
  DISCONNECTED = 0
  CONNECTING = 1
  CONNECTED = 2
  PINGED = 4
