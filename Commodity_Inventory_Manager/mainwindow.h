#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QStandardItemModel>
#include "CInventorySystem.h"
#include "InquireSaleRecordsDialog.h"
#include "AddSaleRecordDialog.h"
#include "DeleteSaleRecordDialog.h"
#include "InventorySupplyDialog.h"

QT_BEGIN_NAMESPACE
namespace Ui {
class MainWindow;
}
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

    // 在表格中显示商品信息表
    void ShowProductsTable();
    // 在表格中显示指定商品的销售信息表
    void ShowSaleRecordsTable(QString &id);

private slots:
    void on_actionOpen_triggered();

    void on_actionSave_triggered();

    void on_actionInquire_triggered();

    bool slot_inquireSaleRecords(QString &id);

    bool slot_addSaleRecord(CSaleRecord &saleRecord, QString &id);

    bool slot_deleteSaleRecord(QString &id, QString &orderId);

    bool slot_inventorySupply(QString &id, int &addQuantity);

    void on_actionAdd_triggered();

    void on_actionDelete_triggered();

    void on_actionSupply_triggered();


    void on_btnShowProductInfo_clicked();

private:
    Ui::MainWindow *ui;
    QStandardItemModel *productInfoModel; //显示商品表格信息数据模型
    QStandardItemModel *saleRecordInfoModel; // 显示销售信息数据模型
    CInventorySystem m_InfoTable; // 数据汇总类
    InquireSaleRecordsDialog *m_inquireSaleRecords; // 查询销售信息窗口
    AddSaleRecordDialog *m_addSaleRecordDialog; // 增加销售信息窗口（售货）
    DeleteSaleRecordDialog *m_deleteSaleRecordDialog; // 删除销售信息窗口（退货）
    InventorySupplyDialog *m_inventorySupplyDialog; // 商品补货窗口

};
#endif // MAINWINDOW_H
