#include "SupplyDialog.h"
#include "ui_SupplyDialog.h"

SupplyDialog::SupplyDialog(QWidget *parent)
    : QDialog(parent)
    , ui(new Ui::SupplyDialog)
{
    ui->setupUi(this);
    setWindowTitle("商品补货");
}

SupplyDialog::~SupplyDialog()
{
    delete ui;
}

void SupplyDialog::clearData()
{
    ui->spbSupplyQuantity->setValue(0);
}

void SupplyDialog::on_btnCancel_clicked()
{
    this->close();
}


void SupplyDialog::on_btnConfirm_clicked()
{
    int supplyQuantity = ui->spbSupplyQuantity->value();
    emit sig_updateProduct(supplyQuantity);

    clearData();
}

