#ifndef __M2L__DBSERVER__H__
#define __M2L__DBSERVER__H__

#include "muduo/net/TcpServer.h"
#include "muduo/net/EventLoop.h"
#include "muduo/net/InetAddress.h"
using namespace muduo;
using namespace muduo::net;

class DBServer
{
public:
    DBServer(EventLoop* loop,const InetAddress& listenAddr);
    ~DBServer();
    void run();
private:
    void onConnection(const TcpConnectionPtr& conn);
    void onMessage(const TcpConnectionPtr& conn, Buffer* buf, Timestamp time);
private:
    EventLoop* loop_;
    TcpServer server_;
};

#endif 