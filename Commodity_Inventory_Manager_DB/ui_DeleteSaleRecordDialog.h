/********************************************************************************
** Form generated from reading UI file 'DeleteSaleRecordDialog.ui'
**
** Created by: Qt User Interface Compiler version 6.7.2
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_DELETESALERECORDDIALOG_H
#define UI_DELETESALERECORDDIALOG_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QDialog>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QPushButton>

QT_BEGIN_NAMESPACE

class Ui_DeleteSaleRecordDialog
{
public:
    QLabel *label;
    QLineEdit *edtOrderId;
    QPushButton *btnConfirm;
    QPushButton *btnCancel;

    void setupUi(QDialog *DeleteSaleRecordDialog)
    {
        if (DeleteSaleRecordDialog->objectName().isEmpty())
            DeleteSaleRecordDialog->setObjectName("DeleteSaleRecordDialog");
        DeleteSaleRecordDialog->resize(204, 94);
        label = new QLabel(DeleteSaleRecordDialog);
        label->setObjectName("label");
        label->setGeometry(QRect(20, 20, 51, 20));
        edtOrderId = new QLineEdit(DeleteSaleRecordDialog);
        edtOrderId->setObjectName("edtOrderId");
        edtOrderId->setGeometry(QRect(70, 20, 113, 20));
        btnConfirm = new QPushButton(DeleteSaleRecordDialog);
        btnConfirm->setObjectName("btnConfirm");
        btnConfirm->setGeometry(QRect(30, 50, 61, 21));
        btnCancel = new QPushButton(DeleteSaleRecordDialog);
        btnCancel->setObjectName("btnCancel");
        btnCancel->setGeometry(QRect(110, 50, 61, 21));

        retranslateUi(DeleteSaleRecordDialog);

        QMetaObject::connectSlotsByName(DeleteSaleRecordDialog);
    } // setupUi

    void retranslateUi(QDialog *DeleteSaleRecordDialog)
    {
        DeleteSaleRecordDialog->setWindowTitle(QCoreApplication::translate("DeleteSaleRecordDialog", "Dialog", nullptr));
        label->setText(QCoreApplication::translate("DeleteSaleRecordDialog", "\350\256\242\345\215\225\345\217\267\357\274\232", nullptr));
        btnConfirm->setText(QCoreApplication::translate("DeleteSaleRecordDialog", "\347\241\256\345\256\232", nullptr));
        btnCancel->setText(QCoreApplication::translate("DeleteSaleRecordDialog", "\345\217\226\346\266\210", nullptr));
    } // retranslateUi

};

namespace Ui {
    class DeleteSaleRecordDialog: public Ui_DeleteSaleRecordDialog {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_DELETESALERECORDDIALOG_H
