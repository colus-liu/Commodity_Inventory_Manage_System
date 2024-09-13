#ifndef CPRODUCT_H
#define CPRODUCT_H

#include <QDate>
#include <QList>
#include "CSaleRecord.h"
#include <QTextStream>

class CProduct
{
public:
    CProduct(); // 构造函数

    // 不同属性的Getter和Setter方法
    void setName(const QString& name);
    QString getName() const;

    void setId(const QString& id);
    QString getId() const;

    void setTotalQuantity(const int& totalQuantity);
    int getTotalQuantity() const;

    void setPurchasePrice(const double& purchasePrice);
    double getPurchasePrice() const;

    void setSalePrice(const double& salePrice);
    double getSalePrice() const;

    void setManufacturer(const QString& manufacturer);
    QString getManufacturer() const;

    void setProductionDate(const QDate& productoinDate);
    QDate getProductionDate() const;

    void setExpirationDate(const QDate& expirationDate);
    QDate getExpirationDate() const;

    double getProfit(); // 计算利润
    int getLeftQuantity(); // 计算剩余库存数量

    void addSaleRecord(CSaleRecord &saleRecord);
    bool removeSaleRecord(QString &orderId);

    int GetSaleRecordsNum();
    void setSaleRecordsNum();
    CSaleRecord & GetSaleRecord(int index);

    void SaveProduct(QTextStream &aStream);
    void ReadProduct(QTextStream &aStream);

private:
    QString name_;
    QString id_;
    int totalQuantity_;
    double purchasePrice_;
    double salePrice_;
    QString manufacturer_;
    QDate productionDate_;
    QDate expirationDate_;
    double profit_; // 商品利润
    int leftQuantity_; // 剩余库存数量

    QList<CSaleRecord> saleRecords_; // 该商品的销售数据集
    int saleRecordsNum_;

};

#endif // CPRODUCT_H
