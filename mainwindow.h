#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QPushButton>
#include <QTableWidget>
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QHeaderView>
#include <QStackedWidget>
#include "transaction.h"
#include "addrecordwindow.h"
#include "statisticswindow.h"
#include "database.h"
#include "querywindow.h"

class MainWindow : public QMainWindow
{
    Q_OBJECT
public:
    explicit MainWindow(QWidget *parent = nullptr);

private slots:
    void onAddRecord();
    void onDeleteRecord();
    void onViewStatistics();
    void onSaveToDatabase();

    void onRecordAdded(const QString &account,const QString &date, const QString &type, double amount,const QString &payment_way, const QString &note);
    void displayTransactions(QVector<Transaction>lists);

private:
    QPushButton *btnAdd;
    QPushButton *btnDelete;
    QPushButton *btnStats;
    QPushButton *btnQuery;
    QTableWidget *table;

    QStackedWidget *stack; // 用于页面切换
    QWidget *mainPage;
    AddRecordWindow *addPage;
    StatisticsWindow *statsPage;
    QueryWindow *queryPage;

    //保存此次新创建的记录
    QVector<Transaction> transactions;
    // ------------------ 测试数据库 ------------------
    Database db;
};

#endif // MAINWINDOW_H
