#include <log4cpp/Category.hh>
#include <log4cpp/PatternLayout.hh>
#include <log4cpp/FileAppender.hh>

int main(){
    //创建一个文件 appender，并设置日志格式
    log4cpp::FileAppender* fileAppender = new log4cpp::FileAppender("FileAppender", "logs/mylog.log");
    log4cpp::PatternLayout* layout = new log4cpp::PatternLayout();
    layout->setConversionPattern("[%d{%Y-%m-%d %H:%M:%S}] [%p] %c: %m%n");
    fileAppender->setLayout(layout);

    //获取Category对象，并设置日志级别和appender
    log4cpp::Category& root = log4cpp::Category::getRoot();
    root.setAppender(fileAppender);
    root.setPriority(log4cpp::Priority::DEBUG);

    //使用日志
    root.emerg(u8"EMERG 0	紧急，系统不可用（最严重错误）");
    root.fatal(u8"FATAL	0	紧急，系统不可用（最严重错误）");
    root.alert(u8"ALERT	100	警报，需要立刻处理的事件");
    root.crit(u8"CRIT	200	严重错误，重要模块故障");
    root.error(u8"ERROR	300	一般性错误，程序可以继续运行但有问题");
    root.warn(u8"WARN	400	警告，有潜在问题但暂时不影响运行");
    root.notice(u8"NOTICE	500	注意，正常但重要的事件");
    root.info(u8"INFO	600	信息，普通运行信息，比如启动/停止服务");
    root.debug(u8"DEBUG	700	调试信息，开发阶段详细信息");
    log4cpp::Category::shutdown();
    return 0;
}