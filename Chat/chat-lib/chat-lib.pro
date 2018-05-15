#-------------------------------------------------
#
# Project created by QtCreator 2018-04-21T12:14:49
#
#-------------------------------------------------

include(../qmake-target-platform.pri)
include(../qmake-destination-path.pri)


QT       -= gui

TARGET = chat-lib
TEMPLATE = lib
CONFIG += c++14

DEFINES += CHATLIB_LIBRARY
INCLUDEPATH += source

DESTDIR = $$PWD/../binaries/$$DESTINATION_PATH
OBJECTS_DIR = $$PWD/build/$$DESTINATION_PATH/.obj
MOC_DIR = $$PWD/build/$$DESTINATION_PATH/.moc
RCC_DIR = $$PWD/build/$$DESTINATION_PATH/.qrc
UI_DIR = $$PWD/build/$$DESTINATION_PATH/.ui

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
    source/data/entity.cpp \
    source/data/data-decorator.cpp \
    source/data/string-decorator.cpp \
    source/data/int-decorator.cpp \
    source/data/datetime-decorator.cpp \
    source/data/enumerator-decorator.cpp \
    source/models/user-model.cpp \
    source/models/friend.cpp \
    source/models/message.cpp \
    source/models/chat-model.cpp \
    source/controllers/friend-controller.cpp \
    source/controllers/message-controller.cpp

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
    source/data/entity.h \
    source/data/entity-collection.h \
    source/data/data-decorator.h \
    source/data/string-decorator.h \
    source/data/int-decorator.h \
    source/data/datetime-decorator.h \
    source/data/enumerator-decorator.h \
    source/models/user-model.h \
    source/models/friend.h \
    source/models/message.h \
    source/models/chat-model.h \
    source/controllers/i-database-controller.h \
    source/controllers/i-user-controller.h \
    source/controllers/friend-controller.h \
    source/controllers/message-controller.h

unix {
    target.path = /usr/lib
    INSTALLS += target
}
