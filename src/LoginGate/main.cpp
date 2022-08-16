#include "muduo/net/TcpServer.h"

#include "muduo/base/AsyncLogging.h"
#include "muduo/base/Logging.h"
#include "muduo/base/Thread.h"
#include "muduo/net/EventLoop.h"
#include "muduo/net/InetAddress.h"

#include <functional>
#include <utility>

#include <stdio.h>
#include <unistd.h>

using namespace muduo;
using namespace muduo::net;

class LoginGateServer
{
 public:
  LoginGateServer(EventLoop* loop, const InetAddress& listenAddr)
    : loop_(loop),
      server_(loop, listenAddr, "LoginGateServer")
  {
    server_.setConnectionCallback(
        std::bind(&LoginGateServer::onConnection, this, _1));
    server_.setMessageCallback(
        std::bind(&LoginGateServer::onMessage, this, _1, _2, _3));
  }

  void start()
  {
    server_.start();
  }

 private:
  void onConnection(const TcpConnectionPtr& conn);

  void onMessage(const TcpConnectionPtr& conn, Buffer* buf, Timestamp time);

  EventLoop* loop_;
  TcpServer server_;
};

void LoginGateServer::onConnection(const TcpConnectionPtr& conn)
{
  LOG_TRACE << conn->peerAddress().toIpPort() << " -> "
            << conn->localAddress().toIpPort() << " is "
            << (conn->connected() ? "UP" : "DOWN");
}

void LoginGateServer::onMessage(const TcpConnectionPtr& conn, Buffer* buf, Timestamp time)
{
  string msg(buf->retrieveAllAsString());
  LOG_TRACE << conn->name() << " recv " << msg.size() << " bytes at " << time.toString();
  conn->send(msg);
}

int kRollSize = 500*1000*1000;

std::unique_ptr<muduo::AsyncLogging> g_asyncLog;

void asyncOutput(const char* msg, int len)
{
  g_asyncLog->append(msg, len);
}

void setLogging(const char* argv0)
{
  muduo::Logger::setOutput(asyncOutput);
  char name[256];
  strncpy(name, argv0, 256);
  g_asyncLog.reset(new muduo::AsyncLogging(::basename(name), kRollSize));
  g_asyncLog->start();
}

int main(int argc, char* argv[])
{
  setLogging(argv[0]);

  LOG_INFO << "pid = " << getpid() << ", tid = " << CurrentThread::tid();
  EventLoop loop;
  InetAddress listenAddr(7000);
  LoginGateServer server(&loop, listenAddr);

  server.start();

  loop.loop();
}