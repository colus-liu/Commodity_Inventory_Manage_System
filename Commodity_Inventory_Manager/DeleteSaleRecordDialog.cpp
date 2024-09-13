#include "DeleteSaleRecordDialog.h"
#include "ui_DeleteSaleRecordDialog.h"
#include <QRegularExpression>
#include <QRegularExpressionValidator>
#include <QMessageBox>

DeleteSaleRecordDialog::DeleteSaleRecordDialog(QWidget *parent)
    : QDialog(parent)
    , ui(new Ui::DeleteSaleRecordDialog)
{
    ui->setupUi(this);
    setWindowTitle("删除销售信息（退货）");
    initUI();
}

DeleteSaleRecordDialog::~DeleteSaleRecordDialog()
{
    delete ui;
}

void DeleteSaleRecordDialog::initUI()
{
    clearData();
    // 设置提示词以及合法数据的范围
    // 商品编号
    ui->edtId->setPlaceholderText("输入四位编号"); // 商品编号输入提示
    QRegularExpression regId1("^[0-9]{4}$"); // 四位数字
    ui->edtId->setValidator(new QRegularExpressionValidator(regId1,this)); // 利用正则表达式判断商品编号的合法性

    // 订单号
    ui->edtOrderId->setPlaceholderText("输入八位编号"); // 订单号输入提示
    QRegularExpression regId2("^[0-9]{8}$"); // 八位数字
    ui->edtOrderId->setValidator(new QRegularExpressionValidator(regId2,this)); // 利用正则表达式判断订单号的合法性
}

bool DeleteSaleRecordDialog::clearData()
{
    ui->edtId->clear();
    ui->edtOrderId->clear();
    return true;
}

void DeleteSaleRecordDialog::on_btnConfirm_clicked()
{
    // 先通过长度判断一些输入是否合法，对于不合法的输入弹出消息框提示
    int idLength = ui->edtId->text().length();
    if(idLength != 4)
    {
        QMessageBox::information(this,"提示","商品编号输入不合规！！");
        return;
    }

    int OrderIdLength = ui->edtOrderId->text().length();
    if(OrderIdLength != 8)
    {
        QMessageBox::information(this,"提示","订单号输入不合规！！");
        return;
    }


    QString id = ui->edtId->text();
    QString orderId = ui->edtOrderId->text();

    // 发送信号
    emit sig_deleteSaleRecord(id,orderId);

    // 清空数据
    clearData();
}


void DeleteSaleRecordDialog::on_btnCancel_clicked()
{
    clearData();
    this->close();
}

