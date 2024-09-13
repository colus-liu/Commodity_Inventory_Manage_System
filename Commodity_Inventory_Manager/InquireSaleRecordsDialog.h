#ifndef INQUIRESALERECORDSDIALOG_H
#define INQUIRESALERECORDSDIALOG_H

#include <QDialog>

namespace Ui {
class InquireSaleRecordsDialog;
}

class InquireSaleRecordsDialog : public QDialog
{
    Q_OBJECT

public:
    explicit InquireSaleRecordsDialog(QWidget *parent = nullptr);
    ~InquireSaleRecordsDialog();

    QString Id(); // 返回商品编号

    bool clearData();

signals:
    void sig_inquireSaleRecords(QString &id);


private slots:
    void on_btnCancel_clicked();

    void on_btnConfirm_clicked();

private:
    Ui::InquireSaleRecordsDialog *ui;
    void initUI();
};

#endif // INQUIRESALERECORDSDIALOG_H
