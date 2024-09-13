#include "InventorySupplyDialog.h"
#include "ui_InventorySupplyDialog.h"
#include <QMessageBox>

InventorySupplyDialog::InventorySupplyDialog(QWidget *parent)
    : QDialog(parent)
    , ui(new Ui::InventorySupplyDialog)
{
    ui->setupUi(this);
    setWindowTitle("库存补货");
    initUI();
}

InventorySupplyDialog::~InventorySupplyDialog()
{
    delete ui;
}

void InventorySupplyDialog::initUI()
{
    // 设置提示词以及合法数据的范围
    // 商品编号
    ui->edtId->setPlaceholderText("输入四位编号"); // 商品编号输入提示
    QRegularExpression regId("^[0-9]{4}$"); // 四位数字
    ui->edtId->setValidator(new QRegularExpressionValidator(regId,this)); // 利用正则表达式判断商品编号的合法性

}

bool InventorySupplyDialog::clearData()
{
    ui->edtId->clear();
    ui->spbSupplyNum->setValue(0);
    return true;
}

void InventorySupplyDialog::on_btnConfirm_clicked()
{
    // 通过长度判断输入的商品编号是否合法，对于不合法的输入弹出消息框提示
    int idLength = ui->edtId->text().length();
    if(idLength != 4)
    {
        QMessageBox::information(this,"提示","商品编号输入不合规！！");
        return;
    }

    QString id = ui->edtId->text();
    int addQuantity = ui->spbSupplyNum->value();

    // 发送信号
    emit sig_inventorySupply(id, addQuantity);

    // 清空数据
    clearData();
}


void InventorySupplyDialog::on_btnCancel_clicked()
{
    clearData();
    this->close();
}

