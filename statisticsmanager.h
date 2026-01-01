#ifndef STATISTICSMANAGER_H
#define STATISTICSMANAGER_H

#include "database.h"
#include "transaction.h"
#include <QVector>
#include <QString>
#include <QMap>

class StatisticsManager
{
public:
    StatisticsManager(Database *db);

    QVector<QVector<QString>> calculateMonthlyTotal();
    QVector<QVector<QString>> calculateMonthlyTotal(const QVector<Transaction>& transactions);

    QVector<QVector<QString>> calculateYearlyTotal();
    QVector<QVector<QString>> calculateYearlyTotal(const QVector<Transaction>& transactions);

private:
    Database *database;  // 指向数据库对象（非拥有）
};

#endif // STATISTICSMANAGER_H
