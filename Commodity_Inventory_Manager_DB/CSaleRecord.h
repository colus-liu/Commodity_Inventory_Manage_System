#ifndef CSALERECORD_H
#define CSALERECORD_H

// #include "qlocale.h"
#include <QString>
#include <QDate>
#include <QMetaType> // 用于使用宏Q_DECLARE_METATYPE

class CSaleRecord
{
public:
    // 默认构造函数
    CSaleRecord();

    // 构造函数
    CSaleRecord(const QString& orderId, int quantity, double discountRate, const QDate& orderDate, const QString& contactPhone, const QString& productId);


    // 拷贝构造函数
    //CSaleRecord(const CSaleRecord &other);

    // 重载=
    //CSaleRecord& operator= (const CSaleRecord& saleRecord);

    // 不同属性的Getter和Setter方法
    void setOrderId(const QString& orderId);
    QString getOrderId() const;

    void setQuantity(int quantity);
    int getQuantity() const;

    void setDiscountRate(double discountRate);
    double getDiscountRate() const;

    void setOrderDate(const QDate& orderDate);
    QDate getOrderDate() const;

    void setContactPhone(const QString& contactPhone);
    QString getContactPhone() const;

    void setProductId(const QString& productId);
    QString getProductId() const;


private:
    QString orderId_;
    int quantity_;
    double discountRate_;
    QDate orderDate_;
    QString contactPhone_;

    QString productId_; // 用于标记该销售信息是哪个产品的

};
Q_DECLARE_METATYPE(CSaleRecord)
// Q_DECLARE_METATYPE 是 Qt 框架中使用的一个宏，
// 用于告诉 Qt 的元对象系统（meta-object system）一个新的类型，
// 这样这个类型就可以被用作信号和槽的参数类型。
// 当想要在 Qt 的信号和槽机制中使用 CSaleRecord 类的实例时，需要使用 Q_DECLARE_METATYPE 宏来声明它。

#endif // CSALERECORD_H
