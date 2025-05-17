import typing

class StarFox64Version(typing.NamedTuple):
  major: int
  minor: int
  build: int

  def as_string(self) -> str:
    return ".".join(str(item) for item in self)

  def as_u32(self) -> int:
    return (self.major << 16) | (self.minor << 8) | self.build

version = StarFox64Version(0, 4, 1)
