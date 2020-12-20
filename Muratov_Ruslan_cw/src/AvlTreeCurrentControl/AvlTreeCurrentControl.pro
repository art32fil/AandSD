QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++11

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

# Чтобы программа запускалась через исполняемый файл
QMAKE_LFLAGS += -no-pie

SOURCES += \
    avltree.cpp \
    fullmatch.cpp \
    main.cpp \
    currentcontrol.cpp \
    oneof.cpp \
    questionanswer.cpp \
    questiongenerator.cpp

HEADERS += \
    avltree.h \
    currentcontrol.h \
    fullmatch.h \
    icheckstrategy.h \
    node.h \
    oneof.h \
    questionanswer.h \
    questiongenerator.h

FORMS += \
    currentcontrol.ui

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

DISTFILES +=
