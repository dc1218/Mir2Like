#include "server.h"
#include "muduo/base/Logging.h"


const char *LoginGateServer::VER_STR = "World of Magic";
int LoginGateServer::MAX_USER = 1000;
int LoginGateServer::MAX_CLIENTRECEIVELENGTH = 300;
int LoginGateServer::MAX_CHECKSENDLENGTH = 512;
int LoginGateServer::MAX_RADDR = 4;
int LoginGateServer::ServerPort = 5500;
int LoginGateServer::GateBasePort = 7000;

LoginGateServer::LoginGateServer(muduo::net::EventLoop *loop, const muduo::net::InetAddress &listenAddr)
    : loop_(loop),
    server_(loop, listenAddr, "LoginGateServer")
{
    server_.setConnectionCallback(
        std::bind(&LoginGateServer::onConnection, this, std::placeholders::_1));
    server_.setMessageCallback(
        std::bind(&LoginGateServer::onMessage, this, std::placeholders::_1, std::placeholders::_2, std::placeholders::_3));
}

void LoginGateServer::start()
{
    server_.start();
}

void LoginGateServer::onConnection(const muduo::net::TcpConnectionPtr &conn)
{
  LOG_TRACE << conn->peerAddress().toIpPort() << " -> "
            << conn->localAddress().toIpPort() << " is "
            << (conn->connected() ? "UP" : "DOWN");
}

void LoginGateServer::onMessage(const muduo::net::TcpConnectionPtr &conn, muduo::net::Buffer *buf, muduo::Timestamp time)
{
  muduo::string msg(buf->retrieveAllAsString());
  LOG_TRACE << conn->name() << " recv " << msg.size() << " bytes at " << time.toString();
  conn->send(msg);
}
