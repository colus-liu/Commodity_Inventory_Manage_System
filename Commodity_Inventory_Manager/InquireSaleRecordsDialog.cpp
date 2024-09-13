#include "InquireSaleRecordsDialog.h"
#include "ui_InquireSaleRecordsDialog.h"
#include <QRegularExpression>
#include <QRegularExpressionValidator>
#include <QMessageBox>
#include <QDebug>

InquireSaleRecordsDialog::InquireSaleRecordsDialog(QWidget *parent)
    : QDialog(parent)
    , ui(new Ui::InquireSaleRecordsDialog)
{
    ui->setupUi(this);
    setWindowTitle("查询商品销售信息");
    initUI();
}

InquireSaleRecordsDialog::~InquireSaleRecordsDialog()
{
    delete ui;
}

QString InquireSaleRecordsDialog::Id()
{
    return ui->edtId->text();
}

bool InquireSaleRecordsDialog::clearData()
{
    ui->edtId->clear();
    return true;
}

void InquireSaleRecordsDialog::on_btnConfirm_clicked()
{
    // 通过长度判断输入的商品编号是否合法，对于不合法的输入弹出消息框提示
    int idLength = ui->edtId->text().length();
    if(idLength != 4)
    {
        QMessageBox::information(this,"提示","商品编号输入不合规！！");
        return;
    }

    QString id = ui->edtId->text();

    // 发送信号
    emit sig_inquireSaleRecords(id);

    // 清空数据
    clearData();
}

void InquireSaleRecordsDialog::on_btnCancel_clicked()
{
    clearData();
    this->close();
}

void InquireSaleRecordsDialog::initUI()
{
    // 设置提示词以及合法数据的范围
    ui->edtId->setPlaceholderText("输入四位编号"); // 商品编号输入提示
    QRegularExpression regId("^[0-9]{4}$"); // 四位数字
    ui->edtId->setValidator(new QRegularExpressionValidator(regId,this)); // 利用正则表达式判断商品编号的合法性
}

