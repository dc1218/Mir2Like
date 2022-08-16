#ifndef __UMYSQL_H__
#define __UMYSQL_H__

#include <mysql/mysql.h>
#include <memory>

class UMysql
{
public:  
    UMysql();
    ~UMysql();
public:
    void LoadConfig();
    bool Connect();
    bool DisConnect();
    bool Query(const char* sql);
    std::shared_ptr<MYSQL_RES> Execute(const char* sql); 
    uint64_t RowCount();
    MYSQL_ROW Row();
private:
    MYSQL sqlCon_;
    std::shared_ptr<MYSQL_RES> result_;
    std::string host_;
    std::string user_;
    std::string passwd_;
    std::string database_;
    int port_;
};

#endif