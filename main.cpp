#include "mainwindow.h"

#include <QVector>
#include <QApplication>
#include <QDebug>

#include "database.h"
int main(int argc, char *argv[])
{
    QApplication a(argc, argv);



    //插入大量数据测试
    //Database db;
   // db.init();
    //db.testFunction();

    // 显示 GUI
    MainWindow w;
    w.show();

    return a.exec();
}

