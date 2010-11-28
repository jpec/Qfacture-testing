# -------------------------------------------------
# Project created by QtCreator 2010-10-26T13:40:37
# -------------------------------------------------
QT += core \
    gui \
    sql
TARGET = Qfacture
TEMPLATE = app
SOURCES += main.cpp \
    models/person.cpp \
    models/customer.cpp \
    models/profile.cpp \
    models/template.cpp \
    models/product.cpp \
    qfacturecore.cpp \
    managers/profilemanager.cpp \
    gui/mainwindow.cpp \
    gui/widgets/profilewidget.cpp \
    gui/tabs/paramstab.cpp \
    gui/widgets/dbwidget.cpp \
    controllers/dbcontroller.cpp \
    controllers/profilecontroller.cpp \
    managers/settingsmanager.cpp \
    gui/tabs/customerstab.cpp \
    gui/widgets/sqltable.cpp \
    gui/widgets/customerwidget.cpp \
    controllers/customercontroller.cpp \
    managers/customermanager.cpp \
    managers/productmanager.cpp \
    controllers/productcontroller.cpp \
    gui/tabs/productstab.cpp \
    gui/widgets/productwidget.cpp \
    gui/tabs/invoicestab.cpp \
    gui/tabs/invoicetab.cpp
HEADERS += models/person.h \
    models/customer.h \
    models/profile.h \
    models/template.h \
    models/product.h \
    qfacturecore.h \
    managers/profilemanager.h \
    gui/mainwindow.h \
    gui/widgets/profilewidget.h \
    gui/tabs/paramstab.h \
    gui/widgets/dbwidget.h \
    controllers/dbcontroller.h \
    controllers/profilecontroller.h \
    managers/settingsmanager.h \
    gui/tabs/customerstab.h \
    gui/widgets/sqltable.h \
    gui/widgets/customerwidget.h \
    controllers/customercontroller.h \
    managers/customermanager.h \
    managers/productmanager.h \
    controllers/productcontroller.h \
    gui/tabs/productstab.h \
    gui/widgets/productwidget.h \
    gui/tabs/invoicestab.h \
    gui/tabs/invoicetab.h
FORMS += gui/mainwindow.ui
