import sys, os, math
from contextlib import contextmanager

@contextmanager
def cwd(path):
  oldcwd = os.getcwd()
  os.chdir(path)
  try:
    yield
  finally:
    os.chdir(oldcwd)

class Image:

  def __init__(self):
    self.path = ""
    self.width = 0
    self.height = 0
    self.offset = 0

  def parse(self, dl):
    offset = len(dl.data)
    with open(self.path, 'rb') as file:
      source = bytes(file.read())
      dest = bytearray(b'\0'*(self.width*self.height*2))
      for y in range(self.height):
        for x in range(self.width):
          si = y*self.width+x
          si *= 4
          di = (self.height-y-1)*self.width+x
          di *= 2
          red = source[si]
          green = source[si+1]
          blue = source[si+2]
          alpha = source[si+3]
          red = int(red/255.0*31)
          green = int(green/255.0*31)
          blue = int(blue/255.0*31)
          alpha = 1 if alpha else 0
          pixel = red << 11
          pixel |= green << 6
          pixel |= blue << 1
          pixel |= alpha
          dest[di] = pixel >> 8
          dest[di+1] = pixel & 0xFF
      dl.data += dest

class Group:

  def __init__(self, name):
    self.name = name
    self.triangles = []
    self.n64vertices = []
    self.n64triangles = []
    self.offset = 0

class Material:

  def __init__(self, name):
    self.name = name
    self.image = Image()

class Obj:

  def __init__(self, name):
    self.name = name
    self.vertices = []
    self.normals = []
    self.uvs = []
    self.groups = {}
    self.group = Group("")

class Vertex:

  def __init__(self, x, y, z=0):
    self.x = x
    self.y = y
    self.z = z

class Model:

  def __init__(self, path):
    self.materials = {}
    self.material = Material("")
    self.objs = {}
    self.obj = Obj("NONAME")
    self.group = ""
    with open(path, "r") as file:
      with cwd(os.path.split(path)[0]):
        for line in file.readlines():
          cmd = line[:-1].split(" ")
          match cmd[0]:
            case "mtllib":
              self.parse_mtl(cmd[1])
            case "o":
              obj = cmd[1]
              if obj not in self.objs:
                self.objs[obj] = Obj(obj)
              self.obj = self.objs[obj]
            case "v":
              self.obj.vertices.append(Vertex(float(cmd[1]), float(cmd[2]), float(cmd[3])))
            case "vn":
              self.obj.normals.append(Vertex(float(cmd[1]), float(cmd[2]), float(cmd[3])))
            case "vt":
              self.obj.uvs.append(Vertex(float(cmd[1]), float(cmd[2])))
            case "g":
              self.group = cmd[1]
            case "usemtl":
              self.material = self.materials[cmd[1]]
            case "f":
              if self.material not in self.obj.groups:
                self.obj.groups[self.material] = {}
              group = self.group
              if group not in self.obj.groups[self.material]:
                self.obj.groups[self.material][group] = Group(group)
              self.obj.group = self.obj.groups[self.material][group]
              points = []
              for point in cmd[1:]:
                point = point.split("/")
                points.append(int(point[0]))
                points.append(int(point[1]))
                points.append(int(point[2]))
              self.obj.group.triangles.append(points)

  def parse_mtl(self, path):
    with open(path, "r") as file:
      for line in file.readlines():
        cmd = line[:-1].split(" ")
        match cmd[0]:
          case "newmtl":
            material = cmd[1]
            if material not in self.materials:
              self.materials[material] = Material(material)
            self.material = self.materials[material]
          case "map_Kd":
            image = Image()
            image.path = os.path.abspath(f"{cmd[1]}.data")
            size = os.path.split(cmd[1])[1].split(".")[-2].split("x")
            image.width = int(size[0])
            image.height = int(size[1])
            self.material.image = image

  def output(self, dl):
    for name, material in self.materials.items():
      material.image.parse(dl)
    for obj_name, obj in self.objs.items():
      for material, groups in obj.groups.items():
        for group_name, group in groups.items():
          point_map = {}
          for triangle in group.triangles:
            face = []
            for index in range(0, len(triangle), 3):
              v = triangle[index]
              uv = triangle[index+1]
              n = triangle[index+2]
              if v not in point_map:
                point_map[v] = len(point_map)
                group.n64vertices.append([v, uv, n])
              face.append(point_map[v])
            group.n64triangles.append(face)
          if len(group.n64triangles) % 2:
            group.n64triangles.append([0, 0, 0])
          group.offset = len(dl.data)
          for vertex in group.n64vertices:
            v = obj.vertices[vertex[0]-1]
            uv = obj.uvs[vertex[1]-1]
            n = obj.normals[vertex[2]-1]
            img_size = material.image.width*material.image.height
            dl.data += round(v.x).to_bytes(2, "big", signed=True)
            dl.data += round(v.y).to_bytes(2, "big", signed=True)
            dl.data += round(v.z).to_bytes(2, "big", signed=True)
            dl.data += b"\0\0"
            dl.data += round(uv.x*material.image.width*math.pow(2, 5)).to_bytes(2, "big", signed=True)
            dl.data += round(uv.y*material.image.height*math.pow(2, 5)).to_bytes(2, "big", signed=True)
            dl.data += round(n.x*0x77).to_bytes(1, "big", signed=True)
            dl.data += round(n.y*0x77).to_bytes(1, "big", signed=True)
            dl.data += round(n.z*0x77).to_bytes(1, "big", signed=True)
            dl.data += b"\xFF"
      dl.offsets[obj_name] = len(dl.data)
      for material, groups in obj.groups.items():
        dl.set_image(material.image)
        for group_name, group in groups.items():
          dl.draw_triangles(group)
      dl.end()

