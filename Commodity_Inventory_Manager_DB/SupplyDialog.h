#ifndef SUPPLYDIALOG_H
#define SUPPLYDIALOG_H

#include <QDialog>

namespace Ui {
class SupplyDialog;
}

class SupplyDialog : public QDialog
{
    Q_OBJECT

public:
    explicit SupplyDialog(QWidget *parent = nullptr);
    ~SupplyDialog();

    void clearData();

signals:
    void sig_updateProduct(int &supplyQuantity);

private slots:
    void on_btnCancel_clicked();

    void on_btnConfirm_clicked();

private:
    Ui::SupplyDialog *ui;
};

#endif // SUPPLYDIALOG_H
