#include "database.h"
#include <QSqlQuery>
#include <QSqlError>
#include <QMessageBox>
#include <QDebug>

Database::Database(QObject *parent) : QObject(parent)
{
}

void Database::init()
{
    // 添加 SQLite 驱动
    my_db = QSqlDatabase::addDatabase("QSQLITE");

    // 设置数据库文件路径（会自动创建）
    my_db.setDatabaseName("E:/QtProjects/AccountingBook/data/transactions.db");

    // 打开数据库
    if (!my_db.open()) {
        qDebug() << "Failed to open database:" << my_db.lastError().text();
        QMessageBox::warning(nullptr, "Database Error",
                             "Unable to open SQLite database: " + my_db.lastError().text());
        return;
    }

    qDebug() << "Database opened successfully!";

    // 创建表（如果不存在）
    QSqlQuery query(my_db);
    QString createTable = R"(
        CREATE TABLE IF NOT EXISTS transactions (
            id INTEGER PRIMARY KEY AUTOINCREMENT,
            account TEXT,
            date TEXT,
            type TEXT,
            amount REAL,
            payment_way TEXT,
            note TEXT
        )
    )";
    if (!query.exec(createTable))
    {
        qDebug() << "Failed to create table:" << query.lastError().text();
    }
    else
    {
        qDebug() << "Table created or already exists.";
    }
}

bool Database::saveTransactions(const QVector<Transaction> &lists)
{
    if (!my_db.isOpen())
    {
        qDebug() << "Database not open!";
        return false;
    }
    /*  string type;
    int amount;//负数代表支出，正数代表收入
    string account;//对方的账户
    string date;//交易日期
    string payment_way;//交易方式
        note 备注*/
    QSqlQuery query(my_db);
    query.prepare("INSERT INTO transactions(account, date, type, amount, payment_way,note) "
                  "VALUES(:account, :date, :type, :amount,:payment_way, :note)");


    for (const auto &t : lists)
    {

        query.bindValue(":type", t.getType());
        query.bindValue(":amount", t.getAmount());
        query.bindValue(":account", t.getAccount());
        query.bindValue(":date", t.getDate());
        query.bindValue(":payment_way", t.getPayment_way());
        query.bindValue(":note", t.getNote());

        if (!query.exec())
        {
            qDebug() << "Insert failed:" << query.lastError().text();
            return false;
        }
    }

    qDebug() << "Transactions saved successfully!";
    return true;
}

bool Database::deleteTransaction(Transaction t)
{
    if (!my_db.isOpen())
    {
        qDebug() << "Database not open!";
        return false;
    }

    QSqlQuery query(my_db);
    query.prepare(R"(
        DELETE FROM transactions
        WHERE account = :account
          AND date = :date
          AND type = :type
          AND amount = :amount
          AND payment_way = :payment_way
          AND note = :note
    )");

    query.bindValue(":account", t.getAccount());
    query.bindValue(":date", t.getDate());
    query.bindValue(":type", t.getType());
    query.bindValue(":amount", t.getAmount());
    query.bindValue(":payment_way", t.getPayment_way());
    query.bindValue(":note", t.getNote());


    if (!query.exec())
    {
        qDebug() << "Delete failed:" << query.lastError().text();
        return false;
    }

    if (query.numRowsAffected() == 0)
    {
        qDebug() << "No matching record found to delete.";
        return false;
    }


    qDebug() << "Transaction deleted successfully.";
    return true;
}

QVector<Transaction> Database::loadTransactions()
{
    QVector<Transaction> result;

    if (!my_db.isOpen())
    {
        qDebug() << "Database not open!";
        return result;
    }

    QSqlQuery query(my_db);

    // 查询所有记录
    if (!query.exec("SELECT account, date, type, amount, payment_way, note FROM transactions"))
    {
        qDebug() << "Query failed:" << query.lastError().text();
        return result;
    }


    // 遍历结果集
    while (query.next())
    {
        QString account = query.value(0).toString();
        QString date = query.value(1).toString();
        QString type = query.value(2).toString();
        double amount = query.value(3).toDouble();
        QString payment_way = query.value(4).toString();
        QString note = query.value(5).toString();

        //  Transaction(const QString type1,double amount1,const QString account1,const QString date1,const QString payment_way1,const QString note1);
        Transaction newt(type,amount,account,date,payment_way,note);
        result.append(newt);
    }

    qDebug() << "Loaded" << result.size() << "transactions from database.";
    return result;
}

