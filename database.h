#ifndef DATABASE_H
#define DATABASE_H

#include <QObject>
#include <QSqlDatabase>
#include <QString>
#include <QVector>
#include "Transaction.h"

class Database : public QObject
{
    Q_OBJECT
public:
    explicit Database(QObject *parent = nullptr);

    // 初始化数据库
    void init();

    // 保存全部交易记录
    bool saveTransactions(const QVector<Transaction> &lists);
    bool deleteTransaction(Transaction t);
    QVector<Transaction> loadTransactions();
    // 可以扩展：查询、删除、修改等方法
    // QVector<Transaction> getTransactions(const QString &account);
    void testFunction();

private:
    QSqlDatabase my_db;
};

#endif // DATABASE_H

