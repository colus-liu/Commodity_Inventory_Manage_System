#include "AddSaleRecordDialog.h"
#include "ui_AddSaleRecordDialog.h"
#include <QMessageBox>
//#include "CSaleRecord.h"


AddSaleRecordDialog::AddSaleRecordDialog(QWidget *parent)
    : QDialog(parent)
    , ui(new Ui::AddSaleRecordDialog)
{
    ui->setupUi(this);
    setWindowTitle("增加销售信息（售货）");
    initUI();
}

AddSaleRecordDialog::~AddSaleRecordDialog()
{
    delete ui;
}

bool AddSaleRecordDialog::clearData()
{
    ui->edtOrderId->clear();
    ui->spbQuantity->setValue(0);
    ui->spbDiscountRate->setValue(1.0);
    QDate defaultDate(2024, 1, 1); // 设置默认日期为2024年1月1日
    ui->edtOrderDate->setDate(defaultDate);
    ui->edtContactPhone->clear();
    return true;
}


void AddSaleRecordDialog::initUI()
{
    clearData();
    // 设置提示词以及合法数据的范围
    // 订单号
    ui->edtOrderId->setPlaceholderText("输入八位编号"); // 订单号输入提示
    QRegularExpression regId2("^[0-9]{8}$"); // 八位数字
    ui->edtOrderId->setValidator(new QRegularExpressionValidator(regId2,this)); // 利用正则表达式判断订单号的合法性

    // 折扣率
    ui->spbDiscountRate->setRange(0.0,1.0); // 强制设置DiscountRate的输入范围，超出范围无法输入

    // 联系电话
    ui->edtContactPhone->setPlaceholderText("请输入11位数字"); // 手机号输入提示
    QRegularExpression regPhone("^[1-9][0-9]{10}$"); // 一位1到9的数字和10位0到9的数字
    ui->edtContactPhone->setValidator(new QRegularExpressionValidator(regPhone,this)); // 利用正则表达式判断手机号的合法性
}

void AddSaleRecordDialog::on_btnCancel_clicked()
{
    this->close();
}


void AddSaleRecordDialog::on_btnConfirm_clicked()
{
    // 先通过长度判断一些输入是否合法，对于不合法的输入弹出消息框提示
    int OrderIdLength = ui->edtOrderId->text().length();
    if(OrderIdLength != 8)
    {
        QMessageBox::information(this,"提示","订单号输入不合规！！");
        return;
    }
    int phoneLength = ui->edtContactPhone->text().length();
    if(phoneLength != 11)
    {
        QMessageBox::information(this,"提示","手机号输入不合规！！");
        return;
    }

    QString orderId = ui->edtOrderId->text();
    int quantity = ui->spbQuantity->value();
    double discountRate = ui->spbDiscountRate->value();
    QDate orderDate = ui->edtOrderDate->date();
    QString contactPhone = ui->edtContactPhone->text();

    // 发送信号
    emit sig_addSaleRecord(orderId,quantity,discountRate,orderDate,contactPhone);

    // 清空数据
    clearData();
}

