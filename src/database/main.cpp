#include "DBServer.h"

int main(int argc, char* argv[])
{

  EventLoop loop;
  InetAddress listenAddr(2017);
  DBServer server(&loop, listenAddr);

  server.run();

  loop.loop();
}