#include "transaction.h"

Transaction::Transaction()
{
    type="NULL";
    amount=0;
    account="NULL";
    date="NULL";
    payment_way="NULL";
}

Transaction::Transaction(QString type1,double amount1,QString account1,QString date1,QString payment_way1,QString note1)
{
    type=type1;
    amount=amount1;
    account=account1;
    date=date1;
    payment_way=payment_way1;
    note=note1;
}
/*
void Transaction::save(ofstream &out)const
{
    /*
     string type;
    int amount;//负数代表支出，正数代表收入
    string account;//对方的账户
    string date;//交易日期
    string payment_way;//交易方式
    */
 //   out<<type<<" "<<amount<<" "<<account<<" "<<date<<" "<<payment_way<<endl;
//}

/*void Transaction::load(ifstream &in)
{
    in>>type>>amount>>account>>date>>payment_way;
    return;
}*/

QString Transaction::getDate()const
{
    return date;
}

double Transaction::getAmount()const
{
    return amount;
}

QString Transaction::getType()const
{
    return type;
}

QString Transaction::getAccount()const
{
    return account;
}

QString Transaction::getPayment_way()const
{
    return payment_way;
}

QString Transaction::getNote()const
{
    return note;
}
