#-------------------------------------------------
#
# Project created by QtCreator 2010-10-26T13:40:37
#
#-------------------------------------------------

QT       += core gui sql

TARGET = Qfacture
TEMPLATE = app


SOURCES += main.cpp\
    models/person.cpp \
    models/customer.cpp \
    models/profile.cpp \
    models/template.cpp \
    models/product.cpp \
    qfacturecore.cpp \
    managers/profilemanager.cpp \
    managers/basemanager.cpp \
    gui/mainwindow.cpp \
    gui/widgets/profilewidget.cpp \
    gui/tabs/paramstab.cpp \
    gui/widgets/dbwidget.cpp \
    controllers/dbcontroller.cpp \
    controllers/controller.cpp \
    controllers/profilecontroller.cpp \
    managers/settingsmanager.cpp \
    gui/tabs/customerstab.cpp \
    gui/widgets/sqltable.cpp \
    gui/widgets/customerwidget.cpp \
    controllers/customercontroller.cpp \
    managers/customermanager.cpp

HEADERS  += models/person.h \
    models/customer.h \
    models/profile.h \
    models/template.h \
    models/product.h \
    qfacturecore.h \
    managers/profilemanager.h \
    managers/dbmanager.h \
    managers/basemanager.h \
    gui/mainwindow.h \
    gui/widgets/profilewidget.h \
    gui/tabs/paramstab.h \
    gui/widgets/dbwidget.h \
    controllers/dbcontroller.h \
    controllers/controller.h \
    controllers/profilecontroller.h \
    managers/settingsmanager.h \
    gui/tabs/customerstab.h \
    gui/widgets/sqltable.h \
    gui/widgets/customerwidget.h \
    controllers/customercontroller.h \
    managers/customermanager.h

FORMS    += gui/mainwindow.ui \
