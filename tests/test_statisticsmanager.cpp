#include <gtest/gtest.h>
#include "statisticsmanager.h"
#include "transaction.h"

// 辅助函数：创建 Transaction
Transaction makeTransaction(const QString& date, double amount)
{
    //Transaction(const QString type1,double amount1,const QString account1,const QString date1,const QString payment_way1,const QString note1);
    QString type = "";
    QString account = "";
    QString payment_way = "";
    QString note = "";
    return Transaction(type, amount, account, date, payment_way, note);
}

TEST(StatisticsManagerTest, MonthlyTotalEmptyInput)
{
    StatisticsManager mgr(nullptr);
    QVector<Transaction> transactions;

    auto result = mgr.calculateMonthlyTotal(transactions);

    EXPECT_TRUE(result.isEmpty());
}

TEST(StatisticsManagerTest, MonthlyTotalOnlyExpense)
{
    StatisticsManager mgr(nullptr);

    QVector<Transaction> transactions = {
        makeTransaction("2025-01-01", -100.0),
        makeTransaction("2025-01-02", -50.0)
    };

    auto result = mgr.calculateMonthlyTotal(transactions);

    EXPECT_EQ(result.size(), 1);
    EXPECT_EQ(result[0][0], "2025-01");
    EXPECT_EQ(result[0][1], "-150.00");
    EXPECT_EQ(result[0][2], "0.00");
}

TEST(StatisticsManagerTest, MonthlyTotalOnlyIncome)
{
    StatisticsManager mgr(nullptr);

    QVector<Transaction> transactions = {
        makeTransaction("2025-02-01", 100.0),
        makeTransaction("2025-02-10", 200.0)
    };

    auto result = mgr.calculateMonthlyTotal(transactions);

    EXPECT_EQ(result.size(), 1);
    EXPECT_EQ(result[0][0], "2025-02");
    EXPECT_EQ(result[0][1], "0.00");
    EXPECT_EQ(result[0][2], "300.00");
}

TEST(StatisticsManagerTest, MonthlyTotalBasic)
{
    StatisticsManager mgr(nullptr); // 不用真实数据库

    QVector<Transaction> transactions = {
        makeTransaction("2025-01-01", -100.10),
        makeTransaction("2025-01-02", -50.0),
        makeTransaction("2025-01-03", 200.20),
        makeTransaction("2025-02-01", -30.0),
        makeTransaction("2025-02-05", 70.0),
        makeTransaction("2025-03-11", -44.0),
        makeTransaction("2025-03-12", 70.0),
        makeTransaction("2025-04-01", -510.0),
        makeTransaction("2025-07-05", 880.0)
    };

    auto result = mgr.calculateMonthlyTotal(transactions);

    // 预期结果：2025-01 支出 -150, 收入 200; 2025-02 支出 -30, 收入 70
    EXPECT_EQ(result.size(), 5);

    EXPECT_EQ(result[0][0], "2025-01");
    EXPECT_EQ(result[0][1], "-150.10");
    EXPECT_EQ(result[0][2], "200.20");

    EXPECT_EQ(result[1][0], "2025-02");
    EXPECT_EQ(result[1][1], "-30.00");
    EXPECT_EQ(result[1][2], "70.00");

    EXPECT_EQ(result[2][0], "2025-03");
    EXPECT_EQ(result[2][1], "-44.00");
    EXPECT_EQ(result[2][2], "70.00");

    EXPECT_EQ(result[3][0], "2025-04");
    EXPECT_EQ(result[3][1], "-510.00");
    EXPECT_EQ(result[3][2], "0.00");

    EXPECT_EQ(result[4][0], "2025-07");
    EXPECT_EQ(result[4][1], "0.00");
    EXPECT_EQ(result[4][2], "880.00");
}

TEST(StatisticsManagerTest, MonthlyTotalZeroAmount)
{
    StatisticsManager mgr(nullptr);

    QVector<Transaction> transactions = {
        makeTransaction("2025-03-01", 0.0)
    };

    auto result = mgr.calculateMonthlyTotal(transactions);

    EXPECT_EQ(result.size(), 1);
    EXPECT_EQ(result[0][1], "0.00");
    EXPECT_EQ(result[0][2], "0.00");
}

