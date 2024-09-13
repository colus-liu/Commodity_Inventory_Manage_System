#ifndef ADDSALERECORDDIALOG_H
#define ADDSALERECORDDIALOG_H

#include <QDialog>
#include "CSaleRecord.h"

namespace Ui {
class AddSaleRecordDialog;
}

class AddSaleRecordDialog : public QDialog
{
    Q_OBJECT

public:
    explicit AddSaleRecordDialog(QWidget *parent = nullptr);
    ~AddSaleRecordDialog();

    void initUI();
    bool clearData();

// 声明了一个名为 sig_addSaleRecord 的信号，它接受一个 CSaleRecord 类型的引用作为参数。当这个信号被发射时，它可以传递一个 CSaleRecord 类型对象的引用给所有连接的槽函数。
signals:
    void sig_addSaleRecord(CSaleRecord &saleRecord, QString &id);

private slots:
    void on_btnConfirm_clicked();

    void on_btnCancel_clicked();

private:
    Ui::AddSaleRecordDialog *ui;
};

#endif // ADDSALERECORDDIALOG_H
