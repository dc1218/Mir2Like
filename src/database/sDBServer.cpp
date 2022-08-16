#include "sDBServer.h"
#include "muduo/base/Logging.h"


#include <sstream>

using namespace muduo;

DBServer::DBServer(EventLoop* loop,const InetAddress& listenAddr)
    :loop_(loop),server_(loop, listenAddr, "DBServer")
{
    LOG_INFO << server_.name() << "开始启动!";
    server_.setConnectionCallback(
        std::bind(&DBServer::onConnection, this, _1));
    server_.setMessageCallback(
        std::bind(&DBServer::onMessage, this, _1, _2, _3));
    
}

DBServer::~DBServer()
{
    LOG_INFO << server_.name() << "停止服务!";
}

bool DBServer::initServer()
{   
    try
    {
        spMysql_ = std::make_shared<UMysql>();
        return true;
    }
    catch(const std::exception& e)
    {
        LOG_ERROR << e.what();
    }
    return false;
}

bool DBServer::run()
{
    try
    {
        if(!initServer())
            throw "初始化服务失败！";

        if(!spMysql_->Connect())
            throw "初始化数据库连接失败！";
        
        server_.start();

        return 0;
    }
    catch(const char* em)
    {
        LOG_ERROR << em;
    }
    catch(const std::exception& e)
    {
        LOG_ERROR << e.what();
    }

    return 1;
}

void DBServer::onConnection(const TcpConnectionPtr& conn)
{
    LOG_TRACE << conn->peerAddress().toIpPort() << " -> "
            << conn->localAddress().toIpPort() << " is "
            << (conn->connected() ? "UP" : "DOWN");
            
    if(!conn->connected())
    {
        LocalConnections::instance().insert(conn);
        LOG_INFO << conn->name() << " connected... now connections count = " << LocalConnections::instance().size();
    }
    else
    {
        LocalConnections::instance().erase(conn);
        LOG_INFO << conn->name() << " disconnected... now connections count = " << LocalConnections::instance().size();   
    }
}

void DBServer::onMessage(const TcpConnectionPtr& conn, Buffer* buf, Timestamp time)
{
    if (conn->connected())
    {
        conn->send(time.toFormattedString());
    }
        
    size_t len = buf->readableBytes();
    LOG_INFO << conn->name() << ' ' << len;
    while (len >= 0 + 2)
    {
        LOG_INFO << "todo";
        break;
    }
}
