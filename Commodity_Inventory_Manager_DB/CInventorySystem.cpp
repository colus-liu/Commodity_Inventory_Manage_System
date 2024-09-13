#include "CInventorySystem.h"
#include <QFile>
#include <QList>

CInventorySystem::CInventorySystem()
{
    productsNum_ = 5; // 规定库存里有五件商品
}


int CInventorySystem::GetProductsNum()
{
    productsNum_ = products_.size();
    return productsNum_;
}

CProduct &CInventorySystem::GetProduct(int index)
{
    return products_[index];
}

CProduct &CInventorySystem::GetProduct(QString id) // 函数重载
{
    for(int i=0; i<productsNum_; ++i)
    {
        if(id == products_[i].getId())
        {
            return products_[i];
        }
    }
}
