#include "CProduct.h"
#include "CSaleRecord.h"
#include <QTextStream>
#include <QString>

// 构造函数的实现
CProduct::CProduct()
{
    saleRecordsNum_ = 0;
}

// 不同属性的Getter和Setter方法的实现
QString CProduct::getName() const
{
    return name_;
}
void CProduct::setName(const QString& name)
{
    name_ = name;
}

QString CProduct::getId() const
{
    return id_;
}
void CProduct::setId(const QString& id)
{
    id_ = id;
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

// 计算利润
double CProduct::getProfit()
{
    for(int i=0; i<saleRecordsNum_; ++i)
    {
        profit_ += saleRecords_[i].getQuantity() * (salePrice_ * saleRecords_[i].getDiscountRate()- purchasePrice_) ;
    }

    return profit_;
}

// 计算剩余库存
int CProduct::getLeftQuantity()
{
    int saledQuantity = 0;
    for(int i=0; i<saleRecordsNum_; ++i)
    {
        saledQuantity += saleRecords_[i].getQuantity();
    }
    leftQuantity_ = totalQuantity_ - saledQuantity;

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

int CProduct::GetSaleRecordsNum()
{
    saleRecordsNum_ = saleRecords_.size();
    return saleRecordsNum_;
}

void CProduct::setSaleRecordsNum()
{
    saleRecordsNum_ = saleRecords_.size();
}

CSaleRecord &CProduct::GetSaleRecord(int index)
{
    return saleRecords_[index];
}

// 商品信息的保存和读取
void CProduct::SaveProduct(QTextStream &aStream)
{
    aStream << name_ << '\n';
    aStream << id_ << '\n';
    aStream << totalQuantity_ << '\n';
    aStream << purchasePrice_ << '\n';
    aStream << salePrice_ << '\n';
    aStream << manufacturer_ << '\n';
    aStream << productionDate_.year() << '\t' << productionDate_.month() << '\t' << productionDate_.day() << '\n';
    aStream << expirationDate_.year() << '\t' << expirationDate_.month() << '\t' << expirationDate_.day() << '\n';
    aStream << saleRecordsNum_ <<'\n';

    for (const CSaleRecord &saleRecord : saleRecords_)
    {
        saleRecord.SaveSaleRecord(aStream);
    }
}

void CProduct::ReadProduct(QTextStream &aStream)
{
    aStream >> name_;
    aStream >> id_;
    aStream >> totalQuantity_;
    aStream >> purchasePrice_;
    aStream >> salePrice_;
    aStream >> manufacturer_;
    int year_p, month_p, day_p;
    aStream >> year_p >> month_p >> day_p;
    productionDate_.setDate(year_p, month_p, day_p);
    int year_e, month_e, day_e;
    aStream >> year_e >> month_e >> day_e;
    expirationDate_.setDate(year_e, month_e, day_e);

    aStream >> saleRecordsNum_;
    saleRecords_.clear();
    for(int i=1; i<=saleRecordsNum_; ++i)
    {
        CSaleRecord saleRecord;
        saleRecord.ReadSaleRecord(aStream);
        saleRecords_.append(saleRecord);
    }
}
