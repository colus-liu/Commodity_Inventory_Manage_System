/********************************************************************************
** Form generated from reading UI file 'ShowSaleRecordsDialog.ui'
**
** Created by: Qt User Interface Compiler version 6.7.2
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_SHOWSALERECORDSDIALOG_H
#define UI_SHOWSALERECORDSDIALOG_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QDialog>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QTableView>

QT_BEGIN_NAMESPACE

class Ui_ShowSaleRecordsDialog
{
public:
    QTableView *tb_saleRecordInfo;
    QPushButton *btnExit;

    void setupUi(QDialog *ShowSaleRecordsDialog)
    {
        if (ShowSaleRecordsDialog->objectName().isEmpty())
            ShowSaleRecordsDialog->setObjectName("ShowSaleRecordsDialog");
        ShowSaleRecordsDialog->resize(586, 316);
        tb_saleRecordInfo = new QTableView(ShowSaleRecordsDialog);
        tb_saleRecordInfo->setObjectName("tb_saleRecordInfo");
        tb_saleRecordInfo->setGeometry(QRect(10, 50, 561, 241));
        btnExit = new QPushButton(ShowSaleRecordsDialog);
        btnExit->setObjectName("btnExit");
        btnExit->setGeometry(QRect(470, 10, 71, 31));

        retranslateUi(ShowSaleRecordsDialog);

        QMetaObject::connectSlotsByName(ShowSaleRecordsDialog);
    } // setupUi

    void retranslateUi(QDialog *ShowSaleRecordsDialog)
    {
        ShowSaleRecordsDialog->setWindowTitle(QCoreApplication::translate("ShowSaleRecordsDialog", "Dialog", nullptr));
        btnExit->setText(QCoreApplication::translate("ShowSaleRecordsDialog", "\351\200\200\345\207\272", nullptr));
    } // retranslateUi

};

namespace Ui {
    class ShowSaleRecordsDialog: public Ui_ShowSaleRecordsDialog {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_SHOWSALERECORDSDIALOG_H
