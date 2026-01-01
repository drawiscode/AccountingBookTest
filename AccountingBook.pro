QT       += core gui sql

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++17

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    addrecordwindow.cpp \
    database.cpp \
    #main.cpp \
    mainwindow.cpp \
    querymanager.cpp \
    querywindow.cpp \
    statisticsmanager.cpp \
    statisticswindow.cpp \
    tests/integrationTest.cpp \
    #tests/test_querymanager.cpp \
    #tests/test_statisticsmanager.cpp \
    transaction.cpp\
    googletest-main/googletest/src/gtest-all.cc \
    googletest-main/googletest/src/gtest_main.cc

HEADERS += \
    addrecordwindow.h \
    database.h \
    mainwindow.h \
    querymanager.h \
    querywindow.h \
    statisticsmanager.h \
    statisticswindow.h \
    transaction.h

FORMS += \
    addrecordwindow.ui \
    mainwindow.ui \
    querywindow.ui \
    statisticswindow.ui


# -------------------------
# GoogleTest include path
# -------------------------
INCLUDEPATH += \
    $$PWD/googletest-main/googletest/include \
    $$PWD/googletest-main/googletest

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

DISTFILES += \

