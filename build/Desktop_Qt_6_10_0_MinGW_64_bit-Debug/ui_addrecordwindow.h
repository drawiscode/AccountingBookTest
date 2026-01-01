/********************************************************************************
** Form generated from reading UI file 'addrecordwindow.ui'
**
** Created by: Qt User Interface Compiler version 6.10.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_ADDRECORDWINDOW_H
#define UI_ADDRECORDWINDOW_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_AddRecordWindow
{
public:

    void setupUi(QWidget *AddRecordWindow)
    {
        if (AddRecordWindow->objectName().isEmpty())
            AddRecordWindow->setObjectName("AddRecordWindow");
        AddRecordWindow->resize(400, 300);

        retranslateUi(AddRecordWindow);

        QMetaObject::connectSlotsByName(AddRecordWindow);
    } // setupUi

    void retranslateUi(QWidget *AddRecordWindow)
    {
        AddRecordWindow->setWindowTitle(QCoreApplication::translate("AddRecordWindow", "Form", nullptr));
    } // retranslateUi

};

namespace Ui {
    class AddRecordWindow: public Ui_AddRecordWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_ADDRECORDWINDOW_H
