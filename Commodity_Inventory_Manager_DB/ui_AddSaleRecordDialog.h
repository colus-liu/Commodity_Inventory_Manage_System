/********************************************************************************
** Form generated from reading UI file 'AddSaleRecordDialog.ui'
**
** Created by: Qt User Interface Compiler version 6.7.2
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_ADDSALERECORDDIALOG_H
#define UI_ADDSALERECORDDIALOG_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QDateEdit>
#include <QtWidgets/QDialog>
#include <QtWidgets/QDoubleSpinBox>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QSpinBox>

QT_BEGIN_NAMESPACE

class Ui_AddSaleRecordDialog
{
public:
    QLabel *label;
    QLineEdit *edtOrderId;
    QLabel *label_2;
    QSpinBox *spbQuantity;
    QDoubleSpinBox *spbDiscountRate;
    QLabel *label_3;
    QLabel *label_4;
    QLabel *label_5;
    QDateEdit *edtOrderDate;
    QLineEdit *edtContactPhone;
    QPushButton *btnConfirm;
    QPushButton *btnCancel;

    void setupUi(QDialog *AddSaleRecordDialog)
    {
        if (AddSaleRecordDialog->objectName().isEmpty())
            AddSaleRecordDialog->setObjectName("AddSaleRecordDialog");
        AddSaleRecordDialog->resize(245, 268);
        label = new QLabel(AddSaleRecordDialog);
        label->setObjectName("label");
        label->setGeometry(QRect(30, 30, 51, 20));
        edtOrderId = new QLineEdit(AddSaleRecordDialog);
        edtOrderId->setObjectName("edtOrderId");
        edtOrderId->setGeometry(QRect(92, 30, 121, 20));
        label_2 = new QLabel(AddSaleRecordDialog);
        label_2->setObjectName("label_2");
        label_2->setGeometry(QRect(30, 70, 41, 20));
        spbQuantity = new QSpinBox(AddSaleRecordDialog);
        spbQuantity->setObjectName("spbQuantity");
        spbQuantity->setGeometry(QRect(90, 70, 42, 22));
        spbDiscountRate = new QDoubleSpinBox(AddSaleRecordDialog);
        spbDiscountRate->setObjectName("spbDiscountRate");
        spbDiscountRate->setGeometry(QRect(90, 150, 62, 22));
        label_3 = new QLabel(AddSaleRecordDialog);
        label_3->setObjectName("label_3");
        label_3->setGeometry(QRect(30, 110, 61, 20));
        label_4 = new QLabel(AddSaleRecordDialog);
        label_4->setObjectName("label_4");
        label_4->setGeometry(QRect(30, 150, 41, 20));
        label_5 = new QLabel(AddSaleRecordDialog);
        label_5->setObjectName("label_5");
        label_5->setGeometry(QRect(29, 190, 51, 20));
        edtOrderDate = new QDateEdit(AddSaleRecordDialog);
        edtOrderDate->setObjectName("edtOrderDate");
        edtOrderDate->setGeometry(QRect(90, 110, 110, 22));
        edtContactPhone = new QLineEdit(AddSaleRecordDialog);
        edtContactPhone->setObjectName("edtContactPhone");
        edtContactPhone->setGeometry(QRect(90, 190, 113, 20));
        btnConfirm = new QPushButton(AddSaleRecordDialog);
        btnConfirm->setObjectName("btnConfirm");
        btnConfirm->setGeometry(QRect(40, 220, 61, 21));
        btnCancel = new QPushButton(AddSaleRecordDialog);
        btnCancel->setObjectName("btnCancel");
        btnCancel->setGeometry(QRect(130, 220, 61, 21));

        retranslateUi(AddSaleRecordDialog);

        QMetaObject::connectSlotsByName(AddSaleRecordDialog);
    } // setupUi

    void retranslateUi(QDialog *AddSaleRecordDialog)
    {
        AddSaleRecordDialog->setWindowTitle(QCoreApplication::translate("AddSaleRecordDialog", "Dialog", nullptr));
        label->setText(QCoreApplication::translate("AddSaleRecordDialog", "\350\256\242\345\215\225\345\217\267\357\274\232", nullptr));
        label_2->setText(QCoreApplication::translate("AddSaleRecordDialog", "\346\225\260\351\207\217\357\274\232", nullptr));
        label_3->setText(QCoreApplication::translate("AddSaleRecordDialog", "\350\256\242\345\215\225\346\227\245\346\234\237\357\274\232", nullptr));
        label_4->setText(QCoreApplication::translate("AddSaleRecordDialog", "\346\212\230\346\211\243\347\216\207\357\274\232", nullptr));
        label_5->setText(QCoreApplication::translate("AddSaleRecordDialog", "\350\201\224\347\263\273\347\224\265\350\257\235\357\274\232", nullptr));
        btnConfirm->setText(QCoreApplication::translate("AddSaleRecordDialog", "\347\241\256\345\256\232", nullptr));
        btnCancel->setText(QCoreApplication::translate("AddSaleRecordDialog", "\345\217\226\346\266\210", nullptr));
    } // retranslateUi

};

namespace Ui {
    class AddSaleRecordDialog: public Ui_AddSaleRecordDialog {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_ADDSALERECORDDIALOG_H
