#include "CInventorySystem.h"
#include <QFile>
#include <QTextStream>
#include <QList>

CInventorySystem::CInventorySystem()
{
    productsNum_ = 5; // 规定库存里有五件商品
}

bool CInventorySystem::ReadProductFromFile(const QString &aReadFileName)
{
    QFile aFile(aReadFileName);
    if(!aFile.exists()) //文件不存在
        return false;
    if(!aFile.open(QIODevice::ReadOnly | QIODevice::Text)) //以文本方式只读打开
        return false;
    QTextStream aStream(&aFile); //用文本流读取文件

    //初始化
    products_.clear();

    //逐个读取产品信息
    CProduct tempProduct;
    for(int i=0; i<productsNum_; i++)
    {
        tempProduct.ReadProduct(aStream);
        products_.append(tempProduct);
    }
    aFile.close();//关闭文件
    return true;
}

bool CInventorySystem::SaveProductToFile(const QString &aSaveFileName)
{
    QFile aFile(aSaveFileName);
    if(!aFile.open(QIODevice::WriteOnly| QIODevice::Text)) //保存为文本
        return false;
    QTextStream aStream(&aFile);//用文本流保存文件

    //逐个写入产品信息
    for(int i=0; i<productsNum_; i++)
    {
        products_[i].SaveProduct(aStream);
    }
    aFile.close(); //关闭文件
    return true;
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
CProduct & CInventorySystem::GetProduct(QString id) // 函数重载
{
    for(int i=0; i<productsNum_; ++i)
    {
        if(id == products_[i].getId())
        {
            return products_[i];
        }
    }
}
