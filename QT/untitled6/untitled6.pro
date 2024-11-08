QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++17

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    control.cpp \
    expression.cpp \
    main.cpp \
    mainwindow.cpp \
    tdicethread.cpp \
    vision.cpp

HEADERS += \
    User_uart.h \
    control.h \
    expression.h \
    mainwindow.h \
    tdicethread.h \
    vision.h

FORMS += \
    control.ui \
    expression.ui \
    mainwindow.ui \
    vision.ui

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

INCLUDEPATH += E:\opencv\opencv\rebuild_for_qt\install\include
LIBS += E:\opencv\opencv\rebuild_for_qt\lib\libopencv_*.a

QT += serialport

RESOURCES += \
    expression_picture.qrc
