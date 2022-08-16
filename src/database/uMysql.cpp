#include "muduo/base/Logging.h"
#include "uMysql.h"
#include "yaml-cpp/yaml.h"
#include <fstream>

UMysql::UMysql()
{
    LoadConfig();
}

UMysql::~UMysql()
{
    DisConnect();
}

void UMysql::LoadConfig()
{
    // load yaml file
    try
    {
        std::string filename = "config.yaml";
        std::ifstream f(filename);
        if(!f)
        {
            std::ofstream nf(filename);
            nf.close();
        }

        // local variable
        auto config = YAML::LoadFile(filename);
        if(!config["mysql"])
        {
            config["mysql"]["host"] = "remotemysql.com";
            config["mysql"]["user"] = "ZKJ0j9WAjP";
            config["mysql"]["passwd"] = "sdI0S9ayJz";
            config["mysql"]["database"] = "ZKJ0j9WAjP";
            config["mysql"]["port"] = 3306;
            std::ofstream out(filename);
            out << config;
            out.close();
        }
        // mysql information
        host_ = config["mysql"]["host"].as<std::string>();
        user_ = config["mysql"]["user"].as<std::string>();
        passwd_ = config["mysql"]["passwd"].as<std::string>();
        database_ = config["mysql"]["database"].as<std::string>();
        port_ = config["mysql"]["port"].as<int>();
    }
    catch(const std::exception& e)
    {
        LOG_INFO << e.what();
    }
}

bool UMysql::Connect()
{
    try
    {
        mysql_init(&sqlCon_);
        if (!mysql_real_connect(&sqlCon_,host_.c_str(),user_.c_str(),passwd_.c_str(),database_.c_str(),port_,NULL, 0))
        {
            LOG_ERROR << "数据库连接失败：" << mysql_error(&sqlCon_);
            return false;
        }
        LOG_INFO << "数据库连接成功！";
        return true;
    }
    catch (const std::exception &e)
    {
        LOG_ERROR << "数据库连接失败!" << e.what();
        return false;
    }
}

bool UMysql::DisConnect()
{
    mysql_close(&sqlCon_);
    LOG_INFO << "断开数据库连接!";
    return true;
}

bool UMysql::Query(const char *sql)
{
    int ret = mysql_query(&sqlCon_, sql);
    if (ret)
    {
        LOG_ERROR << mysql_errno(&sqlCon_) << ":" << mysql_error(&sqlCon_);
        return false;
    }
    LOG_DEBUG << sql;
    return true;
}

std::shared_ptr<MYSQL_RES> UMysql::Execute(const char *sql)
{
    result_.reset();
    if(Query(sql))
    {
        MYSQL_RES* result = mysql_store_result(&sqlCon_);
        if(result)
            result_.reset(result ,[](MYSQL_RES* res){ mysql_free_result(res); });
    }
    return result_;
}

uint64_t UMysql::RowCount()
{
    if(result_)
        return mysql_num_rows(result_.get());
    else
        return 0;
}

MYSQL_ROW UMysql::Row()
{
    if(result_)
        return mysql_fetch_row(result_.get());
    else
        return MYSQL_ROW();
}