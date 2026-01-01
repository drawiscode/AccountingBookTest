#include <gtest/gtest.h>
#include "querymanager.h"
#include "statisticsmanager.h"
#include "transaction.h"

static QVector<Transaction> buildTestTransactions()
{
    return {
        Transaction("交通",-15,"17207065230","2025-11-01","支付宝","公交卡充值"),
        Transaction("餐饮",-32,"17207065230","2025-11-02","微信","午餐外卖"),
        Transaction("购物",-210,"17207065230","2025-11-03","支付宝","超市购物"),
        Transaction("娱乐",-88,"17207065230","2025-11-04","银行卡","看电影"),
        Transaction("工资",5200,"17207065230","2025-11-05","银行卡","十月工资"),
        Transaction("餐饮",-45,"17207065230","2025-11-06","微信","晚餐烧烤"),
        Transaction("红包",200,"17207065230","2025-11-06","微信","朋友发的红包"),
        Transaction("医疗",-120,"17207065230","2025-11-07","支付宝","药店买药"),
        Transaction("交通",-9,"17207065230","2025-11-08","支付宝","地铁"),
        Transaction("购物",-350,"17207065230","2025-11-09","微信","衣服"),

        Transaction("工资",5200,"17207065230","2025-10-05","银行卡","九月工资"),
        Transaction("餐饮",-28,"17207065230","2025-10-06","支付宝","早餐店"),
        Transaction("购物",-500,"17207065230","2025-10-08","支付宝","电器"),

        Transaction("娱乐",-60,"17207065230","2022-10-10","微信","KTV"),
        Transaction("红包",100,"17207065230","2024-10-12","微信","同学发的红包"),

        Transaction("交通",-12,"17207065230","2025-09-15","支付宝","公交车"),
        Transaction("餐饮",-24,"17207065230","2025-09-16","微信","午餐"),
        Transaction("购物",-240,"17207065230","2025-09-17","支付宝","衣服"),
        Transaction("工资",5200,"17207065230","2025-09-05","银行卡","八月工资"),
        Transaction("娱乐",-70,"17207065230","2025-09-18","支付宝","网费"),

        Transaction("交通",-8,"17207065230","2025-08-02","微信","地铁"),
        Transaction("餐饮",-35,"17207065230","2025-08-03","支付宝","晚饭"),
        Transaction("购物",-130,"17207065230","2025-08-04","支付宝","生活用品"),
        Transaction("医疗",-90,"17207065230","2025-08-06","微信","感冒药"),
        Transaction("工资",5200,"17207065230","2025-08-05","银行卡","七月工资"),
        Transaction("学习",-200,"17207065230","2025-08-10","支付宝","课程费用"),
        Transaction("红包",88,"17207065230","2025-08-12","微信","节日红包"),

        Transaction("交通",-6,"17207065230","2025-07-15","支付宝","公交车"),
        Transaction("餐饮",-45,"17207065230","2025-07-16","微信","午餐"),
        Transaction("购物",-180,"17207065230","2025-07-18","支付宝","鞋子"),
        Transaction("工资",5200,"17207065230","2025-07-05","银行卡","六月工资"),
        Transaction("娱乐",-95,"17207065230","2025-07-20","微信","游戏充值")
    };
}

TEST(IntegrationTest, Query2025_MonthlyStatistics_ExactValue_2025_11)
{
    QueryManager qm(nullptr);
    StatisticsManager sm(nullptr);

    auto all = buildTestTransactions();
    auto result2025 = qm.Query_By_Date("2025", all);
    auto stats = sm.calculateMonthlyTotal(result2025);

    bool found = false;
    for (const auto& row : stats)
    {
        if (row[0] == "2025-11")
        {
            EXPECT_EQ(row[1], "-869.00");
            EXPECT_EQ(row[2], "5400.00");
            found = true;
        }
    }
    EXPECT_TRUE(found);
}

TEST(IntegrationTest, QueryAmountRange_ThenMonthlyStatistics_2025_11)
{
    QueryManager qm(nullptr);
    StatisticsManager sm(nullptr);

    auto all = buildTestTransactions();
    auto expenses = qm.Query_By_Amount(-100, 0, all);
    auto stats = sm.calculateMonthlyTotal(expenses);

    bool found = false;
    for (const auto& row : stats)
    {
        if (row[0] == "2025-11")
        {
            EXPECT_EQ(row[1], "-189.00");
            EXPECT_EQ(row[2], "0.00");
            found = true;
        }
    }
    EXPECT_TRUE(found);
}

TEST(IntegrationTest, QuerySalary_ThenYearlyStatistics_2025)
{
    QueryManager qm(nullptr);
    StatisticsManager sm(nullptr);

    auto all = buildTestTransactions();
    auto salaries = qm.Query_By_type("工资", all);
    auto stats = sm.calculateYearlyTotal(salaries);

    bool found = false;
    for (const auto& row : stats)
    {
        if (row[0] == "2025")
        {
            EXPECT_EQ(row[1], "0.00");
            EXPECT_EQ(row[2], "26000.00");
            found = true;
        }
    }
    EXPECT_TRUE(found);
}
