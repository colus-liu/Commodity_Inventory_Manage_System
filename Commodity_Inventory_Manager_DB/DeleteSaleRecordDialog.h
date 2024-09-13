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

    void clearData();

signals:
    void sig_deleteSaleRecord(QString &orderId);


private slots:
    void on_btnConfirm_clicked();

    void on_btnCancel_clicked();

private:
    Ui::DeleteSaleRecordDialog *ui;
    void initUI();
};

#endif // DELETESALERECORDDIALOG_H
