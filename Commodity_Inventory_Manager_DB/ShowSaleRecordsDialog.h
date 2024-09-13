#ifndef SHOWSALERECORDSDIALOG_H
#define SHOWSALERECORDSDIALOG_H

#include <QDialog>
#include "CSaleRecord.h"
#include <QStandardItemModel>

namespace Ui {
class ShowSaleRecordsDialog;
}

class ShowSaleRecordsDialog : public QDialog
{
    Q_OBJECT

public:
    explicit ShowSaleRecordsDialog(QWidget *parent = nullptr);
    ~ShowSaleRecordsDialog();

    bool appendSaleRecordToModel(CSaleRecord &saleRecord);


public slots:
    void on_btnExit_clicked();
    bool slot_showSaleRecords(QList<CSaleRecord> &theSaleRecordList);

private:
    Ui::ShowSaleRecordsDialog *ui;
    QStandardItemModel *m_saleRecordModel; // 销售信息模型
};

#endif // SHOWSALERECORDSDIALOG_H
