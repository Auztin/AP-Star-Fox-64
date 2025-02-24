import colorama, asyncio, bsdiff4, pathlib, os, Utils, hashlib, sys, zipfile
import worlds.LauncherComponents as LauncherComponents
from CommonClient import CommonContext, get_base_parser, server_loop, gui_enabled, logger
from NetUtils import ClientStatus

from .version import version
from .ids import option_name_to_id, location_name_to_id, AP_CMD, AP_STATE

patch_md5: str = "2d8101d76ea62ec9b3e01818f78a2c2f"
game_name = "Star Fox 64"
vanilla_version = "v1.1"
patch_name = f"{game_name} AP v{version.major}.{version.minor}.{version.build}.z64"

def read_file(path):
  with open(path, "rb") as fi:
    data = fi.read()
  return data

def write_file(path, data):
  with open(path, "wb") as fi:
    fi.write(data)

def open_world_file(resource: str, mode: str = "rb", encoding: str = None):
  filename = sys.modules[__name__].__file__
  apworldExt = ".apworld"
  game = "star_fox_64/"
  if apworldExt in filename:
    zip_path = pathlib.Path(filename[:filename.index(apworldExt) + len(apworldExt)])
    with zipfile.ZipFile(zip_path) as zf:
      zipFilePath = game + resource
      if mode == "rb":
        return zf.open(zipFilePath, "r")
      else:
        return io.TextIOWrapper(zf.open(zipFilePath, "r"), encoding)
  else:
    return open(os.path.join(pathlib.Path(__file__).parent, resource), mode, encoding=encoding)

def patch_rom(rom_path, dst_path, patch_path):
  rom = read_file(rom_path)
  md5 = hashlib.md5(rom).hexdigest()
  if (md5 == "ef9a76901153f66123dafccb0c13cd94"): # byte swapped
    swapped = bytearray(b'\0'*len(rom))
    for i in range(0, len(rom), 2):
      swapped[i] = rom[i+1]
      swapped[i+1] = rom[i]
    rom = bytes(swapped)
  elif (md5 != "741a94eee093c4c8684e66b89f8685e8"):
    logger.error("Unknown ROM!")
    return
  patch = open_world_file(patch_path).read()
  write_file(dst_path, bsdiff4.patch(rom, patch))

async def check_patch():
  fpath = pathlib.Path(__file__)
  archipelago_root = None
  for i in range(0, 5, 1) :
    if fpath.parents[i].stem == "Archipelago":
      archipelago_root = pathlib.Path(__file__).parents[i]
      break
  patch_path = None
  if archipelago_root:
    patch_path = os.path.join(archipelago_root, patch_name)
  existing_md5 = None
  if os.path.isfile(patch_path):
    rom = read_file(patch_path)
    existing_md5 = hashlib.md5(rom).hexdigest()
  await asyncio.sleep(0.01)
  if not patch_path or existing_md5 != patch_md5:
    rom = Utils.open_filename(f"Open your {game_name} {vanilla_version} ROM", (("Rom Files", (".z64", ".n64")), ("All Files", "*"),))
    if not rom:
      logger.info(f"No ROM selected. Please restart the {game_name} Client to try again.")
      return
    if not patch_path:
      patch_path = f"{os.path.split(rom)}/{patch_name}"
    patch_rom(rom, patch_path, f"{game_name.replace(" ", "_")}.patch")
  if patch_path:
    logger.info(f"Patched {game_name} is located here: {patch_path}")

