#ifndef __M2L__DBSERVER__H__
#define __M2L__DBSERVER__H__

#include <set>

#include "muduo/net/TcpServer.h"
#include "muduo/net/EventLoop.h"
#include "muduo/net/InetAddress.h"

#include "muduo/base/ThreadLocalSingleton.h"

#include "uMysql.h"

using namespace muduo;
using namespace muduo::net;


class DBServer
{
public:
    DBServer(EventLoop* loop,const InetAddress& listenAddr);
    ~DBServer();
    bool run();
    bool initServer();
private:
    void onConnection(const TcpConnectionPtr& conn);
    void onMessage(const TcpConnectionPtr& conn, Buffer* buf, Timestamp time);
private:
    EventLoop* loop_;
    TcpServer server_;
private:
    std::shared_ptr<UMysql> spMysql_;
    typedef std::set<TcpConnectionPtr> ConnectionList;
    typedef ThreadLocalSingleton<ConnectionList> LocalConnections;
};

#endif 