#ifndef DELETESALERECORDDIALOG_H
#define DELETESALERECORDDIALOG_H

#include <QDialog>

namespace Ui {
class DeleteSaleRecordDialog;
}

class DeleteSaleRecordDialog : public QDialog
{
    Q_OBJECT

public:
    explicit DeleteSaleRecordDialog(QWidget *parent = nullptr);
    ~DeleteSaleRecordDialog();

    void initUI();
    bool clearData();

// 声明一个名为 sig_deleteSaleRecord 的信号
signals:
    void sig_deleteSaleRecord(QString &id, QString &orderId);

private slots:
    void on_btnConfirm_clicked();

    void on_btnCancel_clicked();

private:
    Ui::DeleteSaleRecordDialog *ui;
};

#endif // DELETESALERECORDDIALOG_H
