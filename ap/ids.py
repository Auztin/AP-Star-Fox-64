# Automatically generated using enum_gen.py

option_name_to_id = {
  "deathlink": 0,
  "ringlink": 1,
  "victory_condition": 2,
  "required_medals": 3,
  "shuffle_medals": 4,
  "shuffle_paths": 5,
  "accomplished_sends_complete": 6,
  "radio_rando": 7,
  "default_lives": 8,
  "medal_corneria": 9,
  "medal_meteo": 10,
  "medal_sector_y": 11,
  "medal_katina": 12,
  "medal_fortuna": 13,
  "medal_aquas": 14,
  "medal_solar": 15,
  "medal_sector_x": 16,
  "medal_zoness": 17,
  "medal_titania": 18,
  "medal_sector_z": 19,
  "medal_macbeth": 20,
  "medal_area_6": 21,
  "medal_bolse": 22,
  "medal_venom": 23
}

item_name_to_id = {
  "None": -1,
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
  READY = 6
  LOCATIONS = 7
  ITEMS = 8
  DEATHLINK = 9
  RINGLINK = 10

class AP_STATE:
  DISCONNECTED = 0
  CONNECTING = 1
  CONNECTED = 2
  PINGED = 4
