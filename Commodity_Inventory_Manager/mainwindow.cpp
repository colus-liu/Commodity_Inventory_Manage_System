#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "CInventorySystem.h"
#include <QFileDialog>
#include "InquireSaleRecordsDialog.h"
#include <QFileInfo>
#include <QFile>
#include <QMessageBox>
#include <QDebug>
#include <QMetaType>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
    , productInfoModel(NULL)
    , saleRecordInfoModel(NULL)
    , m_inquireSaleRecords(NULL)
    , m_addSaleRecordDialog(NULL)
    , m_deleteSaleRecordDialog(NULL)
    , m_inventorySupplyDialog(NULL)
{
    ui->setupUi(this);
    qRegisterMetaType<CSaleRecord>("CSaleRecord");

    // 创建两个不同的信息显示表格模型
    productInfoModel = new QStandardItemModel();
    saleRecordInfoModel = new QStandardItemModel();

    // 实例化查询，增加，删除销售信息窗口
    m_inquireSaleRecords = new InquireSaleRecordsDialog(this);
    m_addSaleRecordDialog = new AddSaleRecordDialog(this);
    m_deleteSaleRecordDialog = new DeleteSaleRecordDialog(this);
    m_inventorySupplyDialog = new InventorySupplyDialog(this);

    // 关联查询销售信息槽函数
    connect(m_inquireSaleRecords,&InquireSaleRecordsDialog::sig_inquireSaleRecords,this,&MainWindow::slot_inquireSaleRecords);
    connect(m_addSaleRecordDialog,&AddSaleRecordDialog::sig_addSaleRecord,this,&MainWindow::slot_addSaleRecord);
    connect(m_deleteSaleRecordDialog,&DeleteSaleRecordDialog::sig_deleteSaleRecord,this,&MainWindow::slot_deleteSaleRecord);
    connect(m_inventorySupplyDialog,&InventorySupplyDialog::sig_inventorySupply,this,&MainWindow::slot_inventorySupply);


}

MainWindow::~MainWindow()
{
    delete ui;
    delete productInfoModel;
    delete saleRecordInfoModel;
    delete m_inquireSaleRecords;
    delete m_addSaleRecordDialog;
    delete m_deleteSaleRecordDialog;
    delete m_inventorySupplyDialog;
}

void MainWindow::on_actionOpen_triggered()
{
    QString curPath = QDir::currentPath();
    QString dlgTitle = "选择一个文件";
    QString filter = "文本文件(*.txt);;所有文件(*.*)";
    QString aFileName = QFileDialog::getOpenFileName(this, dlgTitle, curPath, filter);

    if(aFileName.isEmpty())
        return;

    // 读取文件
    m_InfoTable.ReadProductFromFile(aFileName);

    // 显示商品信息
    ui->tb_ShowInfo->setModel(productInfoModel);
    ShowProductsTable();

    // 判断那些商品需要补货，并依次输出提示框
    for(int i=0; i<m_InfoTable.GetProductsNum(); ++i)
    {
        if(m_InfoTable.GetProduct(i).getLeftQuantity() <= 0)
        {
            QString id = m_InfoTable.GetProduct(i).getId();
            QString tip = "%1需要补货";
            QMessageBox::information(this, "提示", tip.arg(id), QMessageBox::Ok);
        }
    }
}

