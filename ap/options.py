from dataclasses import dataclass
from Options import PerGameCommonOptions, Choice, Range, Toggle, DefaultOnToggle

class DeathLink(Toggle):
  """
    When you die, everyone who enabled death link dies. Of course, the reverse is true too.
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

@dataclass
class StarFox64OptionsList:
  deathlink: DeathLink
  victory_condition: VictoryCondition
  required_medals: RequiredMedals
  shuffle_medals: ShuffleMedals
  shuffle_paths: ShufflePaths
  accomplished_sends_complete: AccomplishedSendsComplete
  radio_rando: RadioRando
  default_lives: DefaultLives

@dataclass
class StarFox64Options(StarFox64OptionsList, PerGameCommonOptions):
  pass
