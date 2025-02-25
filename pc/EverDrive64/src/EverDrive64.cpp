#include <stdio.h>
#include <asio.hpp>
#include <ftd2xx.h>
#include <queue>

using namespace std;

int port = 0x5F64;

class Connection;

class Connection {
public:
  asio::io_context* ctx;
  asio::ip::tcp::socket socket;
  asio::ip::tcp::resolver resolver;
  bool connected = false;
  queue<uint8_t> buffer;

  Connection(asio::io_context* ctx):
    socket(*ctx),
    resolver(*ctx) {
    this->ctx = ctx;
  }

  void connection_error() {
    printf("Connection error\n");
    if (connected) socket.close();
    connected = false;
  }

  void connect() {
    printf("Connecting\n");
    resolver.async_resolve("127.0.0.1", to_string(port), [this](auto error, auto results) {
      if (error) connection_error();
      else asio::async_connect(socket, results, [this](auto error, auto endpoint) {
        if (error) connection_error();
        else {
          connected = true;
          printf("Connected\n");
          buffer = {};
          asio::co_spawn(*ctx, receive(), asio::detached);
        }
      });
    });
  }

  void send(uint8_t* bytes) {
    if (!connected) {
      connect();
      return;
    }
    int size = (bytes[0] << 8) | bytes[1];
    uint8_t data[512];
    memcpy(data, bytes, size+2);
    asio::async_write(socket, asio::buffer(bytes, size+2), [this, size, data](auto error, auto transferred) {
      if (error || transferred != size+2) connection_error();
    });
  }

  asio::awaitable<void> receive() {
    asio::error_code error;
    int received;
    while (connected) {
      uint8_t buf[512];
      received = co_await socket.async_receive(asio::buffer(buf, 2), asio::redirect_error(asio::use_awaitable, error));
      if (error || received != 2) {
        connection_error();
        break;
      }
      int size = (buf[0] << 8) | buf[1];
      if (size > 510) {
        connection_error();
        break;
      }
      received = co_await socket.async_receive(asio::buffer(buf+2, size), asio::redirect_error(asio::use_awaitable, error));
      if (error || received != size) {
        connection_error();
        break;
      }
      for (int i = 0; i < received+2; i++) buffer.push(buf[i]);
    }
  }
};
Connection* connection;

class Game {
public:
  asio::steady_timer timer;
  FT_HANDLE handle;
  bool ready = false;
  typedef union {
    struct {
      uint8_t header[8];
      uint8_t extra[504];
    };
    uint8_t raw[512];
  } packet_t;

  Game(asio::io_context* ctx):
    timer(*ctx) {
    check();
  }

  void check() {
    int wait = (int)(1/60.0*1000);
    if (read() != FT_OK) {
      FT_Close(handle);
      if (open() != FT_OK) wait = 1000;
    }
    else if (process() != FT_OK) {
      connection->connection_error();
      FT_Close(handle);
      if (open() != FT_OK) wait = 1000;
    }

    timer.expires_after(std::chrono::milliseconds(wait));
    timer.async_wait([this](const asio::error_code& error) {
      if (!error) check();
    });
  }

  FT_STATUS open() {
    uint8_t opened = 0;
    DWORD devices;
    if (FT_CreateDeviceInfoList(&devices) != FT_OK) return FT_OTHER_ERROR;
    if (devices) {
      FT_DEVICE_LIST_INFO_NODE dev_info[devices];
      if (FT_GetDeviceInfoList(dev_info, &devices) != FT_OK) return FT_OTHER_ERROR;
      for (DWORD i = 0; i < devices; i++) {
        if (!strcmp(dev_info[i].Description, "FT245R USB FIFO") && dev_info[i].ID == 0x4036001) {
          if (FT_Open(i, &handle) != FT_OK) return FT_OTHER_ERROR;
          opened = 1;
          FT_ResetDevice(handle);
          FT_SetTimeouts(handle, 10000, 10000);
          FT_Purge(handle, FT_PURGE_RX | FT_PURGE_TX);
        }
      }
    }
    if (!opened) return FT_OTHER_ERROR;
    return FT_OK;
  }

  FT_STATUS read() {
    packet_t packet;
    FT_STATUS status;
    DWORD pending = 0;
    DWORD size = 0;
    status = FT_GetQueueStatus(handle, &pending);
    if (pending >= 8) {
      if (FT_Read(handle, packet.raw, 8, &size) != FT_OK || size != 8) return FT_OTHER_ERROR;
      int packet_size = ((packet.raw[0] << 8) | packet.raw[1])-6;
      if (packet_size > 0) {
        packet_size--;
        packet_size = packet_size-packet_size%4+4;
        if (packet_size > 504) return FT_OTHER_ERROR;
        if (FT_Read(handle, packet.extra, packet_size, &size) != FT_OK || size != packet_size) return FT_OTHER_ERROR;
      }
      connection->send(packet.raw);
    }
    else if (pending > 0) FT_Purge(handle, FT_PURGE_RX);
    return status;
  }

  FT_STATUS write(uint8_t* packet) {
    DWORD size;
    int packet_size = ((packet[0] << 8) | packet[1])+2;
    if (packet_size < 8) packet_size = 8;
    else if (packet_size) {
      packet_size--;
      packet_size = packet_size-packet_size%4+4;
    }
    return (FT_Write(handle, packet, packet_size, &size) != FT_OK || size != packet_size) ? FT_OTHER_ERROR : FT_OK;
  }

  FT_STATUS process() {
    if (!connection->connected || connection->buffer.empty()) return FT_OK;
    packet_t packet;
    packet.raw[0] = connection->buffer.front();
    connection->buffer.pop();
    packet.raw[1] = connection->buffer.front();
    connection->buffer.pop();
    int size = (packet.raw[0] << 8) | packet.raw[1];
    for (int i = 0; i < size; i++) {
      packet.raw[i+2] = connection->buffer.front();
      connection->buffer.pop();
    }
    return write(packet.raw);
  }
};

int main() {
  asio::io_context ctx;
  Connection c(&ctx);
  connection = &c;
  Game g(&ctx);
  ctx.run();
  return 0;
}
