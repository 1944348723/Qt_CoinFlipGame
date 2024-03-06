QT       += core gui multimedia

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++17

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

# msvc:QMAKE_CXXFLAGS += -execution-charset:utf-8

SOURCES += \
    coin.cpp \
    levelmap.cpp \
    levelselectionscene.cpp \
    main.cpp \
    basewindow.cpp \
    mainscene.cpp \
    mypushbutton.cpp \
    playscene.cpp

HEADERS += \
    basewindow.h \
    coin.h \
    levelmap.h \
    levelselectionscene.h \
    mainscene.h \
    mypushbutton.h \
    playscene.h

FORMS += \
    basewindow.ui

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

RESOURCES += \
    res.qrc
