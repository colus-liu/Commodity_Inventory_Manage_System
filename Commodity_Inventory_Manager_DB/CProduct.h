#ifndef CPRODUCT_H
#define CPRODUCT_H
#include <QString>
#include <QDate>
#include "CSaleRecord.h"
#include <QList>

class CProduct
{
public:
    CProduct(); // 构造函数

    bool setProduct(QString id, QString name, int totalQuantity, double purchasePrice, double salePrice,
                    QString manufacturer, QDate productionDate, QDate expirationDate);

    // 不同属性的Getter和Setter方法
    void setId(const QString& id);
    QString getId() const;

    void setName(const QString& name);
    QString getName() const;

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

    int getSaleRecordsNum();
    void setSaleRecordsNum();


    void setProfit(); // 计算并设置利润
    double getProfit();

    void setLeftQuantity(); // 计算并设置剩余库存量
    int getLeftQuantity();

    // 添加和删除销售信息
    void addSaleRecord(CSaleRecord &saleRecord);
    bool removeSaleRecord(QString &orderId);

    // 获取销售信息
    CSaleRecord & GetSaleRecord(int index);

private:
    QString id_;
    QString name_;
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
