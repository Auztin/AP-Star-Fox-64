from dataclasses import dataclass
from Options import PerGameCommonOptions, Choice, Range, Toggle, DefaultOnToggle, StartInventoryPool

class DeathLink(Toggle):
  """
    When you die, everyone who enabled death link dies. Of course, the reverse is true too.
  """
  display_name = "Death Link"

class RingLink(Toggle):
  """
    Enable Ring Link for use with games that support it. Incoming rings are converted to the current level's Hit counter.
  """
  display_name = "Ring Link"

class VictoryCondition(Choice):
  """
    Choose your victory condition.
    Andross or Robot Andross - Defeat either Andross or Robot Andross
    Andross and Robot Andross - Defeat both Andross and Robot Andross
    Andross - Defeat Andross in Venom 2
  """
  display_name = "Victory Condition"
  option_andross_or_robot_andross = 0
  option_andross_and_robot_andross = 1
  option_andross = 2

class RequiredMedals(Range):
  """
    Require a certain number of medals before you can enter Venom 2.
    The same requirment will apply for Venom 1 if your victory condition is 'Andross or Robot Andross'
  """
  display_name = "Required Medals"
  range_start = 0
  range_end = 15

class LevelAccess(Choice):
  """
    Completing a level a certain way will give a random item.
    Choose what type of level access item gets added to the pool.

    Shuffle Levels - You will receive levels as items which will allow you to select that level at any time.
    Shuffle Paths - You will receive paths as items which will allow you to take that path to other levels.
  """
  display_name = "Level Access"
  option_shuffle_levels = 0
  option_shuffle_paths = 1

class ShuffleStartingLevel(Toggle):
  """
    If Level Access is 'Shuffle Levels', shuffle which level you start with.
    You normally start with Corneria.
  """
  display_name = "Shuffle Starting Level"

class ShuffleMedals(Toggle):
  """
    Shuffle the medals awarded by reaching a certain number of Hits in each level.
    Earning a medal will give a random item, and you will visually see the medal on the map to indicate that you've completed the check.

    Note: Medals are very challenging in vanilla.
    Unless you know what you're doing, it is recommended to lower the score needed for each level using their options.
  """
  display_name = "Shuffle Medals"

class ShuffleCheckpoints(Toggle):
  """
    Shuffle checkpoints rings for the levels that have them.
    You will not be able to use the checkpoint ring in a level until you receive the item for it.
  """
  display_name = "Shuffle Checkpoints"

class AccomplishedSendsComplete(Toggle):
  """
    Getting 'Mission Accomplished' on any level will also count as getting 'Mission Complete' for that level.
  """
  display_name = "Accomplished Sends Complete"

class RadioRando(Choice):
  """
    Randomize the radio dialog.
  """
  display_name = "Radio Rando"
  option_off = 0
  option_on = 1
  option_on_including_training = 2
  default = 1

class EngineGlow(Choice):
  """
    Set the color of your engine's glow.
  """
  display_name = "Engine Glow"
  option_default = 0
  option_rainbow = 1
  option_red = 2
  option_deep_pink = 3
  option_magenta = 4
  option_electric_indigo = 5
  option_blue = 6
  option_dodger_blue = 7
  option_aqua = 8
  option_spring_green = 9
  option_lime = 10
  option_chartreuse = 11
  option_yellow = 12
  option_dark_orange = 13

class DefaultLives(Range):
  """
    Set the number of lives (Arwings) you start with and reset to after a game over.
  """
  display_name = "Default Lives"
  range_start = 0
  range_end = 99
  default = 2

class MedalCorneria(Range):
  """
    Set the score required to earn the medal on Corneria.
  """
  display_name = "Medal Corneria"
  range_start = 0
  range_end = 150
  default = 150

class MedalMeteo(Range):
  """
    Set the score required to earn the medal on Meteo.
  """
  display_name = "Medal Meteo"
  range_start = 0
  range_end = 200
  default = 200

class MedalSectorY(Range):
  """
    Set the score required to earn the medal on Sector Y.
  """
  display_name = "Medal Sector Y"
  range_start = 0
  range_end = 150
  default = 150

class MedalKatina(Range):
  """
    Set the score required to earn the medal on Katina.
  """
  display_name = "Medal Katina"
  range_start = 0
  range_end = 150
  default = 150

class MedalFortuna(Range):
  """
    Set the score required to earn the medal on Fortuna.
  """
  display_name = "Medal Fortuna"
  range_start = 0
  range_end = 50
  default = 50

class MedalAquas(Range):
  """
    Set the score required to earn the medal on Aquas.
  """
  display_name = "Medal Aquas"
  range_start = 0
  range_end = 150
  default = 150

class MedalSolar(Range):
  """
    Set the score required to earn the medal on Solar.
  """
  display_name = "Medal Solar"
  range_start = 0
  range_end = 100
  default = 100

class MedalSectorX(Range):
  """
    Set the score required to earn the medal on Sector X.
  """
  display_name = "Medal Sector X"
  range_start = 0
  range_end = 150
  default = 150

class MedalZoness(Range):
  """
    Set the score required to earn the medal on Zoness.
  """
  display_name = "Medal Zoness"
  range_start = 0
  range_end = 250
  default = 250

class MedalTitania(Range):
  """
    Set the score required to earn the medal on Titania.
  """
  display_name = "Medal Titania"
  range_start = 0
  range_end = 150
  default = 150

class MedalSectorZ(Range):
  """
    Set the score required to earn the medal on Sector Z.
  """
  display_name = "Medal Sector Z"
  range_start = 0
  range_end = 100
  default = 100

class MedalMacbeth(Range):
  """
    Set the score required to earn the medal on Macbeth.
  """
  display_name = "Medal Macbeth"
  range_start = 0
  range_end = 150
  default = 150

class MedalArea6(Range):
  """
    Set the score required to earn the medal on Area 6.
  """
  display_name = "Medal Area 6"
  range_start = 0
  range_end = 300
  default = 300

class MedalBolse(Range):
  """
    Set the score required to earn the medal on Bolse.
  """
  display_name = "Medal Bolse"
  range_start = 0
  range_end = 150
  default = 150

class MedalVenom(Range):
  """
    Set the score required to earn the medal on Venom.
  """
  display_name = "Medal Venom"
  range_start = 0
  range_end = 200
  default = 200

@dataclass
class StarFox64OptionsList:
  deathlink: DeathLink
  ringlink: RingLink
  victory_condition: VictoryCondition
  required_medals: RequiredMedals
  level_access: LevelAccess
  shuffle_starting_level: ShuffleStartingLevel
  shuffle_medals: ShuffleMedals
  shuffle_checkpoints: ShuffleCheckpoints
  accomplished_sends_complete: AccomplishedSendsComplete
  radio_rando: RadioRando
  engine_glow: EngineGlow
  default_lives: DefaultLives
  medal_corneria: MedalCorneria
  medal_meteo: MedalMeteo
  medal_sector_y: MedalSectorY
  medal_katina: MedalKatina
  medal_fortuna: MedalFortuna
  medal_aquas: MedalAquas
  medal_solar: MedalSolar
  medal_sector_x: MedalSectorX
  medal_zoness: MedalZoness
  medal_titania: MedalTitania
  medal_sector_z: MedalSectorZ
  medal_macbeth: MedalMacbeth
  medal_area_6: MedalArea6
  medal_bolse: MedalBolse
  medal_venom: MedalVenom

@dataclass
class StarFox64Options(StarFox64OptionsList, PerGameCommonOptions):
  start_inventory_from_pool: StartInventoryPool
