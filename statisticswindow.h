#ifndef STATISTICSWINDOW_H
#define STATISTICSWINDOW_H

#include <QWidget>
#include <QPushButton>
#include <QTableWidget>
#include <QVBoxLayout>
#include <QSqlQuery>
#include <QSqlError>
#include <QDebug>
#include <QLabel>
#include <QHeaderView>

#include "database.h"
#include "statisticsmanager.h"
class StatisticsWindow : public QWidget
{
    Q_OBJECT
public:
    explicit StatisticsWindow(Database *db,QWidget *parent = nullptr);

signals:
    void backToMain();

public slots:
    void loadStatistics();

private:
    QTableWidget *tableMonth;
    QTableWidget *tableYear;
    QPushButton *btnBack;

    StatisticsManager *statisticsManager;
};

#endif // STATISTICSWINDOW_H
