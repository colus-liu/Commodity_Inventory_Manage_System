#ifndef CDATASOURCESQLITE_H
#define CDATASOURCESQLITE_H

#include "IDataSource.h"
#include <QSqlDatabase>
#include "CSaleRecord.h"
#include "CProduct.h"

class CDataSourceSQLite : public IDataSource
{
public:
    CDataSourceSQLite();
    ~CDataSourceSQLite();

    // 在CDataSourceSQLite类中重写基类IDataSource中的虚函数
    virtual bool selectProducts(QList<CProduct> &productList);
    virtual bool selectSaleRecords(QList<CSaleRecord> &saleRecordList);
    virtual bool addSaleRecord(CSaleRecord &saleRecord);
    virtual bool updateProduct(const QString &id, int &supplyQuantity);
    virtual bool deleteSaleRecord(const QString &orderId);

private:
    QSqlDatabase m_db;

};

#endif // CDATASOURCESQLITE_H
