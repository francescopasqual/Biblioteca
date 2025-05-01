QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++17

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    appcontroller.cpp \
    authenticator.cpp \
    biblioteca.cpp \
    cartaceo.cpp \
    catalogwindow.cpp \
    digitale.cpp \
    disco.cpp \
    epub.cpp \
    film.cpp \
    fisico.cpp \
    formato.cpp \
    item.cpp \
    libro.cpp \
    loginwindow.cpp \
    main.cpp \
    mainwindow.cpp \
    mp4.cpp \
    vinile.cpp

HEADERS += \
    appcontroller.h \
    authenticator.h \
    biblioteca.h \
    cartaceo.h \
    catalogwindow.h \
    digitale.h \
    disco.h \
    epub.h \
    film.h \
    fisico.h \
    formato.h \
    item.h \
    libro.h \
    loginwindow.h \
    mainwindow.h \
    mp4.h \
    vinile.h

FORMS += \
    mainwindow.ui

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target
