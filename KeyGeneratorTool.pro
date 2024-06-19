QT       += core gui network

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++17
LIBS += -L$$[QT_INSTALL_LIBS]
# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

INCLUDEPATH += "D:\ProgramFiles\OpenSSL-Win64\include"
LIBS += -L"D:\ProgramFiles\OpenSSL-Win64\lib\VC\x64\MT" -llibcrypto_static -llibssl_static

SOURCES += \
    Toast.cpp \
    common/BaseWindow.cpp \
    common/TitleBar.cpp \
    common/basecontroller.cpp \
    main.cpp \
    generatortool.cpp

HEADERS += \
    Toast.h \
    common/BaseWindow.h \
    common/TitleBar.h \
    common/basecontroller.h \
    generatortool.h

FORMS += \
    Toast.ui \
    generatortool.ui

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

RESOURCES += \
    res.qrc
RC_ICONS = mfc.ico
