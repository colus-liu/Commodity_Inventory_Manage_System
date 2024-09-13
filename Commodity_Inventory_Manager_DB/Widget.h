#ifndef WIDGET_H
#define WIDGET_H

#include <QWidget>
#include "CDataSourceSQLite.h"
#include <QStandardItemModel>
#include "ShowSaleRecordsDialog.h"
#include "AddSaleRecordDialog.h"
#include "DeleteSaleRecordDialog.h"
#include "SupplyDialog.h"

QT_BEGIN_NAMESPACE
namespace Ui {
class Widget;
}
QT_END_NAMESPACE

class Widget : public QWidget
{
    Q_OBJECT

public:
    Widget(QWidget *parent = nullptr);
    ~Widget();

    bool appendProductToModel(CProduct &product);

signals:
    void sig_showSaleRecords(QList<CSaleRecord> &saleRecordList);

private slots:
    void on_btnInquire_clicked();

    void on_btnAdd_clicked();

    void slot_addSaleRecord(QString &orderId, int &quantity, double &discountRate, QDate &orderDate, QString &contactPhone);

    void on_btnRefresh_clicked();

    void slot_deleteSaleRecord(QString &orderId);

    void on_btnDelete_clicked();

    void on_btnSupply_clicked();

    void slot_updataProduct(int &supplyQuantity);

private:
    Ui::Widget *ui;
    CDataSourceSQLite *m_dataSource; // 数据源
    QStandardItemModel *m_productModel; // 商品信息模型

    ShowSaleRecordsDialog *m_showSaleRecordDlg; // 显示销售信息对话框
    AddSaleRecordDialog *m_addSaleRecordDlg; // 添加销售信息对话框
    DeleteSaleRecordDialog *m_deleteSaleRecordDlg; // 删除销售信息对话框
    SupplyDialog * m_supplyDlg; // 补货对话框

    void initUI(); // 初始化界面

};
#endif // WIDGET_H
