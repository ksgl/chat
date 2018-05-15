#-------------------------------------------------
#
# Project created by QtCreator 2018-04-21T12:14:49
#
#-------------------------------------------------

QT       -= gui

TARGET = chat-lib
TEMPLATE = lib
CONFIG += c++14

DEFINES += CHATLIB_LIBRARY
INCLUDEPATH += source

# The following define makes your compiler emit warnings if you use
# any feature of Qt which has been marked as deprecated (the exact warnings
# depend on your compiler). Please consult the documentation of the
# deprecated API in order to know how to port your code away from it.
DEFINES += QT_DEPRECATED_WARNINGS

# You can also make your code fail to compile if you use deprecated APIs.
# In order to do so, uncomment the following line.
# You can also select to disable deprecated APIs only up to a certain version of Qt.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    source/controllers/master-controller.cpp \
    source/framework/object-factory.cpp \
    source/framework/command.cpp \
    source/controllers/command-controller.cpp \
    source/data/data-decorator.cpp \
    source/data/string-decorator.cpp

HEADERS += \
    source/chat-lib_global.h \
    source/controllers/master-controller.h \
    source/framework/object-factory.h \
    source/framework/i-object-factory.h \
    source/chat-lib_global.h \
    source/controllers/navigation-controller.h \
    source/controllers/i-navigation-controller.h \
    source/controllers/i-command-controller.h \
    source/framework/command.h \
    source/controllers/command-controller.h \
    source/data/data-decorator.h \
    source/data/string-decorator.h

unix {
    target.path = /usr/lib
    INSTALLS += target
}
