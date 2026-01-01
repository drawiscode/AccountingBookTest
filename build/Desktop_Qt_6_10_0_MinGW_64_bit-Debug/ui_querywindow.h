/********************************************************************************
** Form generated from reading UI file 'querywindow.ui'
**
** Created by: Qt User Interface Compiler version 6.10.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_QUERYWINDOW_H
#define UI_QUERYWINDOW_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_QueryWindow
{
public:

    void setupUi(QWidget *QueryWindow)
    {
        if (QueryWindow->objectName().isEmpty())
            QueryWindow->setObjectName("QueryWindow");
        QueryWindow->resize(400, 300);

        retranslateUi(QueryWindow);

        QMetaObject::connectSlotsByName(QueryWindow);
    } // setupUi

    void retranslateUi(QWidget *QueryWindow)
    {
        QueryWindow->setWindowTitle(QCoreApplication::translate("QueryWindow", "Form", nullptr));
    } // retranslateUi

};

namespace Ui {
    class QueryWindow: public Ui_QueryWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_QUERYWINDOW_H
