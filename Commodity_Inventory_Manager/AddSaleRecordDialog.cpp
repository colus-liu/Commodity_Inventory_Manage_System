#include "AddSaleRecordDialog.h"
#include "ui_AddSaleRecordDialog.h"
#include <QDate>
#include <QRegularExpression>
#include <QRegularExpressionValidator>
#include <QMessageBox>
#include "CSaleRecord.h"

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

void AddSaleRecordDialog::initUI()
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

    // 总数量的判断相对困难，需要考虑库存量，放到后面实现

    // 折扣率
    ui->spbDiscountRate->setRange(0.0,1.0); // 强制设置DiscountRate的输入范围，超出范围无法输入

    // 联系电话
    ui->edtContactPhone->setPlaceholderText("请输入11位数字"); // 手机号输入提示
    QRegularExpression regPhone("^[1-9][0-9]{10}$"); // 一位1到9的数字和10位0到9的数字
    ui->edtContactPhone->setValidator(new QRegularExpressionValidator(regPhone,this)); // 利用正则表达式判断手机号的合法性
}

bool AddSaleRecordDialog::clearData()
{
    ui->edtId->clear();
    ui->edtOrderId->clear();
    ui->spbQuantity->setValue(0);
    ui->spbDiscountRate->setValue(1.0);
    QDate defaultDate(2024, 1, 1); // 设置默认日期为2024年1月1日
    ui->edtOrderDate->setDate(defaultDate);
    ui->edtContactPhone->clear();
    return true;
}

void AddSaleRecordDialog::on_btnConfirm_clicked()
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

    int phoneLength = ui->edtContactPhone->text().length();
    if(phoneLength != 11)
    {
        QMessageBox::information(this,"提示","手机号输入不合规！！");
        return;
    }

    QString id = ui->edtId->text();
    QString orderId = ui->edtOrderId->text();
    int quantity = ui->spbQuantity->value();
    double discountRate = ui->spbDiscountRate->value();
    QDate orderDate = ui->edtOrderDate->date();
    QString contactPhone = ui->edtContactPhone->text();
    CSaleRecord saleRecord(orderId,quantity,discountRate,orderDate,contactPhone);

    // 发送信号
    emit sig_addSaleRecord(saleRecord, id);

    // 清空数据
    clearData();
}

void AddSaleRecordDialog::on_btnCancel_clicked()
{
    clearData();
    this->close();
}

