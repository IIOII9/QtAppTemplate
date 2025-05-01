#include <log4cpp/Category.hh>
#include <log4cpp/PropertyConfigurator.hh>
#include <iostream>

void networkModuleTask() {
    log4cpp::Category& logger = log4cpp::Category::getInstance("network");
    logger.info("Network connection established");
    logger.warn("Network latency high");
}

void databaseModuleTask() {
    log4cpp::Category& logger = log4cpp::Category::getInstance("database");
    logger.info("Database query executed");
    logger.error("Database connection lost");
}

int main() {
    try {
        // 加载配置文件
        log4cpp::PropertyConfigurator::configure("log4cpp.conf");
    } catch (log4cpp::ConfigureFailure& e) {
        std::cerr << "配置失败: " << e.what() << std::endl;
        return 1;
    }

    // 获取不同模块的logger
    log4cpp::Category& rootLogger = log4cpp::Category::getRoot();
    log4cpp::Category& networkLogger = log4cpp::Category::getInstance("network");
    log4cpp::Category& databaseLogger = log4cpp::Category::getInstance("database");

    // 记录日志
    rootLogger.info("Application started");
    networkModuleTask();
    databaseModuleTask();
    rootLogger.info("Application shutting down");

    // 清理日志系统
    log4cpp::Category::shutdown();
    return 0;
}