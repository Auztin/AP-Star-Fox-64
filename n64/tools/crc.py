import sys, itertools

from ntype import uint32, BigStream

def calculate_cic(data: BigStream):
  crc = 0
  for count in range(0x40, 0x1000, 4):
    crc += data.read_int32(count)

  match crc:
    case 0x000000D0027FDF31: return "CIC_NUS_6101"
    case 0x000000CFFB631223: return "CIC_NUS_6101"
    case 0x000000D057C85244: return "CIC_NUS_6102"
    case 0x000000D6497E414B: return "CIC_NUS_6103"
    case 0x0000011A49F60E96: return "CIC_NUS_6105"
    case 0x000000D6D5BE5580: return "CIC_NUS_6106"
    case 0x000001053BC19870: return "CIC_NUS_5167"
    case 0x000000D2E53EF008: return "CIC_NUS_8303"
    case 0x000000D2E53EF39F: return "CIC_NUS_8401"
    case 0x000000D2E53E5DDA: return "CIC_NUS_DDUS"
    case 0x0000000AF3A34BC8: return "CIC_MINI_IPL3"
    case 0x0000007c56242373: return "CIC_NUS_6102"
    case _:
      print("Unknown CIC")
      return ""

def calculate_crc(data: BigStream):
  t0 = t2 = t3 = t4 = t5 = 0
  a0 = a1 = a2 = a3 = 0
  s0 = 0
  v0 = v1 = 0
  length = 0x00100000
  u32 = 0xFFFFFFFF

  cic = calculate_cic(data)

  match cic:
    case "CIC_NUS_6101" | "CIC_NUS_6102": v0 = 0xF8CA4DDC
    case "CIC_NUS_6103": v0 = 0xA3886759
    case "CIC_NUS_6105": v0 = 0xDF26F436
    case "CIC_NUS_6106": v0 = 0x1FEA617A
    case "CIC_NUS_DDUS":
        length = 0x000A0000
        v0 = 0x861AE3A7
    case "CIC_NUS_8303":
        length = 0x000A0000
        v0 = 0x8331D4CA
    case "CIC_NUS_8401":
        length = 0x000A0000
        v0 = 0x0D8303E2
    case "CIC_NUS_5101": v0 = 0x95104FDD
    case _:
        return bytes(0)

  if (cic == "CIC_NUS_5101" and data.read_int32(0x8) == 0x80100400):
      length = 0x003FE000

  v1 = 0
  t0 = 0
  t5 = 0x20

  a3 = v0
  t2 = v0
  t3 = v0
  s0 = v0
  a2 = v0
  t4 = v0

  for t0 in range(0, length, 4):
    v0 = data.read_int32(t0 + 0x1000)

    v1 = (a3 + v0) & u32
    a1 = v1

    if (v1 < a3):
      if (cic == "CIC_NUS_DDUS" or cic == "CIC_NUS_8303"):
        t2 = (t2 ^ t3) & u32
      else:
        t2 += 0x1
    v1 = v0 & 0x001F

    a0 = (v0 << v1) | (v0 >> (t5 - v1)) & u32

    a3 = a1
    t3 = (t3 ^ v0) & u32

    s0 = (s0 + a0) & u32
    if (a2 < v0):
      a2 = (a3 ^ v0 ^ a2) & u32
    else:
      if (cic == "CIC_NUS_8303"):
        a2 = (a2 + a0) & u32
      else:
        a2 = (a2 ^ a0) & u32

    if (cic == "CIC_NUS_6105"):
      t4 = ((v0 ^ (data.read_int32((0xFF & t0) + 0x750))) + t4) & u32
    else:
      t4 = ((v0 ^ s0) + t4) & u32
  if (cic == "CIC_NUS_6103"):
    a3 = ((a3 ^ t2) + t3) & u32
    s0 = ((s0 ^ a2) + t4) & u32
  elif (cic == "CIC_NUS_6106"):
    a3 = (0xFFFFFFFF & (a3 * t2) + t3) & u32
    s0 = (0xFFFFFFFF & (s0 * a2) + t4) & u32
  elif (cic == "CIC_NUS_5101"):
    a3 = (0xFFFFFFFF & (a3 ^ t2) + t3) & u32
    s0 = (0xFFFFFFFF & (s0 ^ a2) + t4) & u32
  else:
    a3 = (a3 ^ t2 ^ t3) & u32
    s0 = (s0 ^ a2 ^ t4) & u32

  crc0 = a3
  crc1 = s0
  return uint32.bytes(crc0) + uint32.bytes(crc1)


with open(sys.argv[1], 'rb') as stream:
  rom = BigStream(bytearray(stream.read()))
  rom.write_bytes(0x20, bytearray("AP STAR FOX 64", "utf-8"))
  crc = calculate_crc(rom)
  rom.write_bytes(0x10, crc)
  with open(sys.argv[1], 'wb') as outfile:
    outfile.write(rom.buffer)
