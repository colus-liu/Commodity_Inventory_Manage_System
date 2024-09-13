#include "CDataSourceSQLite.h"
#include "CProduct.h"
#include "CSaleRecord.h"
#include <QDebug>
#include <QSqlQuery> // 用于创建QSqlQuery来执行SQL语句
#include <QSqlError>


CDataSourceSQLite::CDataSourceSQLite()
{
    // 创建并打开数据库
    m_db = QSqlDatabase::addDatabase("QSQLITE"); // 注册一个新数据库连接，使用 SQLite 作为数据库驱动
    m_db.setDatabaseName("./inventoryInfoDB.db"); // 设置数据库名称，即数据库文件的路径
    if(!m_db.open())
    {
        qDebug() << "Failed to open database";
        return; // 结束构造函数
    }


    // 使用SQL语句为数据库创建商品信息图表,数据库中的表不包括利润和剩余库存
    QSqlQuery query1; // 创建一个 QSqlQuery 对象，用于执行 SQL 语句
    QString sql1 = QString("create table if not exists tb_productInfo ("
                          "id VARCHAR(4),"
                          "name VARCHAR(50),"
                          "totalQuantity INT,"
                          "purchasePrice DOUBLE,"
                          "salePrice DOUBLE,"
                          "manufacturer VARCHAR(255)," // 假设生产厂家名称长度不超过255
                          "productionDate DATE,"
                          "expirationDate DATE,"
                          "PRIMARY KEY (id)" // 将id设为主键
                          ");"); // 定义一个 SQL 语句，用于创建一个名为 tb_productInfo 的新表
    if(!query1.exec(sql1)) // 执行上述创建表的 SQL 语句。如果执行失败，输出错误信息和失败的 SQL 语句。
    {
        qDebug() << "Failed to create tb_productInfo";
        qDebug() << query1.lastQuery();
        m_db.close();
        return;
    }

    // 使用SQL语句为数据库创建销售信息图表

    QSqlQuery query2; // 创建一个 QSqlQuery 对象，用于执行 SQL 语句
    QString sql2 = QString("create table if not exists tb_saleRecordInfo ("
                          "orderId VARCHAR(8),"
                          "quantity INT,"
                          "discountRate DOUBLE CHECK (discountRate >= 0.0 AND discountRate <= 1.0),"
                          "orderDate DATE,"
                          "contactPhone VARCHAR(11),"
                          "productId VARCHAR(4),"
                          "PRIMARY KEY (orderId)" // 将orderId设为主键
                          ");");// 定义一个 SQL 语句，用于创建一个名为 tb_saleRecordInfo 的新表
    if(!query2.exec(sql2))
    {
        qDebug() << "Failed to create tb_productInfo";
        qDebug() << query2.lastQuery();
        m_db.close();
        return;
    }


    // 关闭数据库
    m_db.close();
}


CDataSourceSQLite::~CDataSourceSQLite()
{

}


// 商品信息显示（将数据库中的表格tb_productInfo中的信息放入该函数传入的参数productList中）
// 数据库中不存商品利润和剩余库存，在tableView上显示表格时实时计算并将利润和剩余库存显示出来
bool CDataSourceSQLite::selectProducts(QList<CProduct> &productList)
{
    if(!m_db.open())
    {
        qDebug() << "Failed to open DataBase for selecting products";
        return false;
    }

    QSqlQuery query;
    QString sql = "select * from tb_productInfo;"; // 该SQL查询语句用于从名为tb_productInfo的表中选择所有列
    if(!query.exec(sql))
    {
        qDebug() << "Failed to select tb_productInfo;";
        qDebug() << query.lastQuery();
        m_db.close();
        return false;
    }

    while(query.next())
    {
        CProduct product;
        QString id = query.value("id").toString();
        QString name= query.value("name").toString();
        int totalquantity = query.value("totalquantity").toInt();
        double purchasePrice = query.value("purchasePrice").toDouble();
        double salePrice = query.value("salePrice").toDouble();
        QString manufacturer = query.value("manufacturer").toString();
        QDate productionDate = QDate::fromString(query.value("productionDate").toString(), "yyyy-MM-dd");
        QDate expirationDate = QDate::fromString(query.value("expirationDate").toString(), "yyyy-MM-dd");

        product.setProduct(id,name,totalquantity,purchasePrice,salePrice,manufacturer,productionDate,expirationDate);
        productList.append(product);
// insert into tb_productInfo(id,name,totalquantity,purchasePrice,salePrice,manufacturer,productionDate,expirationDate)
//        values(‘0001’,‘商品一’,100,10.2,12.2,‘产商一’,2024-02-02,2025-02-02)
    }
    m_db.close();
    return true;
}


