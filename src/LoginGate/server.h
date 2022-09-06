#ifndef __M2L__LOGINGATE_H__
#define __M2L__LOGINGATE_H__

#include "muduo/net/TcpServer.h"
#include "muduo/net/EventLoop.h"
#include "muduo/net/InetAddress.h"

class LoginGateServer
{
public:
  LoginGateServer(muduo::net::EventLoop *loop, const muduo::net::InetAddress &listenAddr);
  void start();
private:
  void onConnection(const muduo::net::TcpConnectionPtr &conn);
  void onMessage(const muduo::net::TcpConnectionPtr &conn, muduo::net::Buffer *buf, muduo::Timestamp time);
  muduo::net::EventLoop *loop_;
  muduo::net::TcpServer server_;
private:
  static const char *VER_STR;
  static int MAX_USER;
  static int MAX_CLIENTRECEIVELENGTH;
  static int MAX_CHECKSENDLENGTH;
  static int MAX_RADDR;
  static int ServerPort;
  static int GateBasePort;
};

#endif