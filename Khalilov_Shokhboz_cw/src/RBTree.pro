#TEMPLATE = app
#TARGET = RBTree
##INCLUDEPATH += .
QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++20

DEFINES += QT_DEPRECATED_WARNINGS
# You can make your code fail to compile if you use deprecated APIs.
# In order to do so, uncomment the following line.
# Please consult the documentation of the deprecated API in order to know
# how to port your code away from it.
# You can also select to disable deprecated APIs only up to a certain version of Qt.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

# Input
HEADERS += documentation.h helperfunctions.h mainwindow.h node.hpp \
    libs.h
SOURCES += documentation.cpp \
           helperfunctions.cpp \
           main.cpp \
           mainwindow.cpp \
           node.cpp
RESOURCES += resource.qrc


# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target