class DisplayList:
  segment = 0x0B
  data = bytes()
  offsets = {}

  def set_image(self, image):
    self.data += (0xE8000000).to_bytes(4, "big")
    self.data += (0x00000000).to_bytes(4, "big")
    size = 0xF5100000 # G_SETTILE
    size |= int(image.width/4) << 9
    self.data += size.to_bytes(4, "big")
    self.data += (0x00000000).to_bytes(4, "big")
    self.data += (0xF2000000).to_bytes(4, "big") # G_SETTILESIZE
    size = (image.width-1) << 2
    size <<= 12
    size |= (image.height-1) << 2
    self.data += size.to_bytes(4, "big")
    self.data += (0xFD100000).to_bytes(4, "big") # G_SETTIMG
    self.data += self.segment.to_bytes(1, "big")
    self.data += image.offset.to_bytes(3, "big")
    self.data += (0xE8000000).to_bytes(4, "big")
    self.data += (0x00000000).to_bytes(4, "big")
    self.data += (0xF5100000).to_bytes(4, "big") # G_SETTILE
    self.data += (0x07000000).to_bytes(4, "big")
    self.data += (0xE6000000).to_bytes(4, "big") # G_RDPLOADSYNC
    self.data += (0x00000000).to_bytes(4, "big")
    self.data += (0xF3000000).to_bytes(4, "big") # G_LOADBLOCK
    self.data += b"\x07"
    size = (image.width*image.height-1) << 12
    size |= int(1/(image.width*16/64)*math.pow(2, 11))
    self.data += size.to_bytes(3, "big")

  def draw_triangles(self, group):
    self.data += b"\x04\x00" # G_VTX
    size = len(group.n64vertices)
    size = (size << 10) | (size*0x10-1)
    self.data += size.to_bytes(2, "big")
    self.data += self.segment.to_bytes(1, "big")
    self.data += group.offset.to_bytes(3, "big")
    for index in range(0, len(group.n64triangles), 2):
      for x in range(2):
        if x: self.data += b"\x00"
        else: self.data += b"\xB1" # G_TRI2
        triangle = group.n64triangles[index+x]
        for point in triangle:
          self.data += (point*2).to_bytes(1, "big")

  def end(self):
    self.data += (0xE7000000).to_bytes(4, "big") # G_RDPPIPESYNC
    self.data += (0x00000000).to_bytes(4, "big")
    self.data += (0xB8000000).to_bytes(4, "big") # G_ENDDL
    self.data += (0x00000000).to_bytes(4, "big")

dl = DisplayList()

for path in sys.argv[3:]:
  model = Model(path)
  model.output(dl)

with open(sys.argv[1], "wb") as file:
  file.write(dl.data)

segment = dl.segment << 24
with open(sys.argv[2], "w") as file:
  for name, offset in dl.offsets.items():
    file.write(f"ASSET_{name}:\n")
    file.write(f".word 0x{(segment | offset):X}\n")
