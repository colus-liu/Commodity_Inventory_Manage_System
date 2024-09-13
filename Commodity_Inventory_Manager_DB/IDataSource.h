#ifndef IDATASOURCE_H
#define IDATASOURCE_H
#include "CSaleRecord.h"
#include "CProduct.h"

class IDataSource
{
public:
    IDataSource();
    virtual ~IDataSource() = 0; // 纯虚析构函数
    // 纯虚析构函数是一种特殊的虚函数，它没有实现。
    // 声明纯虚析构函数的类是一个抽象类，不能被实例化。
    // 并且要求任何派生类都必须提供自己的析构函数实现，否则派生类也会是抽象类。
    // 这通常用于接口类，即那些不打算被实例化的类。

    // 查询所有商品信息，成功则返回true，否则返回false
    virtual bool selectProducts(QList<CProduct> &productList) = 0;

    // 查询所有销售信息，成功则返回true，否则返回false
    virtual bool selectSaleRecords(QList<CSaleRecord> &saleRecordList) = 0;

    // 添加销售信息，成功则返回true，否则返回false
    virtual bool addSaleRecord(CSaleRecord &saleRecord) = 0;

    // 修改销售信息，成功则返回true，否则返回false
    virtual bool updateProduct(const QString &id, int &supplyQuantity) = 0;

    // 根据订单号来删除销售信息，成功则返回true，否则返回false
    virtual bool deleteSaleRecord(const QString &orderId) = 0;

    // 以上虚函数在子类CDataSourceSQLite中实现

};

#endif // IDATASOURCE_H
