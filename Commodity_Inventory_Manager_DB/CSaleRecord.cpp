#include "CSaleRecord.h"
#include <QDate>

// 默认构造函数的实现
CSaleRecord::CSaleRecord()
    : orderId_(""), quantity_(0), discountRate_(0.0), orderDate_(QDate()), contactPhone_("") {}

// 构造函数的实现
CSaleRecord::CSaleRecord(const QString& orderId, int quantity, double discountRate, const QDate& orderDate, const QString& contactPhone, const QString& productId)
    : orderId_(orderId), quantity_(quantity), discountRate_(discountRate), orderDate_(orderDate), contactPhone_(contactPhone), productId_(productId) {}

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

void CSaleRecord::setProductId(const QString &productId)
{
    productId_ = productId;
}
QString CSaleRecord::getProductId() const
{
    return productId_;
}
