local input_ptr = 0x80400000
local output_ptr = 0x80400004
local port = 0x5F64

console.clear()
local socket_loaded, socket = pcall(require, "socket")
if not socket_loaded then
  print("Please place this lua in the 'Archipelago/data/lua' directory. Use the Archipelago Launcher's 'Browse Files' button to find the Archipelago directory.")
  return
end
print("Waiting for ROM to be ready...");
print("Make sure you load the patched ROM and not the vanilla ROM...");

local ready = false
local connection = nil
local connection_time = 0
local socket_buffer = {}

function to_string(bytes)
  local str = {}
  for i, v in ipairs(bytes) do
    str[#str+1] = string.char(v)
  end
  return table.concat(str)
end

function to_bytes(str, bytes)
  if (bytes == nil) then
    bytes = {}
  end
  for v in str:gmatch"." do
    bytes[#bytes+1] = string.byte(v)
  end
  return bytes
end

function slice(bytes, offset, size)
  local sliced = {}
  for i = offset, size, 1 do
    sliced[#sliced+1] = table.remove(bytes, 1)
  end
  return sliced
end

function check_game()
  local input = mainmemory.read_u32_be(input_ptr & 0xFFFFFF)
  local output = mainmemory.read_u32_be(output_ptr & 0xFFFFFF)
  if (not (input ~= nil and output ~= nil and input < 0x80800000 and output < 0x80800000 and input > 0x80000000 and output > 0x80000000)) then
    ready = false
    return
  end
  input = input & 0xFFFFFF
  output = output & 0xFFFFFF
  local size = mainmemory.read_u16_be(output)+2
  local cmd = mainmemory.read_u16_be(output+2)
  if (cmd > 0) then ready = true end
  if (connection == nil) then
    if (cmd == 0) then ready = false end
    return
  end
  if (cmd > 0) then
    connection:send(to_string(mainmemory.read_bytes_as_array(output, size)))
    mainmemory.write_u16_be(output+2, 0)
  end
  if (mainmemory.read_u16_be(input+2) == 0 and #socket_buffer >= 3) then
    size = (socket_buffer[1] << 8 | socket_buffer[2])+2
    if (#socket_buffer >= size) then
      mainmemory.write_bytes_as_array(input, slice(socket_buffer, 1, size))
    end
  end
end

function check_socket()
  if (connection ~= nil and not ready) then
    connection:close()
    connection = nil
    print("Disconnected")
  end
  if (not ready) then return end
  if (connection == nil) then
    if (socket.socket.gettime() - connection_time < 3) then return end
    connection_time = socket.socket.gettime()
    print("Connecting")
    local conn, err = socket.socket.tcp()
    if (not conn) then return end
    conn:settimeout(0)
    local res, err = conn:connect("127.0.0.1", port)
    if (err ~= "timeout") then
      print("Connection error")
      return
    end
    connection = conn
  end
  local read, write, err = socket.socket.select({connection}, {connection}, 0)
  if (err ~= nil) then
    if (socket.socket.gettime() - connection_time > 3) then
      connection:close()
      connection = nil
      print("Connection timeout")
    end
    return
  end
  if (#write > 0 and socket.socket.gettime() - connection_time < 3) then
    connection_time = 0
    socket_buffer = {}
    print("Connected")
  end
  if (#read > 0) then
    while true do
      local data, err, partial = connection:receive(1)
      if (err == "closed") then
        connection = nil
        connection_time = socket.socket.gettime()
        print("Disconnected")
        break
      end
      if (data == nil) then break end
      socket_buffer[#socket_buffer+1] = string.byte(data)
    end
  end
end

while true do
  check_game()
  check_socket()
  emu.frameadvance()
end
