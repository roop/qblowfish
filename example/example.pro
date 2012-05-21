TARGET = qblowfish
TEMPLATE = app

QT       += core
QT       -= gui

CONFIG   += console
CONFIG   -= app_bundle

SOURCES += ../src/qblowfish.cpp \
           main.cpp

HEADERS += ../src/qblowfish.h \
           ../src/qblowfish_p.h

INCLUDEPATH += ../src
