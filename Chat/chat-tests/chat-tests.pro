#-------------------------------------------------
#
# Project created by QtCreator 2018-05-13T20:22:27
#
#-------------------------------------------------

include(../qmake-target-platform.pri)
include(../qmake-destination-path.pri)

QT       += testlib

QT       -= gui

TARGET = tst_chattest
CONFIG   += console
CONFIG   -= app_bundle

TEMPLATE = app

# The following define makes your compiler emit warnings if you use
# any feature of Qt which has been marked as deprecated (the exact warnings
# depend on your compiler). Please consult the documentation of the
# deprecated API in order to know how to port your code away from it.
DEFINES += QT_DEPRECATED_WARNINGS

# You can also make your code fail to compile if you use deprecated APIs.
# In order to do so, uncomment the following line.
# You can also select to disable deprecated APIs only up to a certain version of Qt.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

# Additional import path used to resolve QML modules in Qt Creator's code model
QML_IMPORT_PATH = $$PWD

DESTDIR = $$PWD/../binaries/$$DESTINATION_PATH
OBJECTS_DIR = $$PWD/build/$$DESTINATION_PATH/.obj
MOC_DIR = $$PWD/build/$$DESTINATION_PATH/.moc
RCC_DIR = $$PWD/build/$$DESTINATION_PATH/.qrc
UI_DIR = $$PWD/build/$$DESTINATION_PATH/.ui

INCLUDEPATH += source \
    ../chat-lib/source

SOURCES += \
        tst_chattest.cpp \ 
    source/test-suite.cpp \
    source/main.cpp \
    source/controllers/master-controller-tests.cpp \
    source/data/int-decorator-tests.cpp \
    source/data/string-decorator-tests.cpp \
    source/data/datetime-decorator-tests.cpp \
    source/data/enumerator-decorator-tests.cpp \
    source/models/user-model-tests.cpp

DEFINES += SRCDIR=\\\"$$PWD/\\\"

HEADERS += \
    source/test-suite.h \
    source/controllers/master-controller-tests.h \
    source/mocks/mock-object-factory.h \
    source/data/int-decorator-tests.h \
    source/data/string-decorator-tests.h \
    source/data/datetime-decorator-tests.h \
    source/data/enumerator-decorator-tests.h \
    source/models/user-model-tests.h

#LIBS += -L$$PWD/../binaries/$$DESTINATION_PATH -lchat-lib
LIBS += -L$$PWD/../../build-Chat-Desktop_Qt_5_10_1_GCC_64bit-Debug/chat-lib -lchat-lib
