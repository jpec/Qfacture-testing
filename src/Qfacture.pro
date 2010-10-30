#-------------------------------------------------
#
# Project created by QtCreator 2010-10-26T13:40:37
#
#-------------------------------------------------

QT       += core gui sql

TARGET = Qfacture
TEMPLATE = app


SOURCES += main.cpp\
    gui/qfacturegui.cpp \
    models/person.cpp \
    models/customer.cpp \
    models/profile.cpp \
    models/template.cpp \
    models/product.cpp \
    qfacturecore.cpp

HEADERS  += gui/qfacturegui.h \
    models/person.h \
    models/customer.h \
    models/profile.h \
    models/template.h \
    models/product.h \
    qfacturecore.h

FORMS    += gui/qfacturegui.ui