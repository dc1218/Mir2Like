#include "sDBServer.h"

#include "muduo/base/AsyncLogging.h"
#include "muduo/base/Logging.h"
#include "muduo/base/Timestamp.h"

using namespace muduo;
using namespace muduo::net;

int kRollSize = 500*1000*1000;

std::unique_ptr<muduo::AsyncLogging> g_asyncLog;

void asyncOutput(const char* msg, int len)
{
  g_asyncLog->append(msg, len);
}

void setLogging(const char* argv0)
{
  char name[256];
  strncpy(name, argv0, 256);
  g_asyncLog.reset(new muduo::AsyncLogging(::basename(name), kRollSize));
  g_asyncLog->start();
  muduo::Logger::setOutput(asyncOutput);
}

int main(int argc, char* argv[])
{
  //setLogging("DBServer");//file mode

  EventLoop loop;

  InetAddress listenAddr(6000);

  DBServer server(&loop, listenAddr);

  if(!server.run())
    loop.loop();

  return 0;
}