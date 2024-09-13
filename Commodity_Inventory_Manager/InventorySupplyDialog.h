#ifndef INVENTORYSUPPLYDIALOG_H
#define INVENTORYSUPPLYDIALOG_H

#include <QDialog>

namespace Ui {
class InventorySupplyDialog;
}

class InventorySupplyDialog : public QDialog
{
    Q_OBJECT

public:
    explicit InventorySupplyDialog(QWidget *parent = nullptr);
    ~InventorySupplyDialog();

    bool clearData();

signals:
    void sig_inventorySupply(QString &id, int &addQuantity);


private slots:
    void on_btnConfirm_clicked();

    void on_btnCancel_clicked();

private:
    Ui::InventorySupplyDialog *ui;
    void initUI();
};

#endif // INVENTORYSUPPLYDIALOG_H