class StarFox64Context(CommonContext):
  tags = CommonContext.tags
  game = "Star Fox 64"
  items_handling = 0b111
  want_slot_data = True

  seed_name = 0

  slot_data = {}
  n64_sockets = set()

  def make_gui(self):
    from kvui import GameManager

    class StarFox64Manager(GameManager):
      base_title = f"Star Fox 64 Client {version.as_string()} | AP"

    asyncio.create_task(check_patch())

    return StarFox64Manager

  async def server_auth(self, password_requested=False):
    if password_requested and not self.password:
      await super().server_auth(password_requested)
    await self.get_username()
    await self.send_connect()

  async def disconnect(self, allow_autoreconnect: bool = False):
    seed_name = 0
    await super().disconnect(allow_autoreconnect)

  async def check_assert(self, condition, title, message):
    if not condition:
      self.gui_error(title, message)
      await self.disconnect()
      raise AssertionError(f"{title}: {message}")

  def on_package(self, cmd, args):
    asyncio.create_task(self.on_cmd(cmd, args))

  async def on_cmd(self, cmd, args):
    try:
      match cmd:
        case "RoomInfo":
          self.seed_name = args["seed_name"]
          self.n64_send_seed()
        case "RoomUpdate":
          await self.n64_send_checked_locations(locations=set(args["checked_locations"]))
        case "Connected":
          await self.check_assert("slot_data" in args, "Missing Slot Data", "Necessary data is missing from this slot...")
          self.slot_data = args["slot_data"]
          await self.check_assert(version.as_u32() == self.slot_data["version"], "Version Mismatch", "The client version does not match the generated version.")
          self.n64_send_slot_data()
          self.n64_send_checked_locations()
        case "ReceivedItems":
          self.n64_send_items(items=args["items"])
        # case "PrintJSON":
        #   match args["type"]:
        #     case "ItemSend" | "ItemCheat":
        #       print(f"  receiving: {args["receiving"]}")
        #       print(f"  item: {args["item"]}") # item.item, item.player
    except AssertionError as e:
      logger.error(e)

  def n64_send_seed(self, writer=None):
    if self.seed_name == None: return
    send = AP_CMD.SEED.to_bytes(2)
    send += self.seed_name.encode()
    self.n64_send(send, writer)

  def n64_send_slot_data(self, writer=None):
    if self.seed_name == None: return
    send = bytes()
    for name, value in self.slot_data["options"].items():
      send += option_name_to_id[name].to_bytes(1)
      send += value.to_bytes(1)
    self.n64_split_and_send(AP_CMD.OPTIONS.to_bytes(2), send, 2, writer)

  def n64_send_checked_locations(self, writer=None, locations=None):
    if self.seed_name == None: return
    if not locations: locations = self.checked_locations
    send = bytes()
    for location in locations:
      send += location.to_bytes(4)
    self.n64_split_and_send(AP_CMD.LOCATIONS.to_bytes(2), send, 4, writer)

  def n64_send_items(self, writer=None, items=None):
    if self.seed_name == None: return
    if not items: items = self.items_received
    send = bytes()
    for item in items:
      send += item.item.to_bytes(4)
    self.n64_split_and_send(AP_CMD.ITEMS.to_bytes(2), send, 4, writer)

  def n64_send(self, send, writer=None):
    send = len(send).to_bytes(2) + send
    writers = self.n64_sockets
    if writer: writers = {writer}
    for n64 in writers:
      n64.write(send)

  def n64_split_and_send(self, cmd, send, element_size, writer=None):
    max_packet_size = 510 # not including cmd
    size = max_packet_size - max_packet_size % element_size
    for idx in range(0, len(send), size):
      self.n64_send(cmd + send[idx:idx+size], writer)