// 应该根据商品编号从数据库表格中获取并显示特定的销售信息
// 销售信息显示（将数据库中的表格tb_saleRecordInfo中的信息放入该函数传入的参数saleReclrdList中）
bool CDataSourceSQLite::selectSaleRecords(QList<CSaleRecord> &saleReclrdList)
{
    if(!m_db.open())
    {
        qDebug() << "Failed to open DataBase for selecting saleRecords";
        return false;
    }

    QSqlQuery query;
    QString sql = "select * from tb_saleRecordInfo;"; // 该SQL查询语句用于从名为tb_productInfo的表中选择所有列
    if(!query.exec(sql))
    {
        qDebug() << "Failed to select tb_saleRecordInfo;";
        qDebug() << query.lastQuery();
        m_db.close();
        return false;
    }

    while(query.next())
    {

        QString orderId = query.value("orderId").toString();
        int quantity = query.value("quantity").toInt();
        double discountRate = query.value("discountRate").toDouble();
        QDate orderDate = QDate::fromString(query.value("orderDate").toString(), "yyyy-MM-dd");
        QString contactPhone = query.value("contactPhone").toString();
        QString productId = query.value("productId").toString();

        CSaleRecord saleRecord(orderId,quantity,discountRate,orderDate,contactPhone,productId);
        saleReclrdList.append(saleRecord);

    }
    m_db.close();
    return true;
}


// 添加（向数据库中添加一条销售信息）
bool CDataSourceSQLite::addSaleRecord(CSaleRecord &saleRecord)
{
    if(!m_db.open())
    {
        qDebug() << "Failed to open DataBase for adding saleRecord";
        return false;
    }

    QSqlQuery query;
    query.prepare("insert into tb_saleRecordInfo (orderId,quantity,discountRate,orderDate,contactPhone,productId)"
                  "values(:orderId,:quantity,:discountRate,:orderDate,:contactPhone,:productId)");
    // 使用bindValue方法将saleRecord中的相应字段值绑定到SQL语句的参数上
    query.bindValue(":orderId",saleRecord.getOrderId());
    query.bindValue(":quantity",saleRecord.getQuantity());
    query.bindValue(":discountRate",saleRecord.getDiscountRate());
    query.bindValue(":orderDate",saleRecord.getOrderDate());
    query.bindValue(":contactPhone",saleRecord.getContactPhone());
    query.bindValue(":productId",saleRecord.getProductId());

    if(!query.exec())
    {
        qDebug() << "Failed to add saleReord to tb_saleRecordInfo!";
        qDebug() << query.lastQuery();
        m_db.close();
        return false;
    }
    m_db.close();
    return true;
}

// 删除（根据orderId从数据库中删除一条销售信息）
bool CDataSourceSQLite::deleteSaleRecord(const QString &orderId)
{
    if (!m_db.open())
    {
        qDebug() << "Failed to open DataBase for deleting SaleRecord";
        return false;
    }

    QString sql = "delete from tb_saleRecordInfo where orderId = :orderId";
    QSqlQuery query;
    if (!query.prepare(sql))
    {
        qDebug() << "Failed to prepare statement";
        qDebug() << query.lastError();
        m_db.close();
        return false;
    }

    query.bindValue(":orderId", orderId); // 使用参数化查询绑定orderId

    if (!query.exec())
    {
        qDebug() << "Failed to execute delete operation";
        qDebug() << query.lastError();
        m_db.close();
        return false;
    }

    m_db.close();
    return true;
}


// 修改（在数据库中根据商品编号和补货量修改该商品的总数量）
bool CDataSourceSQLite::updateProduct(const QString &id, int &supplyQuantity)
{
    if(!m_db.open())
    {
        qDebug() << "Failed to Open Database for updating productInfo";
        return false;
    }

    // 查询当前商品的总数量
    QSqlQuery querySelect;
    querySelect.prepare("select totalQuantity from tb_productInfo where id = :id");
    querySelect.bindValue(":id", id);
    if(!querySelect.exec())
    {
        qDebug() << "Error selecting product info:" << querySelect.lastError();
        m_db.close();
        return false;
    }

    if(querySelect.next()) // 如果找到商品记录
    {
        int currentTotalQuantity = querySelect.value(0).toInt();
        int newTotalQuantity = currentTotalQuantity + supplyQuantity; // 计算新的总数量

        // 准备SQL更新语句
        QSqlQuery queryUpdate;
        queryUpdate.prepare("update tb_productInfo set totalQuantity = :newTotalQuantity where id = :id");

        // 绑定新总数量和商品编号
        queryUpdate.bindValue(":newTotalQuantity", newTotalQuantity);
        queryUpdate.bindValue(":id", id);

        if(!queryUpdate.exec())
        {
            qDebug() << "Error updating product info:" << queryUpdate.lastError();
            m_db.close();
            return false;
        }
    }
    else
    {
        qDebug() << "No product found with the given ID.";
        m_db.close();
        return false;
    }

    m_db.close();
    return true;
}

