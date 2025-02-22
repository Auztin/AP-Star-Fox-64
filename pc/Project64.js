var input_ptr = 0x80400000
var output_ptr = 0x80400004
var port = 0x5F64

console.clear()
console.log("Waiting for ROM to be ready...");
console.log("Make sure you load the patched ROM and not the vanilla ROM...");

var ready = false;
var connection = null;
var socket_buffer = new Buffer(0);

function check_game() {
  var input = mem.u32[input_ptr];
  var output = mem.u32[output_ptr];
  if (!(input && output && input < 0x80800000 && output < 0x80800000 && input > 0x80000000 && output > 0x80000000)) {
    ready = false;
    return;
  }
  var size = mem.u16[output]+2;
  var cmd = mem.u16[output+2];
  if (cmd) ready = true;
  if (!connection) {
    if (!cmd) ready = false;
    return;
  }
  if (cmd) {
    connection.write(mem.getblock(output, 512).slice(0, size));
    mem.u16[output+2] = 0;
  }
  if (!mem.u16[input+2] && socket_buffer.length >= 3) {
    size = socket_buffer.readUInt16BE()+2;
    if (socket_buffer.length >= size) {
      mem.setblock(input, socket_buffer.slice(0, size));
      socket_buffer = socket_buffer.slice(size);
    }
  }
}
check_game();
setInterval(check_game, 50);

function check_socket() {
  if (connection && !ready) connection.close();
  if (connection || !ready) return;
  console.log("Connecting");
  connection = new Socket();
  connection.on("error", function (error) {
    console.log("Connection error");
    connection = null;
  });
  connection.connect(port, "127.0.0.1", function() {
    console.log("Connected");
    socket_buffer = new Buffer(0);
    connection.on("data", function (data) {
      socket_buffer = Buffer.concat([socket_buffer, data]);
    });
    connection.on("close", function() {
      connection = null;
      console.log("Disconnected");
    });
  });
}
check_socket();
setInterval(check_socket, 3000);
