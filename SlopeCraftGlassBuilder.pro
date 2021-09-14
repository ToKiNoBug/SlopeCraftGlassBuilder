QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

INCLUDEPATH += D:/eigen-3.3.9 \
                               ../SlopeCraft/Kernel

CONFIG += c++11

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    ../SlopeCraft/Kernel/WaterItem.cpp \
    GlassBuilder.cpp \
    main.cpp \
    glassbuilderwind.cpp

HEADERS += \
    ../SlopeCraft/Kernel/WaterItem.h \
    GlassBuilder.h \
    glassbuilderwind.h

FORMS += \
    glassbuilderwind.ui

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target
