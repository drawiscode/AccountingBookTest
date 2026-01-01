#ifndef QUERYMANAGER_H
#define QUERYMANAGER_H

#include <QVector>
#include "transaction.h"
#include <QString>
#include "database.h"

class QueryManager
{
public:
    QueryManager(Database *database);
    QVector<Transaction>Query_By_Amount(double money1,double money2);
    QVector<Transaction>Query_By_Amount(double money1,double money2,const QVector<Transaction>& transactions);

    QVector<Transaction>Query_By_Date(QString date);
    QVector<Transaction>Query_By_Date(QString date,const QVector<Transaction>& transactions);

    QVector<Transaction>Query_By_type(QString type);
    QVector<Transaction>Query_By_type(QString type,const QVector<Transaction>& transactions);

private:
    Database *db;
};

#endif // QUERYMANAGER_H
