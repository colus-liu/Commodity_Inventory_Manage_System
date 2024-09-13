#include "Widget.h"
#include "ui_Widget.h"
#include <QStandardItemModel>
#include <QMenu>
#include <QMessageBox>
#include "ShowSaleRecordsDialog.h"
#include "AddSaleRecordDialog.h"

#include <QDebug>

Widget::Widget(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::Widget)
    , m_dataSource(NULL)
    , m_productModel(NULL)
    , m_showSaleRecordDlg(NULL)
    , m_addSaleRecordDlg(NULL)
    , m_deleteSaleRecordDlg(NULL)
    , m_supplyDlg(NULL)

{
    ui->setupUi(this);
    qRegisterMetaType<CSaleRecord>("CSaleRecord");
    //qRegisterMetaType 函数用于在运行时注册自定义类型，使其可以被用于跨线程的信号和槽通信等操作。这通常在使用 Q_DECLARE_METATYPE 宏之后进行。


    // 实例化数据源
    m_dataSource = new CDataSourceSQLite();

    // 实例化商品信息模型
    m_productModel = new QStandardItemModel();

    // 实例化对话框
    m_showSaleRecordDlg = new ShowSaleRecordsDialog();
    m_addSaleRecordDlg = new AddSaleRecordDialog();
    m_deleteSaleRecordDlg = new DeleteSaleRecordDialog();
    m_supplyDlg = new SupplyDialog();

    // 连接槽函数
    connect(this, &Widget::sig_showSaleRecords,m_showSaleRecordDlg,&ShowSaleRecordsDialog::slot_showSaleRecords);
    connect(m_addSaleRecordDlg,&AddSaleRecordDialog::sig_addSaleRecord,this,&Widget::slot_addSaleRecord);
    connect(m_deleteSaleRecordDlg,&DeleteSaleRecordDialog::sig_deleteSaleRecord,this,&Widget::slot_deleteSaleRecord);
    connect(m_supplyDlg,&SupplyDialog::sig_updateProduct,this,&Widget::slot_updataProduct);

    // 初始化界面
    initUI();
}

Widget::~Widget()
{
    delete ui;
    delete m_dataSource;
}

// 将单个商品信息对象 CProduct 的数据(包括利润和剩余库存量)添加到 m_productModel 模型中
bool Widget::appendProductToModel(CProduct &product)
{
    // 为每个商品信息字段创建 QStandardItem 对象
    QStandardItem *itemId = new QStandardItem(product.getId());
    itemId->setCheckable(true); //为商品编号这一列添加复选框
    QStandardItem *itemName = new QStandardItem(product.getName());
    QStandardItem *itemQuantity = new QStandardItem(QString::number(product.getTotalQuantity()));
    QStandardItem *itemPurchasePrice = new QStandardItem(QString::number(product.getPurchasePrice()));
    QStandardItem *itemSalePrice = new QStandardItem(QString::number(product.getSalePrice()));
    QStandardItem *itemManufacturer = new QStandardItem(product.getManufacturer());
    QStandardItem *itemProductionDate = new QStandardItem(product.getProductionDate().toString("yyyy-MM-dd"));
    QStandardItem *itemExpirationDate = new QStandardItem(product.getExpirationDate().toString("yyyy-MM-dd"));
    QStandardItem *itemProfit = new  QStandardItem(QString::number(product.getProfit()));
    QStandardItem *itemLeftQuantity = new QStandardItem(QString::number(product.getLeftQuantity()));

    // 将每一列的内容在单元格中居中
    itemId->setTextAlignment(Qt::AlignHCenter | Qt::AlignVCenter);
    itemName->setTextAlignment(Qt::AlignHCenter | Qt::AlignVCenter);
    itemQuantity->setTextAlignment(Qt::AlignHCenter | Qt::AlignVCenter);
    itemPurchasePrice->setTextAlignment(Qt::AlignHCenter | Qt::AlignVCenter);
    itemSalePrice->setTextAlignment(Qt::AlignHCenter | Qt::AlignVCenter);
    itemManufacturer->setTextAlignment(Qt::AlignHCenter | Qt::AlignVCenter);
    itemProductionDate->setTextAlignment(Qt::AlignHCenter | Qt::AlignVCenter);
    itemExpirationDate->setTextAlignment(Qt::AlignHCenter | Qt::AlignVCenter);
    itemProfit->setTextAlignment(Qt::AlignHCenter | Qt::AlignVCenter);
    itemLeftQuantity->setTextAlignment(Qt::AlignHCenter | Qt::AlignVCenter);

    // 创建一个列表来存储这一行的所有项目
    QList<QStandardItem*> rowItem;
    rowItem.append(itemId);
    rowItem.append(itemName);
    rowItem.append(itemQuantity);
    rowItem.append(itemPurchasePrice);
    rowItem.append(itemSalePrice);
    rowItem.append(itemManufacturer);
    rowItem.append(itemProductionDate);
    rowItem.append(itemExpirationDate);
    rowItem.append(itemProfit);
    rowItem.append(itemLeftQuantity);

    m_productModel->appendRow(rowItem); // 将这一行的项目添加到商品信息模型中

    return true;
}


