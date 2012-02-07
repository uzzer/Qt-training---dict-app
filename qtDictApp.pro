#-------------------------------------------------
#
# Project created by QtCreator 2012-02-07T13:18:29
#
#-------------------------------------------------

QT       += core gui

TARGET = qtDictApp
TEMPLATE = app


SOURCES += main.cpp\
        qtdictapp.cpp

HEADERS  += qtdictapp.h

CONFIG += mobility
MOBILITY = 

symbian {
    TARGET.UID3 = 0xe3dff9ab
    # TARGET.CAPABILITY += 
    TARGET.EPOCSTACKSIZE = 0x14000
    TARGET.EPOCHEAPSIZE = 0x020000 0x800000
}

OTHER_FILES += \
    README.txt

