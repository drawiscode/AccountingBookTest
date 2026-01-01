#ifndef TRANSACTION_H
#define TRANSACTION_H
#include <iostream>
#include <QString>
#include <fstream>

using namespace std;

class Transaction
{
private:
    QString type;
    double amount;//负数代表支出，正数代表收入
    //string my_account;//自己的账户
    QString account;//对方的账户
    QString date;//交易日期
    QString payment_way;//交易方式
    QString note;//备注
public:
    Transaction(const QString type1,double amount1,const QString account1,const QString date1,const QString payment_way1,const QString note1);
    Transaction();
   // void save(ofstream &out)const;
   // void load(ifstream &in);

    QString getType()const;
    QString getDate()const;//返回交易日期
    double getAmount()const;
    QString getAccount()const;
    QString getPayment_way()const;
    QString getNote()const;
};
#endif // TRANSACTION_H
