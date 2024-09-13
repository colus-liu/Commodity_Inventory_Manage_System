#ifndef CINVENTORYSYSTEM_H
#define CINVENTORYSYSTEM_H

#include <QList>
#include "CProduct.h"

class CInventorySystem
{
public:
    CInventorySystem();

    int GetProductsNum();
    CProduct & GetProduct(int index);
    CProduct & GetProduct(QString id); // 函数重载

private:
    QList<CProduct> products_;
    int productsNum_;

};

#endif // CINVENTORYSYSTEM_H
