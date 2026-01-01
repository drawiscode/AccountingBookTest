#include "querymanager.h"

QueryManager::QueryManager(Database *database)
{
    db=database;
}

QVector<Transaction> QueryManager::Query_By_Amount(double money1,double money2)
{
    QVector<Transaction> all = db->loadTransactions();
    QVector<Transaction> result=Query_By_Amount(money1,money2,all);
    return result;
}

QVector<Transaction> QueryManager::Query_By_Amount(double money1,double money2,const QVector<Transaction>& transactions)
{
    QVector<Transaction> result;
    for (const auto &t : transactions)
    {
        if (t.getAmount() >= money1 && t.getAmount() <= money2)
        {
            result.append(t);
        }
    }
    return result;
}

QVector<Transaction> QueryManager::Query_By_Date(QString date)
{
    QVector<Transaction> transactions=db->loadTransactions();
    QVector<Transaction> result=Query_By_Date(date,transactions);
    return result;
}

QVector<Transaction> QueryManager::Query_By_Date(QString date,const QVector<Transaction>& transactions)
{
    QVector<Transaction> result;
    for(const auto &t:transactions)
    {
        QString qstr=t.getDate();
        if(qstr.startsWith(date))
        {
            result.append(t);
        }
    }
    return result;
}

QVector<Transaction> QueryManager::Query_By_type(QString type)
{
    QVector<Transaction> transactions=db->loadTransactions();
    QVector<Transaction> result=Query_By_type(type,transactions);
    return result;
}

QVector<Transaction> QueryManager::Query_By_type(QString type,const QVector<Transaction>& transactions)
{
    QVector<Transaction> result;
    for(const auto &t:transactions)
    {
        QString qstr=t.getType();
        if(qstr.startsWith(type))
        {
            result.append(t);

        }
    }
    return result;
}
