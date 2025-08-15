#include "Server.h"

#include "EventLoop.h"
#pragma comment(lib, "ws2_32.lib")

int main() {
  EventLoop *loop = new EventLoop();
  Server *server = new Server(loop);
  loop->Loop();
  delete server;
  delete loop;
  return 0;
}
