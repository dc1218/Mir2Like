#include "DBServer.h"


DBServer::DBServer(EventLoop* loop,const InetAddress& listenAddr)
    :loop_(loop),server_(loop, listenAddr, "DBServer")
{
    server_.setConnectionCallback(
        std::bind(&DBServer::onConnection, this, _1));
    server_.setMessageCallback(
        std::bind(&DBServer::onMessage, this, _1, _2, _3));
}

DBServer::~DBServer()
{

}

void DBServer::run()
{
    server_.start();
}

void DBServer::onConnection(const TcpConnectionPtr& conn)
{

}

void DBServer::onMessage(const TcpConnectionPtr& conn, Buffer* buf, Timestamp time)
{

}

