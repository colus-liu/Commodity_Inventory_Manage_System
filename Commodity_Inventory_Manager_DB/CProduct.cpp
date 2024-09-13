#include "CProduct.h"
#include "CSaleRecord.h"
#include <QString>

// 构造函数的实现
CProduct::CProduct(){}

bool CProduct::setProduct(QString id, QString name, int totalQuantity, double purchasePrice, double salePrice,
                          QString manufacturer, QDate productionDate, QDate expirationDate)
{
    id_ = id;
    name_ = name;
    totalQuantity_ = totalQuantity;
    purchasePrice_ = purchasePrice;
    salePrice_ = salePrice;
    manufacturer_ = manufacturer;
    productionDate_ = productionDate;
    expirationDate_ = expirationDate;

    return true;
}

// 不同属性的Getter和Setter方法的实现
QString CProduct::getId() const
{
    return id_;
}
void CProduct::setId(const QString& id)
{
    id_ = id;
}

QString CProduct::getName() const
{
    return name_;
}
void CProduct::setName(const QString& name)
{
    name_ = name;
}

int CProduct::getTotalQuantity() const
{
    return totalQuantity_;
}
void CProduct::setTotalQuantity(const int& totalQuantity)
{
    totalQuantity_ = totalQuantity;
}

double CProduct::getPurchasePrice() const
{
    return purchasePrice_;
}
void CProduct::setPurchasePrice(const double& purchasePrice)
{
    purchasePrice_ = purchasePrice;
}

double CProduct::getSalePrice() const
{
    return salePrice_;
}
void CProduct::setSalePrice(const double& salePrice)
{
    salePrice_ = salePrice;
}

QString CProduct::getManufacturer() const
{
    return manufacturer_;
}
void CProduct::setManufacturer(const QString& manufacturer)
{
    manufacturer_ = manufacturer;
}

QDate CProduct::getProductionDate() const
{
    return productionDate_;
}
void CProduct::setProductionDate(const QDate& productionDate)
{
    productionDate_ = productionDate;
}

QDate CProduct::getExpirationDate() const
{
    return expirationDate_;
}
void CProduct::setExpirationDate(const QDate& expirationDate)
{
    expirationDate_ = expirationDate;
}

int CProduct::getSaleRecordsNum()
{
    saleRecordsNum_ = saleRecords_.size();
    return saleRecordsNum_;
}
void CProduct::setSaleRecordsNum()
{
    saleRecordsNum_ = saleRecords_.size();
}

// 计算并设置利润
void CProduct::setProfit()
{
    double saled = 0;
    for(int i=0; i<saleRecordsNum_; ++i)
    {
        saled += saleRecords_[i].getQuantity() * salePrice_ * saleRecords_[i].getDiscountRate();
    }
    double profit = saled  - totalQuantity_ * purchasePrice_;

    profit_ = profit;
}

double CProduct::getProfit()
{
    return profit_;
}

// 计算剩余库存
void CProduct::setLeftQuantity()
{
    int saledQuantity = 0;
    for(int i=0; i<saleRecordsNum_; ++i)
    {
        saledQuantity += saleRecords_[i].getQuantity();
    }
    int leftQuantity = totalQuantity_ - saledQuantity;

    leftQuantity_ = leftQuantity;
}

int CProduct::getLeftQuantity()
{
    return leftQuantity_;
}

// 销售信息的添加和删除
void CProduct::addSaleRecord(CSaleRecord &saleRecord)
{
    saleRecords_.append(saleRecord);
}

bool CProduct::removeSaleRecord(QString &orderId)
{
    for (int i = 0; i < saleRecords_.size(); ++i)
    {
        if (saleRecords_[i].getOrderId() == orderId)
        {
            saleRecords_.removeAt(i);
            return true;
        }
    }
    return false;
}


// 获取销售信息
CSaleRecord &CProduct::GetSaleRecord(int index)
{
    return saleRecords_[index];
}
