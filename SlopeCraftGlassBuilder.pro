QT       += core gui concurrent

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

INCLUDEPATH += D:/CppLibs/eigen-3.4.0 \
                               ../SlopeCraft/Kernel

CONFIG += c++11

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    ../SlopeCraft/Kernel/CIEDE00.cpp \
    ../SlopeCraft/Kernel/WaterItem.cpp \
    ../SlopeCraft/Kernel/colorset.cpp \
    ../SlopeCraft/Kernel/tokicolor.cpp \
    PrimGlassBuilder.cpp \
    main.cpp \
    glassbuilderwind.cpp

HEADERS += \
    ../SlopeCraft/Kernel/ColorSet.h \
    ../SlopeCraft/Kernel/TokiColor.h \
    ../SlopeCraft/Kernel/WaterItem.h \
    PrimGlassBuilder.h \
    glassbuilderwind.h \
    object_pool.hpp

FORMS += \
    glassbuilderwind.ui

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target
