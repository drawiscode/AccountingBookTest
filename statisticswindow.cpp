#include "statisticswindow.h"

StatisticsWindow::StatisticsWindow(Database *db, QWidget *parent)
    : QWidget(parent)
{
    // 保存指向数据库的指针
    statisticsManager = new StatisticsManager(db);


    tableMonth = new QTableWidget(this);
    tableYear = new QTableWidget(this);
    btnBack = new QPushButton("返回主界面", this);

    tableMonth->setColumnCount(3);
    tableMonth->setHorizontalHeaderLabels({"月份", "总支出","总收入"});
    tableMonth->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);

    tableYear->setColumnCount(3);
    tableYear->setHorizontalHeaderLabels({"年份", "总支出","总收入"});
    tableYear->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);

    QVBoxLayout *layout = new QVBoxLayout;
    layout->addWidget(new QLabel("📅 按月统计："));
    layout->addWidget(tableMonth);
    layout->addWidget(new QLabel("📆 按年统计："));
    layout->addWidget(tableYear);
    layout->addWidget(btnBack);

    setLayout(layout);
    setWindowTitle("统计信息");
    resize(500, 600);

    connect(btnBack, &QPushButton::clicked, this, &StatisticsWindow::backToMain);

    //一定要放在最后！
    loadStatistics();
}

void StatisticsWindow::loadStatistics()
{
    tableMonth->setRowCount(0);
    tableYear->setRowCount(0);

    auto monthly = statisticsManager->calculateMonthlyTotal();
    for (const auto &row : monthly)
    {
        int r = tableMonth->rowCount();
        tableMonth->insertRow(r);

        tableMonth->setItem(r, 0, new QTableWidgetItem(row[0])); // 月份

        QTableWidgetItem *spendItem = new QTableWidgetItem(row[1]);
        QTableWidgetItem *incomeItem = new QTableWidgetItem(row[2]);

        spendItem->setForeground(QBrush(Qt::red));       // 支出红色
        incomeItem->setForeground(QBrush(Qt::darkGreen));// 收入绿色

        tableMonth->setItem(r, 1, spendItem);
        tableMonth->setItem(r, 2, incomeItem);
    }

    auto yearly = statisticsManager->calculateYearlyTotal();
    for (const auto &row : yearly)
    {
        int r = tableYear->rowCount();
        tableYear->insertRow(r);

        tableYear->setItem(r, 0, new QTableWidgetItem(row[0])); // 年份

        QTableWidgetItem *spendItem = new QTableWidgetItem(row[1]);
        QTableWidgetItem *incomeItem = new QTableWidgetItem(row[2]);

        spendItem->setForeground(QBrush(Qt::red));
        incomeItem->setForeground(QBrush(Qt::darkGreen));

        tableYear->setItem(r, 1, spendItem);
        tableYear->setItem(r, 2, incomeItem);
    }
}
