#include "CSaleRecord.h"
#include <QTextStream>
#include <QDate>

// 默认构造函数的实现
CSaleRecord::CSaleRecord()
    : orderId_(""), quantity_(0), discountRate_(0.0), orderDate_(QDate()), contactPhone_("") {}

// 构造函数的实现
CSaleRecord::CSaleRecord(const QString& orderId, int quantity, double discountRate, const QDate& orderDate, const QString& contactPhone)
    : orderId_(orderId), quantity_(quantity), discountRate_(discountRate), orderDate_(orderDate), contactPhone_(contactPhone) {}

// 拷贝构造函数
CSaleRecord::CSaleRecord(const CSaleRecord &other)
    : orderId_(other.orderId_), quantity_(other.quantity_), discountRate_(other.discountRate_), orderDate_(other.orderDate_), contactPhone_(other.contactPhone_)
{}

// 重载=
CSaleRecord &CSaleRecord::operator=(const CSaleRecord &saleRecord)
{
    orderId_=saleRecord.orderId_;
    quantity_=saleRecord.quantity_;
    discountRate_=saleRecord.discountRate_;
    orderDate_=saleRecord.orderDate_;
    contactPhone_=saleRecord.contactPhone_;
    return *this;
}

// 不同属性的Getter和Setter方法的实现
void CSaleRecord::setOrderId(const QString& orderId)
{
    orderId_ = orderId;
}
QString CSaleRecord::getOrderId() const
{
    return orderId_;
}

void CSaleRecord::setQuantity(int quantity)
{
    quantity_ = quantity;
}
int CSaleRecord::getQuantity() const
{
    return quantity_;
}

void CSaleRecord::setDiscountRate(double discountRate)
{
    discountRate_ = discountRate;
}
double CSaleRecord::getDiscountRate() const
{
    return discountRate_;
}

void CSaleRecord::setOrderDate(const QDate& orderDate)
{
    orderDate_ = orderDate;
}
QDate CSaleRecord::getOrderDate() const
{
    return orderDate_;
}

void CSaleRecord::setContactPhone(const QString& contactPhone)
{
    contactPhone_ = contactPhone;
}
QString CSaleRecord::getContactPhone() const
{
    return contactPhone_;
}

void CSaleRecord::SaveSaleRecord(QTextStream &aStream) const
{
    aStream << orderId_ << '\t' << quantity_ << '\t' << discountRate_ << '\t' << orderDate_.year() << '\t' << orderDate_.month() << '\t' << orderDate_.day() << '\t' << contactPhone_ << '\n';
}

void CSaleRecord::ReadSaleRecord(QTextStream &aStream)
{
    aStream >> orderId_;
    aStream >> quantity_;
    aStream >> discountRate_;
    int year, month, day;
    aStream >> year >> month >> day;
    orderDate_.setDate(year, month, day);
    aStream >> contactPhone_;
}
