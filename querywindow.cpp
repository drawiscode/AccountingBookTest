// querywindow.cpp
#include "querywindow.h"
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QLabel>
#include <QTableWidgetItem>

QueryWindow::QueryWindow(Database *db, QWidget *parent)
    : QWidget(parent), database(db)
{
    //初始化查询管理器
    querymanager=new QueryManager(db);

    inputAmount = new QLineEdit(this);
    btnQuery_Amount = new QPushButton("查询", this);
    inputDate=new QLineEdit(this);
    btnQuery_Date =new QPushButton("查询",this);
    inputType=new QLineEdit(this);
    btnQuery_Type =new QPushButton("查询",this);

    btnBack = new QPushButton("返回主界面", this);
    tableResults = new QTableWidget(this);

    tableResults->setColumnCount(6);
    tableResults->setHorizontalHeaderLabels({"账号","日期","类型","金额","交易方式","备注"});
    tableResults->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);

    //初始化 查询by金额行
    QHBoxLayout *queryLayout_Amount = new QHBoxLayout;
    queryLayout_Amount->addWidget(new QLabel("金额(xxx-xxx):"));
    queryLayout_Amount->addWidget(inputAmount);
    queryLayout_Amount->addWidget(btnQuery_Amount);

    //初始化 查询by日期行
    QHBoxLayout *queryLayout_Date =new QHBoxLayout;
    queryLayout_Date->addWidget(new QLabel("日期(xxxx-xx或xxxx):"));
    queryLayout_Date->addWidget(inputDate);
    queryLayout_Date->addWidget(btnQuery_Date);


    //初始化 查询by日期行 年
    QHBoxLayout *queryLayout_Type =new QHBoxLayout;
    queryLayout_Type->addWidget(new QLabel("类型:"));
    queryLayout_Type->addWidget(inputType);
    queryLayout_Type->addWidget(btnQuery_Type);


    //以此把每个部件加入视图中
    QVBoxLayout *layout = new QVBoxLayout;
    layout->addLayout(queryLayout_Amount);
    layout->addLayout(queryLayout_Date);
    layout->addLayout(queryLayout_Type);
    layout->addWidget(tableResults);
    layout->addWidget(btnBack);

    setLayout(layout);
    setWindowTitle("查询账单");

    connect(btnQuery_Amount, &QPushButton::clicked, this, &QueryWindow::onQuery_Amount);
    connect(btnQuery_Date, &QPushButton::clicked, this, &QueryWindow::onQuery_Date);
    connect(btnQuery_Type, &QPushButton::clicked, this, &QueryWindow::onQuery_Type);
    connect(btnBack, &QPushButton::clicked, this, &QueryWindow::backToMain);
}

void QueryWindow::onQuery_Amount()
{
    tableResults->setRowCount(0);
    QString input = inputAmount->text().trimmed();

    double minAmount = 0, maxAmount = 0;

    if (input.contains("-"))//范围查询
    {
        QStringList parts = input.split("-", Qt::SkipEmptyParts);
        if (parts.size() != 2)
        {
            QMessageBox::warning(this, "输入错误", "请输入正确的范围格式，例如：50-100");
            return;
        }
        minAmount = parts[0].toDouble();
        maxAmount = parts[1].toDouble();
    }
    else//固定金额，单值查询
    {
        minAmount = input.toDouble();
        maxAmount = input.toDouble();
    }

    QVector<Transaction> transactions = querymanager->Query_By_Amount(minAmount, maxAmount);

    for (const auto &t : transactions)
    {
        int row = tableResults->rowCount();
        tableResults->insertRow(row);
        tableResults->setItem(row, 0, new QTableWidgetItem(t.getAccount()));
        tableResults->setItem(row, 1, new QTableWidgetItem(t.getDate()));
        tableResults->setItem(row, 2, new QTableWidgetItem(t.getType()));
        tableResults->setItem(row, 3, new QTableWidgetItem(QString::number(t.getAmount())));
        tableResults->setItem(row, 4, new QTableWidgetItem(t.getPayment_way()));
        tableResults->setItem(row, 5, new QTableWidgetItem(t.getNote()));
    }
}

void QueryWindow::onQuery_Date()
{
    tableResults->setRowCount(0);
    QString date = inputDate->text().trimmed(); // 例如 "2025-11"
    QVector<Transaction> transactions = querymanager->Query_By_Date(date);

    for (const auto &t : transactions)
    {
        int row = tableResults->rowCount();
        tableResults->insertRow(row);
        tableResults->setItem(row, 0, new QTableWidgetItem(t.getAccount()));
        tableResults->setItem(row, 1, new QTableWidgetItem(t.getDate()));
        tableResults->setItem(row, 2, new QTableWidgetItem(t.getType()));
        tableResults->setItem(row, 3, new QTableWidgetItem(QString::number(t.getAmount())));
        tableResults->setItem(row, 4, new QTableWidgetItem(t.getPayment_way()));
        tableResults->setItem(row, 5, new QTableWidgetItem(t.getNote()));
    }
}

void QueryWindow::onQuery_Type()
{
    tableResults->setRowCount(0);
    QString type = inputType->text().trimmed(); // 例如 "2025"
    QVector<Transaction> transactions = querymanager->Query_By_type(type);

    for (const auto &t : transactions)
    {
        int row = tableResults->rowCount();
        tableResults->insertRow(row);
        tableResults->setItem(row, 0, new QTableWidgetItem(t.getAccount()));
        tableResults->setItem(row, 1, new QTableWidgetItem(t.getDate()));
        tableResults->setItem(row, 2, new QTableWidgetItem(t.getType()));
        tableResults->setItem(row, 3, new QTableWidgetItem(QString::number(t.getAmount())));
        tableResults->setItem(row, 4, new QTableWidgetItem(t.getPayment_way()));
        tableResults->setItem(row, 5, new QTableWidgetItem(t.getNote()));
    }
}