class N64Socket:

  @classmethod
  async def create(cls, reader, writer, ctx):
    self = cls()
    self.reader = reader
    self.writer = writer
    self.ctx = ctx
    self.ping = True
    self.state = AP_STATE.DISCONNECTED
    logger.info(f"[N64] Connecting")
    asyncio.create_task(self.ping_loop())
    await self.loop()
    self.ping = False
    ctx.n64_sockets -= {writer}
    writer.close()
    await writer.wait_closed()
    logger.info(f"[N64] Disconnected")
    return self

  async def loop(self):
    try:
      while not self.reader.at_eof():
        size = int.from_bytes(await self.reader.readexactly(2))-2
        if size < 0 or size > 512:
          logger.error(f"[N64] Invalid packet")
          return
        cmd = int.from_bytes(await self.reader.readexactly(2))
        data = b""
        if size:
          data = await self.reader.readexactly(size)
        match self.state & ~AP_STATE.PINGED:
          case AP_STATE.DISCONNECTED:
            match cmd:
              case AP_CMD.HANDSHAKE:
                v = int.from_bytes(data[:4])
                if v != version.as_u32():
                  logger.error(f"[N64] ROM Version Mismatch: {hex(version.as_u32())} (client) vs {hex(v)} (ROM)")
                  return
                if data[4:] != b"HELO":
                  logger.error(f"[N64] Unexpected packet")
                  return
                send = AP_CMD.HANDSHAKE.to_bytes(2)
                send += v.to_bytes(4)
                send += b"'LO!"
                self.ctx.n64_send(send, self.writer)
                self.state = AP_STATE.CONNECTING
          case AP_STATE.CONNECTING:
            match cmd:
              case AP_CMD.PING:
                self.ctx.n64_send(AP_CMD.PONG.to_bytes(2), self.writer)
                self.state = AP_STATE.CONNECTED
                self.ctx.n64_send_seed(self.writer)
                self.ctx.n64_send_slot_data(self.writer)
                self.ctx.n64_send_checked_locations(self.writer)
                self.ctx.n64_send_items(self.writer)
                self.ctx.n64_sockets.add(self.writer)
                logger.info(f"[N64] Connected")
          case AP_STATE.CONNECTED:
            self.state &= ~AP_STATE.PINGED
            match cmd:
              case AP_CMD.PING:
                self.ctx.n64_send(AP_CMD.PONG.to_bytes(2), self.writer)
              case AP_CMD.LOCATIONS:
                locations = set()
                for idx in range(0, len(data), 4):
                  location = int.from_bytes(data[idx:idx+4])
                  if location == location_name_to_id["Goal Completed"]:
                    self.ctx.finished_game = True
                    await self.ctx.send_msgs([{"cmd": "StatusUpdate", "status": ClientStatus.CLIENT_GOAL}])
                  else:
                    locations.add(location)
                await self.ctx.send_msgs([{"cmd": 'LocationChecks', "locations": tuple(locations)}])
                pass
              case _:
                logger.error(f"[N64] Unexpected packet: {cmd}")
                return
    except asyncio.IncompleteReadError:
      pass

  async def ping_loop(self):
    while self.ping:
      await asyncio.sleep(5)
      if self.writer.is_closing():
        return
      if self.state & AP_STATE.PINGED:
        logger.info(f"[N64] Ping timeout")
        self.writer.close()
        await self.writer.wait_closed()
        return
      else:
        self.state |= AP_STATE.PINGED

def run(*args):

  async def main(args):
    ctx = StarFox64Context(args.connect, args.password)
    ctx.auth = args.name
    if gui_enabled:
      ctx.run_gui()
    ctx.run_cli()
    try:
      await asyncio.start_server(lambda r, w: N64Socket.create(r, w, ctx), port=0x5F64)
    except OSError:
      logger.error("[N64] Unable to open port 24420")
    await ctx.exit_event.wait()
    await ctx.shutdown()

  parser = get_base_parser(description="Star Fox 64 Archipelago Client.")
  parser.add_argument('--name', default=None, help="Slot Name to connect as.")
  parser.add_argument("url", nargs="?", help="Archipelago connection url")
  args = parser.parse_args(args)
  if args.url:
    url = urllib.parse.urlparse(args.url)
    if url.scheme == "archipelago":
      args.connect = url.netloc
      if url.username:
        args.name = urllib.parse.unquote(url.username)
      if url.password:
        args.password = urllib.parse.unquote(url.password)
    else:
      parser.error(f"bad url, found {args.url}, expected url in form of archipelago://archipelago.gg:38281")

  colorama.init()
  asyncio.run(main(args))
  colorama.deinit()

if __name__ == '__main__':
  run(*sys,argv[1:])
