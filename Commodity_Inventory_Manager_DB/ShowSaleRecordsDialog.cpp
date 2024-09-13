#include "ShowSaleRecordsDialog.h"
#include "ui_ShowSaleRecordsDialog.h"
#include <QMessageBox>

#include <QDebug>

ShowSaleRecordsDialog::ShowSaleRecordsDialog(QWidget *parent)
    : QDialog(parent)
    , ui(new Ui::ShowSaleRecordsDialog)
    , m_saleRecordModel(NULL)
{
    ui->setupUi(this);
    setWindowTitle("销售信息显示");

    // 实例化销售信息模型
    m_saleRecordModel = new QStandardItemModel();

}

ShowSaleRecordsDialog::~ShowSaleRecordsDialog()
{
    delete ui;
    delete m_saleRecordModel;
}

// 将单个销售信息对象 CSaleRecord 的数据(不包括商品编号orderId)添加到 m_saleRecordModel 模型中
bool ShowSaleRecordsDialog::appendSaleRecordToModel(CSaleRecord &saleRecord)
{
    // 为每个销售信息字段创建 QStandardItem 对象
    QStandardItem *itemOrderId = new QStandardItem(saleRecord.getOrderId());
    QStandardItem *itemQuantity = new QStandardItem(QString::number(saleRecord.getQuantity()));
    QStandardItem *itemDiscountRate = new QStandardItem(QString::number(saleRecord.getDiscountRate()));
    QStandardItem *itemOrderDate = new QStandardItem(saleRecord.getOrderDate().toString("yyyy-MM-dd"));
    QStandardItem *itemContactPhone = new QStandardItem(saleRecord.getContactPhone());

    // 将每一列的内容在单元格中居中
    itemOrderId->setTextAlignment(Qt::AlignHCenter | Qt::AlignVCenter);
    itemQuantity->setTextAlignment(Qt::AlignHCenter | Qt::AlignVCenter);
    itemDiscountRate->setTextAlignment(Qt::AlignHCenter | Qt::AlignVCenter);
    itemOrderDate->setTextAlignment(Qt::AlignHCenter | Qt::AlignVCenter);
    itemContactPhone->setTextAlignment(Qt::AlignHCenter | Qt::AlignVCenter);

    // 创建一个列表来存储这一行的所有项目
    QList<QStandardItem*> rowItem;
    rowItem.append(itemOrderId);
    rowItem.append(itemQuantity);
    rowItem.append(itemDiscountRate);
    rowItem.append(itemOrderDate);
    rowItem.append(itemContactPhone);

    m_saleRecordModel->appendRow(rowItem); // 将这一行的项目添加到销售信息模型中

    return true;
}


void ShowSaleRecordsDialog::on_btnExit_clicked()
{
    this->close();
}

bool ShowSaleRecordsDialog::slot_showSaleRecords(QList<CSaleRecord> &theSaleRecordList)
{
    // 先清空模型中的数据
    m_saleRecordModel->removeRows(0, m_saleRecordModel->rowCount());

    // 遍历 theSaleRecordList ，查找对应商品的销售信息并添加到销售信息模型中
    for(int i=0; i<theSaleRecordList.size(); ++i)
    {
        appendSaleRecordToModel(theSaleRecordList[i]);
    }

    // 设置表格的水平表头
    QStringList headerList;
    headerList<<"订单号"<<"数量"<<"折扣率"<<"销售日期"<<"联系电话";
    m_saleRecordModel->setHorizontalHeaderLabels(headerList);

    // tb_saleRecordInfo 是控件TableView的重命名
    ui->tb_saleRecordInfo->verticalHeader()->setVisible(false); // 隐藏垂直表头，否则在表格左侧会有1，2，3等这样的垂直标号
    ui->tb_saleRecordInfo->setEditTriggers(QAbstractItemView::NoEditTriggers); // 设置表格为不可编辑状态，若不这样设置则每个格子都可以点击并编辑
    ui->tb_saleRecordInfo->setModel(m_saleRecordModel); // 将模型设置到表格视图 tb_saleRecordInfo

    // 遍历所有5列，并将每列的宽度设置为表格宽度除以5（减去20作为边距）
    for(int col=0; col<5; ++col)
    {
        ui->tb_saleRecordInfo->setColumnWidth(col,(width()-20)/5);
    }

    this->show();
    return true;
}

