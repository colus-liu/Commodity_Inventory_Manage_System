/********************************************************************************
** Form generated from reading UI file 'Widget.ui'
**
** Created by: Qt User Interface Compiler version 6.7.2
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_WIDGET_H
#define UI_WIDGET_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QTableView>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_Widget
{
public:
    QTableView *tbInfo;
    QPushButton *btnInquire;
    QPushButton *btnAdd;
    QPushButton *btnDelete;
    QPushButton *btnSupply;
    QPushButton *btnRefresh;
    QPushButton *pushButton;

    void setupUi(QWidget *Widget)
    {
        if (Widget->objectName().isEmpty())
            Widget->setObjectName("Widget");
        Widget->resize(925, 337);
        tbInfo = new QTableView(Widget);
        tbInfo->setObjectName("tbInfo");
        tbInfo->setGeometry(QRect(10, 50, 911, 271));
        btnInquire = new QPushButton(Widget);
        btnInquire->setObjectName("btnInquire");
        btnInquire->setGeometry(QRect(20, 20, 61, 21));
        btnAdd = new QPushButton(Widget);
        btnAdd->setObjectName("btnAdd");
        btnAdd->setGeometry(QRect(100, 20, 61, 21));
        btnDelete = new QPushButton(Widget);
        btnDelete->setObjectName("btnDelete");
        btnDelete->setGeometry(QRect(180, 20, 61, 21));
        btnSupply = new QPushButton(Widget);
        btnSupply->setObjectName("btnSupply");
        btnSupply->setGeometry(QRect(260, 20, 61, 21));
        btnRefresh = new QPushButton(Widget);
        btnRefresh->setObjectName("btnRefresh");
        btnRefresh->setGeometry(QRect(610, 20, 61, 21));
        pushButton = new QPushButton(Widget);
        pushButton->setObjectName("pushButton");
        pushButton->setGeometry(QRect(350, 20, 56, 18));

        retranslateUi(Widget);

        QMetaObject::connectSlotsByName(Widget);
    } // setupUi

    void retranslateUi(QWidget *Widget)
    {
        Widget->setWindowTitle(QCoreApplication::translate("Widget", "Widget", nullptr));
        btnInquire->setText(QCoreApplication::translate("Widget", "\346\237\245\350\257\242", nullptr));
        btnAdd->setText(QCoreApplication::translate("Widget", "\345\224\256\350\264\247", nullptr));
        btnDelete->setText(QCoreApplication::translate("Widget", "\351\200\200\350\264\247", nullptr));
        btnSupply->setText(QCoreApplication::translate("Widget", "\350\241\245\350\264\247", nullptr));
        btnRefresh->setText(QCoreApplication::translate("Widget", "\345\210\267\346\226\260", nullptr));
        pushButton->setText(QCoreApplication::translate("Widget", "test", nullptr));
    } // retranslateUi

};

namespace Ui {
    class Widget: public Ui_Widget {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_WIDGET_H
