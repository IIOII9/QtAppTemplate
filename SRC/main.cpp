#include <QApplication>
#include "mainwindow.h"

#include <log4cpp/Category.hh>
#include <log4cpp/FileAppender.hh>
#include <log4cpp/BasicLayout.hh>

int main(int argc, char *argv[]) {
    QApplication a(argc, argv);
    log4cpp::FileAppender* fileAppender = new log4cpp::FileAppender("fileAppender", "mylog.txt");
    fileAppender->setLayout(new log4cpp::BasicLayout());

    log4cpp::Category& root = log4cpp::Category::getRoot();
    root.addAppender(fileAppender);
    root.setPriority(log4cpp::Priority::INFO);
    root.info("Logging into a file now!");
    root.error("An error message.");   

    MainWindow w;
    w.show();
    return a.exec();
    log4cpp::Category::shutdown();
}