// 初始化界面
void Widget::initUI()
{
    // 查询数据
    // 查询商品信息，并将结果存储在 productList 中
    QList<CProduct> productList;
    bool res1 = m_dataSource->selectProducts(productList);
    if(!res1)
    {
        QMessageBox::information(this,"提示","查询商品信息失败");
        return;
    }
    // 查询销售信息，并将结果存储在 saleRecordList 中
    QList<CSaleRecord> saleRecordList;
    bool res2 = m_dataSource->selectSaleRecords(saleRecordList);
    if(!res2)
    {
        QMessageBox::information(this,"提示","查询销售信息失败");
        return;
    }
    // 把saleRecordList中productId和某商品的id一样的加到该商品的saleRecords_中，然后计算该商品的利润和剩余库存量
    for(int i=0; i<productList.size(); ++i)
    {
        for(int j=0; j<saleRecordList.size(); ++j)
        {
            if(saleRecordList[j].getProductId() == productList[i].getId())
            {
                productList[i].addSaleRecord(saleRecordList[j]);
            }
        }
        productList[i].setSaleRecordsNum(); // 先设置销售信息条数，再计算利润和剩余库存量
        productList[i].setProfit();
        productList[i].setLeftQuantity();
    }


    for(int i=0; i<productList.size(); ++i) // 遍历商品信息列表，并将每条商品信息添加到模型中
    {
        appendProductToModel(productList[i]);
    }

    // 设置表格的水平表头
    QStringList headerList;
    headerList<<"商品编号"<<"商品名称"<<"总数量"<<"进价"<<"售价"<<"生产商"<<"生产日期"<<"保质期"<<"利润"<<"剩余库存";
    m_productModel->setHorizontalHeaderLabels(headerList);

    // tbStudentInfo是控件TableView的重命名
    ui->tbInfo->verticalHeader()->setVisible(false); // 隐藏垂直表头，否则在表格左侧会有1，2，3等这样的垂直标号

    ui->tbInfo->setEditTriggers(QAbstractItemView::NoEditTriggers); // 设置表格为不可编辑状态，若不这样设置则每个格子都可以点击并编辑

    ui->tbInfo->setModel(m_productModel); // 将模型设置到表格视图 tbInfo

    // 遍历所有10列，并将每列的宽度设置为表格宽度除以10（减去20作为边距）
    for(int col=0; col<10; ++col)
    {
        ui->tbInfo->setColumnWidth(col,(width()-20)/10);
    }

}


void Widget::on_btnInquire_clicked()
{
    // 查询所有销售信息，并将结果存储在 saleRecordList 中
    QList<CSaleRecord> saleRecordList;
    bool res = m_dataSource->selectSaleRecords(saleRecordList);
    if(!res)
    {
        QMessageBox::information(this,"提示","查询销售信息失败");
        return;
    }

    // 遍历所有商品信息行，找到被选择的商品并获取商品编号
    int cnt = 0;
    QString id;
    QModelIndex index;
    for(int row=0; row<m_productModel->rowCount(); ++row)
    {
        QStandardItem *item = m_productModel->item(row);
        if(item->checkState()==Qt::Checked)
        {
            cnt++;
            index = m_productModel->index(row, 0); // 获取id的索引
            // 获取索引处的数据，Qt::DisplayRole 用于获取用于显示的数据
            QVariant value = m_productModel->data(index, Qt::DisplayRole);
            // 根据需要将 QVariant 转换为相应的类型
            id = value.toString();
        }
    }

    // 遍历 saleRecordList ，查找对应商品的销售信息
    QList<CSaleRecord> theSaleRecordList;
    for(int i=0; i<saleRecordList.size(); ++i)
    {
        if(saleRecordList[i].getProductId() == id)
        {
            theSaleRecordList.append(saleRecordList[i]);
        }
    }

    if(cnt == 0)
    {
        QMessageBox::information(this,"提示","请选择一个商品！！");
        return;
    }
    if(cnt == 1)
    {
        emit sig_showSaleRecords(theSaleRecordList);
        return;
    }
    else
    {
        QMessageBox::information(this,"提示","只能选择一个商品！！");
        return;
    }
}