void Database::testFunction()
{
    //Transaction(const QString type1,double amount1,const QString account1,const QString date1,const QString payment_way1,const QString note1);
    Transaction t1("交通",-15,"17207065230","2025-11-01","支付宝","公交卡充值");
    Transaction t2("餐饮",-32,"17207065230","2025-11-02","微信","午餐外卖");
    Transaction t3("购物",-210,"17207065230","2025-11-03","支付宝","超市购物");
    Transaction t4("娱乐",-88,"17207065230","2025-11-04","银行卡","看电影");
    Transaction t5("工资",5200,"17207065230","2025-11-05","银行卡","十月工资");
    Transaction t6("餐饮",-45,"17207065230","2025-11-06","微信","晚餐烧烤");
    Transaction t7("红包",200,"17207065230","2025-11-06","微信","朋友发的红包");
    Transaction t8("医疗",-120,"17207065230","2025-11-07","支付宝","药店买药");
    Transaction t9("交通",-9,"17207065230","2025-11-08","支付宝","地铁");
    Transaction t10("购物",-350,"17207065230","2025-11-09","微信","衣服");
    Transaction t11("工资",5200,"17207065230","2025-10-05","银行卡","九月工资");
    Transaction t12("餐饮",-28,"17207065230","2025-10-06","支付宝","早餐店");
    Transaction t13("购物",-500,"17207065230","2025-10-08","支付宝","电器");
    Transaction t14("娱乐",-60,"17207065230","2022-10-10","微信","KTV");
    Transaction t15("红包",100,"17207065230","2024-10-12","微信","同学发的红包");
    Transaction t16("交通",-12,"17207065230","2025-09-15","支付宝","公交车");
    Transaction t17("餐饮",-24,"17207065230","2025-09-16","微信","午餐");
    Transaction t18("购物",-240,"17207065230","2025-09-17","支付宝","衣服");
    Transaction t19("工资",5200,"17207065230","2025-09-05","银行卡","八月工资");
    Transaction t20("娱乐",-70,"17207065230","2025-09-18","支付宝","网费");
    Transaction t21("交通",-8,"17207065230","2025-08-02","微信","地铁");
    Transaction t22("餐饮",-35,"17207065230","2025-08-03","支付宝","晚饭");
    Transaction t23("购物",-130,"17207065230","2025-08-04","支付宝","生活用品");
    Transaction t24("医疗",-90,"17207065230","2025-08-06","微信","感冒药");
    Transaction t25("工资",5200,"17207065230","2025-08-05","银行卡","七月工资");
    Transaction t26("学习",-200,"17207065230","2025-08-10","支付宝","课程费用");
    Transaction t27("红包",88,"17207065230","2025-08-12","微信","节日红包");
    Transaction t28("交通",-6,"17207065230","2025-07-15","支付宝","公交车");
    Transaction t29("餐饮",-45,"17207065230","2025-07-16","微信","午餐");
    Transaction t30("购物",-180,"17207065230","2025-07-18","支付宝","鞋子");
    Transaction t31("工资",5200,"17207065230","2025-07-05","银行卡","六月工资");
    Transaction t32("娱乐",-95,"17207065230","2025-07-20","微信","游戏充值");
    Transaction t33("学习",-120,"17207065230","2024-07-22","支付宝","教材");
    Transaction t34("医疗",-150,"17207065230","2024-06-12","微信","体检");
    Transaction t35("购物",-250,"17207065230","2024-06-15","支付宝","家居用品");
    Transaction t36("工资",5200,"17207065230","2024-06-05","银行卡","五月工资");
    Transaction t37("餐饮",-28,"17207065230","2024-06-18","支付宝","早餐");
    Transaction t38("娱乐",-60,"17207065230","2024-06-20","微信","电影票");
    Transaction t39("交通",-11,"17207065230","2023-06-22","支付宝","地铁");
    Transaction t40("学习",-300,"17207065230","2023-06-25","微信","培训课程");
    Transaction t41("红包",66,"17207065230","2022-06-28","微信","朋友红包");
    Transaction t42("购物",-310,"17207065230","2022-05-14","支付宝","电脑配件");
    Transaction t43("娱乐",-40,"17207065230","2021-05-15","微信","看演出");
    Transaction t44("餐饮",-33,"17207065230","2021-05-16","支付宝","午餐");
    Transaction t45("工资",5200,"17207065230","2020-05-05","银行卡","四月工资");
    Transaction t46("医疗",-220,"17207065230","2020-05-18","微信","牙医");
    Transaction t47("交通",-7,"17207065230","2019-05-20","支付宝","地铁");
    Transaction t48("购物",-180,"17207065230","2019-05-21","支付宝","衣服");
    Transaction t49("学习",-150,"17207065230","2017-05-23","微信","教材费");
    Transaction t50("红包",50,"17207065230","2025-05-25","微信","节日红包");

    QVector<Transaction> tests = {t1, t2, t3,t4,t5,t6,t7,t8,t9,t10,t11,t12,t13,t14,t15,t16,t17,t18,t19,t20,t21,t22,t23,t24,t25,t26,t27,t28,t29,t30,t31,t32,t33,t34,t35
    ,t36,t37,t38,t39,t40,t41,t42,t43,t44,t45,t46,t47,t48,t49,t50};
    saveTransactions(tests);
    return;
}
