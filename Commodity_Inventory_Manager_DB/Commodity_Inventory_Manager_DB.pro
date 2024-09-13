QT       += core gui sql

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++17

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    AddSaleRecordDialog.cpp \
    CDataSourceSQLite.cpp \
    CInventorySystem.cpp \
    CProduct.cpp \
    CSaleRecord.cpp \
    DeleteSaleRecordDialog.cpp \
    IDataSource.cpp \
    ShowSaleRecordsDialog.cpp \
    SupplyDialog.cpp \
    main.cpp \
    Widget.cpp

HEADERS += \
    AddSaleRecordDialog.h \
    CDataSourceSQLite.h \
    CInventorySystem.h \
    CProduct.h \
    CSaleRecord.h \
    DeleteSaleRecordDialog.h \
    IDataSource.h \
    ShowSaleRecordsDialog.h \
    SupplyDialog.h \
    Widget.h

FORMS += \
    AddSaleRecordDialog.ui \
    DeleteSaleRecordDialog.ui \
    ShowSaleRecordsDialog.ui \
    SupplyDialog.ui \
    Widget.ui

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target
