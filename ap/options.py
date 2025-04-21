from dataclasses import dataclass
from Options import PerGameCommonOptions, Choice, Range, Toggle, DefaultOnToggle

class DeathLink(Toggle):
  """
    When you die, everyone who enabled death link dies. Of course, the reverse is true too.
  """

class RingLink(Toggle):
  """
    Enable Ring Link for use with games that support it. Incoming rings are converted to the current level's Hit counter.
  """

class VictoryCondition(Choice):
  """
    Choose your victory condition.
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

class ShuffleMedals(Toggle):
  """
    Shuffle the medals awarded by reaching a certain number of Hits in each level.
    Earning a medal will give a random item, and you will visually see the medal on the map to indicate that you've completed the check.
  """
  display_name = "Shuffle Medals"

class ShufflePaths(DefaultOnToggle):
  """
    Shuffle the paths between levels.
    Completing a level a certain way will give a random item. You cannot take the path that normally unlocks until you receive that path item.
    For example: Getting 'Mission Complete' on Corneria will give a random item. However, you cannot go to Meteo until you receive 'Corneria - Blue Path'
  """
  display_name = "Shuffle Paths"

class AccomplishedSendsComplete(Toggle):
  """
    Getting 'Mission Accomplished' on any level will also count as getting 'Mission Complete' for that level.
  """
  display_name = "Shuffle Paths"

class RadioRando(Toggle):
  """
    Randomize the radio dialog.
  """

class DefaultLives(Range):
  """
    Set the number of lives (Arwings) you start with and reset to after a game over.
  """
  range_start = 0
  range_end = 99
  default = 2

class MedalCorneria(Range):
  """
    Set the score required to earn the medal on Corneria.
  """
  range_start = 0
  range_end = 150
  default = 150

class MedalMeteo(Range):
  """
    Set the score required to earn the medal on Meteo.
  """
  range_start = 0
  range_end = 200
  default = 200

class MedalSectorY(Range):
  """
    Set the score required to earn the medal on Sector Y.
  """
  range_start = 0
  range_end = 150
  default = 150

class MedalKatina(Range):
  """
    Set the score required to earn the medal on Katina.
  """
  range_start = 0
  range_end = 150
  default = 150

class MedalFortuna(Range):
  """
    Set the score required to earn the medal on Fortuna.
  """
  range_start = 0
  range_end = 50
  default = 50

class MedalAquas(Range):
  """
    Set the score required to earn the medal on Aquas.
  """
  range_start = 0
  range_end = 150
  default = 150

class MedalSolar(Range):
  """
    Set the score required to earn the medal on Solar.
  """
  range_start = 0
  range_end = 100
  default = 100

class MedalSectorX(Range):
  """
    Set the score required to earn the medal on Sector X.
  """
  range_start = 0
  range_end = 150
  default = 150

class MedalZoness(Range):
  """
    Set the score required to earn the medal on Zoness.
  """
  range_start = 0
  range_end = 250
  default = 250

class MedalTitania(Range):
  """
    Set the score required to earn the medal on Titania.
  """
  range_start = 0
  range_end = 150
  default = 150

class MedalSectorZ(Range):
  """
    Set the score required to earn the medal on Sector Z.
  """
  range_start = 0
  range_end = 100
  default = 100

class MedalMacbeth(Range):
  """
    Set the score required to earn the medal on Macbeth.
  """
  range_start = 0
  range_end = 150
  default = 150

class MedalArea6(Range):
  """
    Set the score required to earn the medal on Area 6.
  """
  range_start = 0
  range_end = 300
  default = 300

class MedalBolse(Range):
  """
    Set the score required to earn the medal on Bolse.
  """
  range_start = 0
  range_end = 150
  default = 150

class MedalVenom(Range):
  """
    Set the score required to earn the medal on Venom.
  """
  range_start = 0
  range_end = 200
  default = 200

@dataclass
class StarFox64OptionsList:
  deathlink: DeathLink
  ringlink: RingLink
  victory_condition: VictoryCondition
  required_medals: RequiredMedals
  shuffle_medals: ShuffleMedals
  shuffle_paths: ShufflePaths
  accomplished_sends_complete: AccomplishedSendsComplete
  radio_rando: RadioRando
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
  pass