void MainWindow::ShowProductsTable()
{
    productInfoModel->clear();
    productInfoModel->setColumnCount(10); //10列

    //表头
    //名称、编号、总数量、进价、售价、生产厂家、生产日期、保质期、利润、剩余库存
    QStringList templist;
    templist.append("名称");
    templist.append("编号");
    templist.append("总数量");
    templist.append("进价");
    templist.append("售价");
    templist.append("生产厂家");
    templist.append("生产日期");
    templist.append("保质期");
    templist.append("利润");
    templist.append("剩余库存");
    productInfoModel->setHorizontalHeaderLabels(templist);

    int RowCnt = m_InfoTable.GetProductsNum(); //行数（不含标题）
    productInfoModel->setRowCount(RowCnt);

    //遍历，插入数据
    QStandardItem *aTempItem; //临时的item
    QString tempStr;
    for(int i=0; i<RowCnt; ++i)
    {
        CProduct tempproduct=m_InfoTable.GetProduct(i);

        aTempItem = new QStandardItem(tempproduct.getName());
        productInfoModel->setItem(i, 0, aTempItem);
        aTempItem->setTextAlignment(Qt::AlignHCenter | Qt::AlignVCenter); // 将内容在单元格中居中

        aTempItem = new QStandardItem(tempproduct.getId());
        productInfoModel->setItem(i, 1, aTempItem);
        aTempItem->setTextAlignment(Qt::AlignHCenter | Qt::AlignVCenter);

        tempStr = QString::number(tempproduct.getTotalQuantity());
        aTempItem = new QStandardItem(tempStr);
        productInfoModel->setItem(i, 2, aTempItem);
        aTempItem->setTextAlignment(Qt::AlignHCenter | Qt::AlignVCenter);

        tempStr = QString::number(tempproduct.getPurchasePrice());
        aTempItem = new QStandardItem(tempStr);
        productInfoModel->setItem(i, 3, aTempItem);
        aTempItem->setTextAlignment(Qt::AlignHCenter | Qt::AlignVCenter);

        tempStr = QString::number(tempproduct.getSalePrice());
        aTempItem = new QStandardItem(tempStr);
        productInfoModel->setItem(i, 4, aTempItem);
        aTempItem->setTextAlignment(Qt::AlignHCenter | Qt::AlignVCenter);

        aTempItem = new QStandardItem(tempproduct.getManufacturer());
        productInfoModel->setItem(i, 5, aTempItem);
        aTempItem->setTextAlignment(Qt::AlignHCenter | Qt::AlignVCenter);

        tempStr = tempproduct.getProductionDate().toString("yyyy-MM-dd");
        aTempItem = new QStandardItem(tempStr);
        productInfoModel->setItem(i, 6, aTempItem);
        aTempItem->setTextAlignment(Qt::AlignHCenter | Qt::AlignVCenter);

        tempStr = tempproduct.getExpirationDate().toString("yyyy-MM-dd");
        aTempItem = new QStandardItem(tempStr);
        productInfoModel->setItem(i, 7, aTempItem);
        aTempItem->setTextAlignment(Qt::AlignHCenter | Qt::AlignVCenter);

        tempStr = QString::number(tempproduct.getProfit());
        aTempItem = new QStandardItem(tempStr);
        productInfoModel->setItem(i, 8, aTempItem);
        aTempItem->setTextAlignment(Qt::AlignHCenter | Qt::AlignVCenter);

        tempStr = QString::number(tempproduct.getLeftQuantity());
        aTempItem = new QStandardItem(tempStr);
        productInfoModel->setItem(i, 9, aTempItem);
        aTempItem->setTextAlignment(Qt::AlignHCenter | Qt::AlignVCenter);
    }
    ui->tb_ShowInfo->verticalHeader()->setVisible(false); // 隐藏垂直表头，否则在表格左侧会有1，2，3等这样的垂直标号
    ui->tb_ShowInfo->setEditTriggers(QAbstractItemView::NoEditTriggers); // 设置表格为不可编辑状态，否则每个格子都可以点击并编辑
}


void MainWindow::on_actionInquire_triggered()
{
    // 运行查询对话框
    m_inquireSaleRecords->show();
}

bool MainWindow::slot_inquireSaleRecords(QString &id)
{
    // 判断库存中是否有该商品，若没有则输出提示框
    bool found = false;
    for(int i=0; i<m_InfoTable.GetProductsNum(); ++i)
    {
        if(id == m_InfoTable.GetProduct(i).getId())
        {
            found = true;
            break;
        }
    }
    if(!found)
    {
        QMessageBox::information(this,"提示","库存中无该商品！");
        return false;
    }

    // 根据对话框中输入的商品编号来显示对应商品的销售信息
    ui->tb_ShowInfo->setModel(saleRecordInfoModel);
    ShowSaleRecordsTable(id);
    return true;
}

