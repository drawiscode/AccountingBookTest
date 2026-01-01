#ifndef ADDRECORDWINDOW_H
#define ADDRECORDWINDOW_H

#include <QWidget>
#include <QPushButton>
#include <QLineEdit>
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QLabel>

class AddRecordWindow : public QWidget
{
    Q_OBJECT
public:
    explicit AddRecordWindow(QWidget *parent = nullptr);

signals:
    void recordAdded(const QString &account,const QString &date, const QString &type, double amount, const QString &payment_way,const QString &note);
    void backToMain();

private slots:
    void onSubmit();
    void onBack();

private:
    QLineEdit *editAccount;
    QLineEdit *editDate;
    QLineEdit *editType;
    QLineEdit *editAmount;
    QLineEdit *editPaymentWay;
    QLineEdit *editNote;
};

#endif // ADDRECORDWINDOW_H
