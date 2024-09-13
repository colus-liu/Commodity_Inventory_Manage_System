#ifndef CINVENTORYSYSTEM_H
#define CINVENTORYSYSTEM_H

#include <QList>
#include "CProduct.h"
#include <QTextStream>

class CInventorySystem
{
public:
    CInventorySystem();

    // 从文本文件中读取和保存产品信息
    bool ReadProductFromFile(const QString &aReadFileName);
    bool SaveProductToFile(const QString &aSaveFileName);

    int GetProductsNum();
    CProduct & GetProduct(int index);
    CProduct & GetProduct(QString id); // 函数重载

private:
    QList<CProduct> products_;
    int productsNum_;


};

#endif // CINVENTORYSYSTEM_H