void MainWindow::ShowSaleRecordsTable(QString &id)
{
    saleRecordInfoModel->clear();
    saleRecordInfoModel->setColumnCount(5); //5列

    //表头
    //订单号、销售数量、折扣率、销售日期、联系电话
    QStringList templist;
    templist.append("订单号");
    templist.append("销售数量");
    templist.append("折扣率");
    templist.append("销售日期");
    templist.append("联系电话");
    saleRecordInfoModel->setHorizontalHeaderLabels(templist);

    int RowCnt = m_InfoTable.GetProduct(id).GetSaleRecordsNum();
    saleRecordInfoModel->setRowCount(RowCnt);

    //遍历，插入数据
    QStandardItem *aTempItem; //临时的item
    QString tempStr;
    for(int i=0; i<RowCnt; ++i)
    {
        CSaleRecord tempsaleRecord=m_InfoTable.GetProduct(id).GetSaleRecord(i);

        aTempItem = new QStandardItem(tempsaleRecord.getOrderId());
        saleRecordInfoModel->setItem(i, 0, aTempItem);
        aTempItem->setTextAlignment(Qt::AlignHCenter | Qt::AlignVCenter); // 将内容在单元格中居中

        tempStr = QString::number(tempsaleRecord.getQuantity());
        aTempItem = new QStandardItem(tempStr);
        saleRecordInfoModel->setItem(i, 1, aTempItem);
        aTempItem->setTextAlignment(Qt::AlignHCenter | Qt::AlignVCenter);

        tempStr = QString::number(tempsaleRecord.getDiscountRate());
        aTempItem = new QStandardItem(tempStr);
        saleRecordInfoModel->setItem(i, 2, aTempItem);
        aTempItem->setTextAlignment(Qt::AlignHCenter | Qt::AlignVCenter);

        tempStr = tempsaleRecord.getOrderDate().toString("yyyy-MM-dd");
        aTempItem = new QStandardItem(tempStr);
        saleRecordInfoModel->setItem(i, 3, aTempItem);
        aTempItem->setTextAlignment(Qt::AlignHCenter | Qt::AlignVCenter);

        aTempItem = new QStandardItem(tempsaleRecord.getContactPhone());
        saleRecordInfoModel->setItem(i, 4, aTempItem);
        aTempItem->setTextAlignment(Qt::AlignHCenter | Qt::AlignVCenter);
    }
    ui->tb_ShowInfo->verticalHeader()->setVisible(false); // 隐藏垂直表头，否则在表格左侧会有1，2，3等这样的垂直标号
    ui->tb_ShowInfo->setEditTriggers(QAbstractItemView::NoEditTriggers); // 设置表格为不可编辑状态
}


bool MainWindow::slot_addSaleRecord(CSaleRecord &saleRecord, QString &id)
{
    // 判断库存中是否有该商品，若没有则输出提示框
    bool found = false;
    for(int i=0; i<m_InfoTable.GetProductsNum(); ++i)
    {
        if(id == m_InfoTable.GetProduct(i).getId())
        {
            found = true;
            break;
        }
    }
    if(!found)
    {
        QMessageBox::information(this,"提示","库存中无该商品！");
        return false;
    }

    // 判断该商品是否有该订单，若有则输出提示框
    bool unfound = true;
    for(int i=0; i<m_InfoTable.GetProduct(id).GetSaleRecordsNum(); ++i)
    {
        if(saleRecord.getOrderId() == m_InfoTable.GetProduct(id).GetSaleRecord(i).getOrderId())
        {
            unfound = false;
            break;
        }
    }
    if(!unfound)
    {
        QMessageBox::information(this,"提示","订单号已存在！");
        return false;
    }

    m_InfoTable.GetProduct(id).addSaleRecord(saleRecord);
    m_InfoTable.GetProduct(id).setSaleRecordsNum(); // 重置销售信息数量
    // 将销售记录写入了文件流，并未保存，保存在后面实现，每次添加后需要点击保存才能保存新添加的销售信息。
    QMessageBox::information(this,"提示","售货成功，请及时保存修改信息！");

    return true;
}

bool MainWindow::slot_deleteSaleRecord(QString &id, QString &orderId)
{
    // 判断库存中是否有该商品，若没有则输出提示框
    bool found1 = false;
    for(int i=0; i<m_InfoTable.GetProductsNum(); ++i)
    {
        if(id == m_InfoTable.GetProduct(i).getId())
        {
            found1 = true;
            break;
        }
    }
    if(!found1)
    {
        QMessageBox::information(this,"提示","库存中无该商品！");
        return false;
    }

    // 判断该商品是否有该订单，若没有则输出提示框
    bool found2 = false;
    for(int i=0; i<m_InfoTable.GetProduct(id).GetSaleRecordsNum(); ++i)
    {
        if(orderId == m_InfoTable.GetProduct(id).GetSaleRecord(i).getOrderId())
        {
            found2 = true;
            break;
        }
    }
    if(!found2)
    {
        QMessageBox::information(this,"提示","该订单不存在！");
        return false;
    }

    m_InfoTable.GetProduct(id).removeSaleRecord(orderId);
    m_InfoTable.GetProduct(id).setSaleRecordsNum();
    QMessageBox::information(this,"提示","退货成功，请及时保存修改信息！");
    return true;
}

