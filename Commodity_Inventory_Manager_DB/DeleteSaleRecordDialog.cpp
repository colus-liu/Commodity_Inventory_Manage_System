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

void DeleteSaleRecordDialog::clearData()
{
    ui->edtOrderId->clear();
}

void DeleteSaleRecordDialog::on_btnConfirm_clicked()
{
    // 先通过长度判断输入是否合法，对于不合法的输入弹出消息框提示
    int OrderIdLength = ui->edtOrderId->text().length();
    if(OrderIdLength != 8)
    {
        QMessageBox::information(this,"提示","订单号输入不合规！！");
        return;
    }

    QString orderId = ui->edtOrderId->text();
    emit sig_deleteSaleRecord(orderId);

    clearData();
}


void DeleteSaleRecordDialog::on_btnCancel_clicked()
{
    this->close();
}

void DeleteSaleRecordDialog::initUI()
{
    clearData();
    // 设置提示词以及合法数据的范围
    // 订单号
    ui->edtOrderId->setPlaceholderText("输入八位编号"); // 订单号输入提示
    QRegularExpression regId("^[0-9]{8}$"); // 八位数字
    ui->edtOrderId->setValidator(new QRegularExpressionValidator(regId,this)); // 利用正则表达式判断订单号的合法性
}

