#ifndef ADDSALERECORDDIALOG_H
#define ADDSALERECORDDIALOG_H

#include <QDialog>
//#include "CSaleRecord.h"

namespace Ui {
class AddSaleRecordDialog;
}

class AddSaleRecordDialog : public QDialog
{
    Q_OBJECT

public:
    explicit AddSaleRecordDialog(QWidget *parent = nullptr);
    ~AddSaleRecordDialog();

    bool clearData();

signals:
    void sig_addSaleRecord(QString &orderId, int &quantity, double &discountRate, QDate &orderDate, QString &contactPhone);

private slots:
    void on_btnCancel_clicked();

    void on_btnConfirm_clicked();

private:
    Ui::AddSaleRecordDialog *ui;
    void initUI();
};

#endif // ADDSALERECORDDIALOG_H