void Widget::on_btnAdd_clicked()
{
    // 判断是否只选择了一个商品
    int cnt = 0;
    for(int row=0; row<m_productModel->rowCount(); ++row)
    {
        QStandardItem *item = m_productModel->item(row);
        if(item->checkState()==Qt::Checked)
        {
            cnt++;
        }
    }
    if(cnt == 0)
    {
        QMessageBox::information(this,"提示","请选择一个商品！！");
        return;
    }
    if(cnt == 1)
    {
        m_addSaleRecordDlg->show();
    }
    else
    {
        QMessageBox::information(this,"提示","只能选择一个商品！！");
        return;
    }

}

void Widget::slot_addSaleRecord(QString &orderId, int &quantity, double &discountRate, QDate &orderDate, QString &contactPhone)
{
    // 查询所有销售信息，并将结果存储在 saleRecordList 中
    QList<CSaleRecord> saleRecordList;
    bool res = m_dataSource->selectSaleRecords(saleRecordList);
    if(!res)
    {
        QMessageBox::information(this,"提示","查询销售信息失败");
        return;
    }

    // 遍历所有商品信息行，找到被选择的商品并获取商品编号
    QString id;
    QModelIndex index;
    for(int row=0; row<m_productModel->rowCount(); ++row)
    {
        QStandardItem *item = m_productModel->item(row);
        if(item->checkState()==Qt::Checked)
        {
            index = m_productModel->index(row, 0); // 获取id的索引
            // 获取索引处的数据，Qt::DisplayRole 用于获取用于显示的数据
            QVariant value = m_productModel->data(index, Qt::DisplayRole);
            // 根据需要将 QVariant 转换为相应的类型
            id = value.toString();
        }
    }

    // 判断订单号是否与数据库中的订单号重复
    for(int i=0; i<saleRecordList.size(); ++i)
    {
        if(orderId==saleRecordList[i].getOrderId())
        {
            QMessageBox::information(this,"提示","订单号重复！！");
            return;
        }
    }

    // 向数据库中添加销售信息
    CSaleRecord saleRecord(orderId,quantity,discountRate,orderDate,contactPhone,id);
    m_dataSource->addSaleRecord(saleRecord);

    QMessageBox::information(this,"提示","售货成功！！");
}


void Widget::on_btnRefresh_clicked()
{
    m_productModel->removeRows(0, m_productModel->rowCount());
    initUI();
}

void Widget::slot_deleteSaleRecord(QString &orderId)
{
    // 判断订单号是否存在
    QList<CSaleRecord> saleRecordList; // 查询所有销售信息，并将结果存储在 saleRecordList 中
    bool found = false;
    bool res = m_dataSource->selectSaleRecords(saleRecordList);
    if(!res)
    {
        QMessageBox::information(this,"提示","无法获取销售信息");
        return;
    }
    else
    {
        for(int i=0; i<saleRecordList.size(); ++i)
        {
            if(orderId == saleRecordList[i].getOrderId())
            {
                found = true;
            }
        }
    }
    if(!found)
    {
        QMessageBox::information(this,"提示","订单号不存在！！");
        return;
    }

    m_dataSource->deleteSaleRecord(orderId);
    QMessageBox::information(this,"提示","退货成功！！");
}

void Widget::on_btnDelete_clicked()
{
    m_deleteSaleRecordDlg->show();
}


void Widget::on_btnSupply_clicked()
{
    // 判断是否只选择了一个商品
    int cnt = 0;
    for(int row=0; row<m_productModel->rowCount(); ++row)
    {
        QStandardItem *item = m_productModel->item(row);
        if(item->checkState()==Qt::Checked)
        {
            cnt++;
        }
    }
    if(cnt == 0)
    {
        QMessageBox::information(this,"提示","请选择一个商品！！");
        return;
    }
    if(cnt == 1)
    {
        m_supplyDlg->show();
    }
    else
    {
        QMessageBox::information(this,"提示","只能选择一个商品！！");
        return;
    }
}

void Widget::slot_updataProduct(int &supplyQuantity)
{
    // 遍历所有商品信息行，找到被选择的商品并获取商品编号
    QString id;
    QModelIndex index;
    for(int row=0; row<m_productModel->rowCount(); ++row)
    {
        QStandardItem *item = m_productModel->item(row);
        if(item->checkState()==Qt::Checked)
        {
            index = m_productModel->index(row, 0); // 获取id的索引
            // 获取索引处的数据，Qt::DisplayRole 用于获取用于显示的数据
            QVariant value = m_productModel->data(index, Qt::DisplayRole);
            // 根据需要将 QVariant 转换为相应的类型
            id = value.toString();
        }
    }

    // 修改商品信息
    m_dataSource->updateProduct(id,supplyQuantity);

    QMessageBox::information(this,"提示","补货成功");
}