TEST(StatisticsManagerTest, YearlyTotalEmptyInput)
{
    StatisticsManager mgr(nullptr);
    QVector<Transaction> transactions;

    auto result = mgr.calculateYearlyTotal(transactions);

    EXPECT_TRUE(result.isEmpty());
}

TEST(StatisticsManagerTest, YearlyTotalOnlyExpense)
{
    StatisticsManager mgr(nullptr);

    QVector<Transaction> transactions = {
        makeTransaction("2025-01-01", -1000.0),
        makeTransaction("2025-01-02", -500.0)
    };

    auto result = mgr.calculateYearlyTotal(transactions);

    EXPECT_EQ(result.size(), 1);
    EXPECT_EQ(result[0][0], "2025");
    EXPECT_EQ(result[0][1], "-1500.00");
    EXPECT_EQ(result[0][2], "0.00");
}

TEST(StatisticsManagerTest, YearlyTotalOnlyIncome)
{
    StatisticsManager mgr(nullptr);

    QVector<Transaction> transactions = {
        makeTransaction("2025-02-01", 100.0),
        makeTransaction("2025-02-10", 200.0)
    };

    auto result = mgr.calculateYearlyTotal(transactions);

    EXPECT_EQ(result.size(), 1);
    EXPECT_EQ(result[0][0], "2025");
    EXPECT_EQ(result[0][1], "0.00");
    EXPECT_EQ(result[0][2], "300.00");
}

TEST(StatisticsManagerTest, YearlyTotalBasic) {
    StatisticsManager mgr(nullptr);

    QVector<Transaction> transactions = {
        makeTransaction("2018-01-01", -100.10),
        makeTransaction("2018-02-02", 200.00),
        makeTransaction("2019-03-03", -533.00),
        makeTransaction("2019-04-01", 400.00),
        makeTransaction("2020-02-02", 210.00),
        makeTransaction("2020-03-03", -5220.00),
        makeTransaction("2021-11-01", -110.00),
        makeTransaction("2021-12-02", 2010.00),
        makeTransaction("2022-03-03", -520.10),
        makeTransaction("2022-07-01", -100.00),
        makeTransaction("2025-09-02", 200.00),
        makeTransaction("2025-08-13", -50.10)
    };

    auto result = mgr.calculateYearlyTotal(transactions);

    // 预期结果：2024 支出 -50, 收入 0; 2025 支出 -100, 收入 200
    EXPECT_EQ(result.size(), 6);

    EXPECT_EQ(result[0][0], "2018");
    EXPECT_EQ(result[0][1], "-100.10");
    EXPECT_EQ(result[0][2], "200.00");

    EXPECT_EQ(result[1][0], "2019");
    EXPECT_EQ(result[1][1], "-533.00");
    EXPECT_EQ(result[1][2], "400.00");

    EXPECT_EQ(result[2][0], "2020");
    EXPECT_EQ(result[2][1], "-5220.00");
    EXPECT_EQ(result[2][2], "210.00");

    EXPECT_EQ(result[3][0], "2021");
    EXPECT_EQ(result[3][1], "-110.00");
    EXPECT_EQ(result[3][2], "2010.00");

    EXPECT_EQ(result[4][0], "2022");
    EXPECT_EQ(result[4][1], "-620.10");
    EXPECT_EQ(result[4][2], "0.00");

    EXPECT_EQ(result[5][0], "2025");
    EXPECT_EQ(result[5][1], "-50.10");
    EXPECT_EQ(result[5][2], "200.00");
}

TEST(StatisticsManagerTest, YearlyTotalZeroAmount)
{
    StatisticsManager mgr(nullptr);

    QVector<Transaction> transactions = {
        makeTransaction("2025-03-01", 0.0)
};

    auto result = mgr.calculateYearlyTotal(transactions);

    EXPECT_EQ(result.size(), 1);
    EXPECT_EQ(result[0][1], "0.00");
    EXPECT_EQ(result[0][2], "0.00");
}
