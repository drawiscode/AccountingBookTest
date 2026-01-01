#include "addrecordwindow.h"
#include <QMessageBox>

AddRecordWindow::AddRecordWindow(QWidget *parent)
    : QWidget(parent)
{
    QLabel *labelAccount = new QLabel("账号：");
    QLabel *labelDate = new QLabel("日期：");
    QLabel *labelType = new QLabel("类型：");
    QLabel *labelAmount = new QLabel("金额：");
    QLabel *labelPaymentWay = new QLabel("交易方式：");
    QLabel *labelNote = new QLabel("备注：");

    editAccount = new QLineEdit;
    editDate = new QLineEdit;
    editType = new QLineEdit;
    editAmount = new QLineEdit;
    editPaymentWay=new QLineEdit;
    editNote = new QLineEdit;

    QPushButton *btnSubmit = new QPushButton("完成");
    QPushButton *btnBack = new QPushButton("返回");

    auto *layout = new QVBoxLayout;
    layout->addWidget(labelAccount);
    layout->addWidget(editAccount);
    layout->addWidget(labelDate);
    layout->addWidget(editDate);
    layout->addWidget(labelType);
    layout->addWidget(editType);
    layout->addWidget(labelAmount);
    layout->addWidget(editAmount);
    layout->addWidget(labelPaymentWay);
    layout->addWidget(editPaymentWay);
    layout->addWidget(labelNote);
    layout->addWidget(editNote);

    auto *buttonLayout = new QHBoxLayout;
    buttonLayout->addWidget(btnSubmit);
    buttonLayout->addWidget(btnBack);
    layout->addLayout(buttonLayout);

    setLayout(layout);

    connect(btnSubmit, &QPushButton::clicked, this, &AddRecordWindow::onSubmit);
    connect(btnBack, &QPushButton::clicked, this, &AddRecordWindow::onBack);
}

void AddRecordWindow::onSubmit()
{
    if (editDate->text().isEmpty() || editType->text().isEmpty() || editAmount->text().isEmpty())
    {
        QMessageBox::warning(this, "错误", "请填写所有必要信息！");
        return;
    }

    bool ok;
    double amount = editAmount->text().toDouble(&ok);
    if (!ok)
    {
        QMessageBox::warning(this, "错误", "金额必须是数字！");
        return;
    }

    emit recordAdded(editAccount->text(),editDate->text(), editType->text(), amount,editPaymentWay->text(), editNote->text());
}

void AddRecordWindow::onBack()
{
    emit backToMain();
}
