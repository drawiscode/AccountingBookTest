#include "mainwindow.h"
#include "database.h"
#include <QMessageBox>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
{
    //数据库初始化
    db.init();
    //现将已有数据都从数据库中读出来并且显示出来
    QVector<Transaction>lists;
    lists=db.loadTransactions();


    // === 主页面 ===
    btnAdd = new QPushButton("添加新纪录");
    btnDelete = new QPushButton("删除选中纪录");
    btnStats = new QPushButton("查看统计");
    btnQuery = new QPushButton("查询记录");

    auto *buttonLayout = new QHBoxLayout;
    buttonLayout->addWidget(btnAdd);
    buttonLayout->addWidget(btnDelete);
    buttonLayout->addWidget(btnStats);
    buttonLayout->addWidget(btnQuery);

    table = new QTableWidget(this);
    table->setColumnCount(6);
    QStringList headers = {"账号","日期", "类型", "金额", "交易方式","备注"};
    table->setHorizontalHeaderLabels(headers);
    table->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);
    table->setEditTriggers(QAbstractItemView::DoubleClicked);

    auto *mainLayout = new QVBoxLayout;
    mainLayout->addLayout(buttonLayout);
    mainLayout->addWidget(table);

    mainPage = new QWidget;
    mainPage->setLayout(mainLayout);

    // === 添加页面 ===
    addPage = new AddRecordWindow;
    statsPage = new StatisticsWindow(&db);
    queryPage =new QueryWindow(&db);

    // === 页面管理 ===
    stack = new QStackedWidget;
    stack->addWidget(mainPage);
    stack->addWidget(addPage);
    stack->addWidget(statsPage);
    stack->addWidget(queryPage);
    setCentralWidget(stack);

    setWindowTitle("记账本系统");
    resize(800, 500);

    //显示已有数据
    displayTransactions(lists);

    // === 信号槽 ===
    connect(btnAdd, &QPushButton::clicked, this, &MainWindow::onAddRecord);
    connect(btnDelete, &QPushButton::clicked, this, &MainWindow::onDeleteRecord);
    connect(btnStats, &QPushButton::clicked, this, &MainWindow::onViewStatistics);
    connect(btnQuery, &QPushButton::clicked, [this]() {
        stack->setCurrentWidget(queryPage);
    });

    // 子界面信号连接
    connect(addPage, &AddRecordWindow::recordAdded, this, &MainWindow::onRecordAdded);
    connect(addPage, &AddRecordWindow::backToMain, [this]() {
        stack->setCurrentWidget(mainPage);
    });
    //统计页面
    connect(statsPage, &StatisticsWindow::backToMain, [this]() {
        stack->setCurrentWidget(mainPage);
    });
    //查询页面
    connect(queryPage, &QueryWindow::backToMain, [this]() {
        stack->setCurrentWidget(mainPage);
    });
}

void MainWindow::onAddRecord()
{
    stack->setCurrentWidget(addPage);
}

void MainWindow::onViewStatistics()
{
    statsPage->loadStatistics();
    stack->setCurrentWidget(statsPage);
}


void MainWindow::onRecordAdded(const QString &account,const QString &date, const QString &type, double amount, const QString &payment_way,const QString &note)
{
    int row = table->rowCount();
    table->insertRow(row);
    table->setItem(row, 0, new QTableWidgetItem(account));
    table->setItem(row, 1, new QTableWidgetItem(date));
    table->setItem(row, 2, new QTableWidgetItem(type));
    table->setItem(row, 3, new QTableWidgetItem(QString::number(amount)));
    table->setItem(row, 4, new QTableWidgetItem(payment_way));
    table->setItem(row, 5, new QTableWidgetItem(note));

    // Transaction(string type1,int amount1,string account1,string date1,string payment_way1,string note);
    Transaction new_transaction(type,amount,account,date,payment_way,note);

    //将记录保存到数据库中
    transactions.emplace_back(new_transaction);
    db.saveTransactions(transactions);
    transactions.clear();

    stack->setCurrentWidget(mainPage); // 返回主界面
}

void MainWindow::onDeleteRecord()
{
    int selected = table->currentRow();
    if (selected < 0)
    {
        QMessageBox::warning(this, "提示", "请先选择一条记录！");
        return;
    }

    // 获取该行信息
    // Transaction(string type1,int amount1,string account1,string date1,string payment_way1,string note);
    QString account1 = table->item(selected, 0)->text();
    QString date1 = table->item(selected, 1)->text();
    QString type1 = table->item(selected, 2)->text();
    double amount1 = table->item(selected, 3)->text().toDouble();
    QString payment_way1 = table->item(selected,4)->text();
    QString note1=table->item(selected,5)->text();
    Transaction delete_t(type1,amount1,account1,date1,payment_way1,note1);
    // 删除数据库中的记录
    bool ok = db.deleteTransaction(delete_t);

    if (ok)
    {
        table->removeRow(selected);
        QMessageBox::information(this, "成功", "该记录已删除。");
    }
    else
    {
        QMessageBox::warning(this, "失败", "删除数据库记录失败！");
    }
}


void MainWindow::onSaveToDatabase()
{
    //QMessageBox::information(this, "保存", "这里将保存数据到数据库（待实现）");
    db.saveTransactions(transactions);
    transactions.clear();
}

void MainWindow::displayTransactions(QVector<Transaction>lists)
{
    //将已有数据都显示出来
    for(long long i=0;i<lists.size();i++)
    {
        int row = table->rowCount();
        table->insertRow(row);
        table->setItem(row, 0, new QTableWidgetItem(lists[i].getAccount()));
        table->setItem(row, 1, new QTableWidgetItem(lists[i].getDate()));
        table->setItem(row, 2, new QTableWidgetItem(lists[i].getType()));
        table->setItem(row, 3, new QTableWidgetItem(QString::number(lists[i].getAmount())));
        table->setItem(row, 4, new QTableWidgetItem(lists[i].getPayment_way()));
        table->setItem(row, 5, new QTableWidgetItem(lists[i].getNote()));
    }
}
