#include "Widget.h"

#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    Widget w;
    w.setWindowTitle("商品库存管理系统");
    w.show();
    return a.exec();
}
