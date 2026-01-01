#include <gtest/gtest.h>
#include "querymanager.h"
#include "transaction.h"

// 辅助函数：快速构造 Transaction
/*Transaction(const QString type1,double amount1,const QString account1,const QString date1,const QString payment_way1,const QString note1);*/
Transaction makeTransaction(const QString& type,double amount,const QString& date)
{
    return Transaction(
        type,
        amount,
        "",       // account
        date,
        "",       // payment_way
        ""            // note
        );
}
const QVector<Transaction> transactions = {
    makeTransaction("饮食", -100.00, "2023-01-12"),
    makeTransaction("交通", -50.00,  "2023-01-09"),
    makeTransaction("工资", 2000.00,  "2023-08-03"),
    makeTransaction("购物", -600.00, "2024-03-24"),
    makeTransaction("饮食", -30.00, "2024-07-31"),
    makeTransaction("红包", 200.00,  "2024-10-11"),
    makeTransaction("工资", 3000.00,  "2025-01-08"),
    makeTransaction("购物", -300.00, "2025-01-24"),
    makeTransaction("饮食", -50.00, "2025-02-21"),
    makeTransaction("红包", 500.00,  "2025-03-12")
};
/* =======================
 * Query_By_Amount 测试
 * ======================= */
TEST(QueryManagerTest, QueryByAmountBasic)
{
    QueryManager qm(nullptr);
    auto result1 = qm.Query_By_Amount(-100.0, 200.0, transactions);

    EXPECT_EQ(result1.size(), 5);
    EXPECT_EQ(result1[0].getAmount(), -100.00);
    EXPECT_EQ(result1[1].getAmount(), -50.00);
    EXPECT_EQ(result1[2].getAmount(), -30.00);
    EXPECT_EQ(result1[3].getAmount(), 200.00);
    EXPECT_EQ(result1[4].getAmount(), -50.00);

    auto result2 = qm.Query_By_Amount(-600.0, 2000.0, transactions);
    EXPECT_EQ(result2.size(), 9);
    EXPECT_EQ(result2[0].getAmount(), -100.00);
    EXPECT_EQ(result2[1].getAmount(), -50.00);
    EXPECT_EQ(result2[2].getAmount(), 2000.00);
    EXPECT_EQ(result2[3].getAmount(), -600.00);
    EXPECT_EQ(result2[4].getAmount(), -30.00);
    EXPECT_EQ(result2[5].getAmount(), 200.00);
    EXPECT_EQ(result2[6].getAmount(), -300.00);
    EXPECT_EQ(result2[7].getAmount(), -50.00);
    EXPECT_EQ(result2[8].getAmount(), 500.00);
}

TEST(QueryManagerTest, QueryByAmountEmptyResult)
{
    QueryManager qm(nullptr);

    QVector<Transaction> empty;
    auto result = qm.Query_By_Amount(-100.0, 100.0, empty);
    EXPECT_TRUE(result.isEmpty());
}

/* =======================
 * Query_By_Date 测试
 * ======================= */
TEST(QueryManagerTest, QueryByDateMonth)
{
    QueryManager qm(nullptr);

    auto result1 = qm.Query_By_Date("2025-01", transactions);

    EXPECT_EQ(result1.size(), 2);
    EXPECT_TRUE(result1[0].getDate().startsWith("2025-01"));
    EXPECT_TRUE(result1[1].getDate().startsWith("2025-01"));
}

TEST(QueryManagerTest, QueryByDateYear)
{
    QueryManager qm(nullptr);

    auto result2 = qm.Query_By_Date("2024", transactions);

    EXPECT_EQ(result2.size(), 3);
    EXPECT_TRUE(result2[0].getDate().startsWith("2024"));
    EXPECT_TRUE(result2[1].getDate().startsWith("2024"));
    EXPECT_TRUE(result2[2].getDate().startsWith("2024"));
}

TEST(QueryManagerTest, QueryByDateNoMatch)
{
    QueryManager qm(nullptr);

    QVector<Transaction> NoMatch = {
        makeTransaction("饮食", -100.0, "2024-12-31")
    };

    auto result = qm.Query_By_Date("2025-01", NoMatch);
    EXPECT_TRUE(result.isEmpty());
}

/* =======================
 * Query_By_type 测试
 * ======================= */
TEST(QueryManagerTest, QueryByTypeBasic)
{
    QueryManager qm(nullptr);

    auto result1 = qm.Query_By_type("饮食", transactions);

    EXPECT_EQ(result1.size(), 3);
    EXPECT_TRUE(result1[0].getType().startsWith("饮食"));
    EXPECT_TRUE(result1[1].getType().startsWith("饮食"));
    EXPECT_TRUE(result1[2].getType().startsWith("饮食"));

    auto result2 = qm.Query_By_type("红包", transactions);

    EXPECT_EQ(result2.size(), 2);
    EXPECT_TRUE(result2[0].getType().startsWith("红包"));
    EXPECT_TRUE(result2[1].getType().startsWith("红包"));
}

TEST(QueryManagerTest, QueryByTypeNoMatch)
{
    QueryManager qm(nullptr);

    auto result = qm.Query_By_type("教育", transactions);

    EXPECT_EQ(result.size(), 0);
}
