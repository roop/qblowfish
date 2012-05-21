TARGET = qblowfishtest
TEMPLATE = app

QT       += core
QT       -= gui

CONFIG   += qtestlib

SOURCES += ../src/qblowfish.cpp \
           qblowfishtest.cpp

HEADERS += ../src/qblowfish.h \
           ../src/qblowfish_p.h \
           qblowfishtest.h

INCLUDEPATH += ../src
