# Automatically generated using enum_gen.py

option_name_to_id = {
  "victory_condition": 0,
  "required_medals": 1,
  "shuffle_medals": 2,
  "shuffle_paths": 3
}

item_name_to_id = {
  "Medal": 1,
  "Aquas - Red Path": 2,
  "Area 6 - Red Path": 3,
  "Bolse - Blue Path": 4,
  "Corneria - Blue Path": 5,
  "Corneria - Red Path": 6,
  "Fortuna - Blue Path": 7,
  "Fortuna - Yellow Path": 8,
  "Katina - Blue Path": 9,
  "Katina - Yellow Path": 10,
  "Macbeth - Blue Path": 11,
  "Macbeth - Red Path": 12,
  "Meteo - Blue Path": 13,
  "Meteo - Warp Path": 14,
  "Sector X - Blue Path": 15,
  "Sector X - Yellow Path": 16,
  "Sector X - Warp Path": 17,
  "Sector Y - Yellow Path": 18,
  "Sector Y - Red Path": 19,
  "Sector Z - Blue Path": 20,
  "Sector Z - Red Path": 21,
  "Solar - Yellow Path": 22,
  "Titania - Blue Path": 23,
  "Zoness - Yellow Path": 24,
  "Zoness - Red Path": 25,
  "Defeated Robot Andross": 26,
  "Defeated Andross": 27
}

item_alias_to_name = {
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
  "Aquas - Mission Complete": 1,
  "Aquas - Medal": 2,
  "Area 6 - Mission Complete": 3,
  "Area 6 - Medal": 4,
  "Bolse - Mission Complete": 5,
  "Bolse - Medal": 6,
  "Corneria - Mission Complete": 7,
  "Corneria - Mission Accomplished": 8,
  "Corneria - Medal": 9,
  "Fortuna - Mission Complete": 10,
  "Fortuna - Mission Accomplished": 11,
  "Fortuna - Medal": 12,
  "Katina - Mission Complete": 13,
  "Katina - Mission Accomplished": 14,
  "Katina - Medal": 15,
  "Macbeth - Mission Complete": 16,
  "Macbeth - Mission Accomplished": 17,
  "Macbeth - Medal": 18,
  "Meteo - Mission Complete": 19,
  "Meteo - Warp": 20,
  "Meteo - Medal": 21,
  "Sector X - Mission Complete": 22,
  "Sector X - Mission Accomplished": 23,
  "Sector X - Warp": 24,
  "Sector X - Medal": 25,
  "Sector Y - Mission Complete": 26,
  "Sector Y - Mission Accomplished": 27,
  "Sector Y - Medal": 28,
  "Sector Z - Mission Complete": 29,
  "Sector Z - Mission Accomplished": 30,
  "Sector Z - Medal": 31,
  "Solar - Mission Complete": 32,
  "Solar - Medal": 33,
  "Titania - Mission Complete": 34,
  "Titania - Medal": 35,
  "Venom - Medal": 36,
  "Venom - Defeat Robot Andross": 37,
  "Venom - Defeat Andross": 38,
  "Zoness - Mission Complete": 39,
  "Zoness - Mission Accomplished": 40,
  "Zoness - Medal": 41
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
