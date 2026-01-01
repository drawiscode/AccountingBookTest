#include "statisticsmanager.h"
#include <QDate>

StatisticsManager::StatisticsManager(Database *db)
{
    this->database = db;
}

/**
 * 按月统计支出（amount < 0）
 * 返回格式：{{"2025-01", "-1234.56"}, {"2025-02", "-678.00"}, ...}
 */
QVector<QVector<QString>> StatisticsManager::calculateMonthlyTotal()
{
    QVector<Transaction> transactions = database->loadTransactions();
    return calculateMonthlyTotal(transactions);
}

QVector<QVector<QString>> StatisticsManager::calculateMonthlyTotal(const QVector<Transaction>& transactions)
{
    QVector<QVector<QString>> results;
    QMap<QString, QPair<double, double>> monthTotals;

    for (const auto &t : transactions)
    {
        QString date = t.getDate();
        QString month = date.left(7); // "YYYY-MM"

        double amount = t.getAmount();
        if (amount < 0)
        {
            monthTotals[month].first += amount;   // 支出
        }
        else
        {
            monthTotals[month].second += amount;  // 收入
        }
    }


    // 生成结果表格数据
    for (auto it = monthTotals.begin(); it != monthTotals.end(); ++it)
    {
        QVector<QString> row;
        row.append(it.key()); // 月份
        //将数字转换成字符串并保留两位小数
        row.append(QString::number(it.value().first, 'f', 2));  // 总支出
        row.append(QString::number(it.value().second, 'f', 2)); // 总收入
        results.append(row);
    }

    return results;
}


QVector<QVector<QString>> StatisticsManager::calculateYearlyTotal()
{
    QVector<Transaction> transactions = database->loadTransactions();
    return calculateYearlyTotal(transactions);
}

QVector<QVector<QString>> StatisticsManager::calculateYearlyTotal(const QVector<Transaction>& transactions)
{
    QVector<QVector<QString>> results;

    // QMap<年份, QPair<总支出, 总收入>>
    QMap<QString, QPair<double, double>> yearTotals;


    for (const auto &t : transactions)
    {
        QString date = t.getDate();
        QString year = date.left(4); // 取年份部分（前4个字符）

        double amount = t.getAmount();
        if (amount < 0)
        {
            yearTotals[year].first += amount;   // 累计支出
        }
        else
        {
            yearTotals[year].second += amount;  // 累计收入
        }
    }

    for (auto it = yearTotals.begin(); it != yearTotals.end(); ++it)
    {
        QVector<QString> row;
        row.append(it.key()); // 年份
        row.append(QString::number(it.value().first, 'f', 2));  // 支出
        row.append(QString::number(it.value().second, 'f', 2)); // 收入
        results.append(row);
    }

    return results;
}
