// querywindow.h

#ifndef QUERYWINDOW_H
#define QUERYWINDOW_H

#include <QWidget>
#include <QTableWidget>
#include <QLineEdit>
#include <QPushButton>
#include "database.h"
#include <QHeaderView>
#include "database.h"
#include "querymanager.h"
#include <QMessageBox>

class QueryWindow : public QWidget
{
    Q_OBJECT
public:
    explicit QueryWindow(Database *db, QWidget *parent = nullptr);

signals:
    void backToMain();

private slots:
    void onQuery_Amount();
    void onQuery_Date();
    void onQuery_Type();
private:
    Database *database;

    QLineEdit *inputAmount;//输入金额行
    QLineEdit *inputDate;//输入日期行 月
    QLineEdit *inputType;//输入日期行 年

    QPushButton *btnQuery_Amount;//金额查询按钮
    QPushButton *btnQuery_Date;//日期查询按钮 月
    QPushButton *btnQuery_Type;//日期查询按钮 年

    QPushButton *btnBack;
    QTableWidget *tableResults;

    QueryManager *querymanager;
};

#endif
