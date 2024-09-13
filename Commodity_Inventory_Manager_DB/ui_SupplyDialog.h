/********************************************************************************
** Form generated from reading UI file 'SupplyDialog.ui'
**
** Created by: Qt User Interface Compiler version 6.7.2
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_SUPPLYDIALOG_H
#define UI_SUPPLYDIALOG_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QDialog>
#include <QtWidgets/QLabel>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QSpinBox>

QT_BEGIN_NAMESPACE

class Ui_SupplyDialog
{
public:
    QPushButton *btnConfirm;
    QPushButton *btnCancel;
    QLabel *label;
    QSpinBox *spbSupplyQuantity;

    void setupUi(QDialog *SupplyDialog)
    {
        if (SupplyDialog->objectName().isEmpty())
            SupplyDialog->setObjectName("SupplyDialog");
        SupplyDialog->resize(187, 87);
        btnConfirm = new QPushButton(SupplyDialog);
        btnConfirm->setObjectName("btnConfirm");
        btnConfirm->setGeometry(QRect(20, 50, 61, 21));
        btnCancel = new QPushButton(SupplyDialog);
        btnCancel->setObjectName("btnCancel");
        btnCancel->setGeometry(QRect(100, 50, 61, 21));
        label = new QLabel(SupplyDialog);
        label->setObjectName("label");
        label->setGeometry(QRect(40, 20, 51, 20));
        spbSupplyQuantity = new QSpinBox(SupplyDialog);
        spbSupplyQuantity->setObjectName("spbSupplyQuantity");
        spbSupplyQuantity->setGeometry(QRect(90, 20, 51, 22));

        retranslateUi(SupplyDialog);

        QMetaObject::connectSlotsByName(SupplyDialog);
    } // setupUi

    void retranslateUi(QDialog *SupplyDialog)
    {
        SupplyDialog->setWindowTitle(QCoreApplication::translate("SupplyDialog", "Dialog", nullptr));
        btnConfirm->setText(QCoreApplication::translate("SupplyDialog", "\347\241\256\345\256\232", nullptr));
        btnCancel->setText(QCoreApplication::translate("SupplyDialog", "\345\217\226\346\266\210", nullptr));
        label->setText(QCoreApplication::translate("SupplyDialog", "\350\241\245\350\264\247\351\207\217\357\274\232", nullptr));
    } // retranslateUi

};

namespace Ui {
    class SupplyDialog: public Ui_SupplyDialog {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_SUPPLYDIALOG_H