bool MainWindow::slot_inventorySupply(QString &id, int &addQuantity)
{
    // 判断库存中是否有该商品，若没有则输出提示框
    bool found = false;
    for(int i=0; i<m_InfoTable.GetProductsNum(); ++i)
    {
        if(id == m_InfoTable.GetProduct(i).getId())
        {
            found = true;
            break;
        }
    }
    if(!found)
    {
        QMessageBox::information(this,"提示","库存中无该商品！");
        return false;
    }

    int t = m_InfoTable.GetProduct(id).getTotalQuantity();
    t += addQuantity;
    m_InfoTable.GetProduct(id).setTotalQuantity(t);
    // 每次补货后需要点击保存才能保存修改的商品信息。

    QMessageBox::information(this,"提示","补货成功，请及时保存修改信息！");

    return true;
}

void MainWindow::on_actionAdd_triggered()
{
    // 给出路径打开文件并读取文件内容
    QString filePath = "C:/Qt/My_Projects/Commodity_inventory_Manager/Commodity_Infomation.txt";
    QFileInfo fileInfo(filePath);
    if (!fileInfo.isFile()) // 检查文件是否存在
    {
        qDebug() << "The path is not a file or does not exist:" << filePath;
        return;
    }
    m_InfoTable.ReadProductFromFile(filePath);

    // 运行增加销售信息对话框
    m_addSaleRecordDialog->show();
}

void MainWindow::on_actionDelete_triggered()
{
    // 运行删除销售信息对话框
    m_deleteSaleRecordDialog->show();
}

void MainWindow::on_actionSave_triggered()
{
    // 给出路径打开文件并保存内容
    // QString filePath = "C:/Qt/My_Projects/Commodity_inventory_Manager/Commodity_Infomation.txt";
    // QFileInfo fileInfo(filePath);
    // if (!fileInfo.isFile()) // 检查文件路径是否存在
    // {
    //     qDebug() << "The path is not a file or does not exist:" << filePath;
    //     return;
    // }

    // 将以上绝对路径改为文件框选择
    QString curPath = QDir::currentPath();
    QString dlgTitle = "选择一个文件";
    QString filter = "文本文件(*.txt);;所有文件(*.*)";
    QString aFileName = QFileDialog::getOpenFileName(this, dlgTitle, curPath, filter);

    if(aFileName.isEmpty())
        return;

    m_InfoTable.SaveProductToFile(aFileName);

    QMessageBox::information(this,"提示","修改已成功保存！"); // 弹出成功保存提示框
}

void MainWindow::on_actionSupply_triggered()
{
    // 给出路径打开文件并读取文件内容
    QString filePath = "C:/Qt/My_Projects/Commodity_inventory_Manager/Commodity_Infomation.txt";
    QFileInfo fileInfo(filePath);
    if (!fileInfo.isFile()) // 检查文件是否存在
    {
        qDebug() << "The path is not a file or does not exist:" << filePath;
        return;
    }
    m_InfoTable.ReadProductFromFile(filePath);

    // 运行商品补货对话框
    m_inventorySupplyDialog->show();
}


void MainWindow::on_btnShowProductInfo_clicked()
{
    // 显示最新的商品信息
    ui->tb_ShowInfo->setModel(productInfoModel);
    ShowProductsTable();

    // 判断那些商品需要补货，并依次输出提示框
    for(int i=0; i<m_InfoTable.GetProductsNum(); ++i)
    {
        if(m_InfoTable.GetProduct(i).getLeftQuantity() <= 0)
        {
            QString id = m_InfoTable.GetProduct(i).getId();
            QString tip = "%1需要补货";
            QMessageBox::information(this, "提示", tip.arg(id), QMessageBox::Ok);
        }
    }
}

