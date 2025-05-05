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
    catalogscreen.cpp \
    digitale.cpp \
    disco.cpp \
    epub.cpp \
    film.cpp \
    fisico.cpp \
    formato.cpp \
    item.cpp \
    itemdetailscreen.cpp \
    itemlistscreen.cpp \
    libro.cpp \
    loginscreen.cpp \
    main.cpp \
    mainwindow.cpp \
    mp4.cpp \
    vinile.cpp

HEADERS += \
    appcontroller.h \
    authenticator.h \
    biblioteca.h \
    cartaceo.h \
    catalogscreen.h \
    digitale.h \
    disco.h \
    epub.h \
    film.h \
    fisico.h \
    formato.h \
    item.h \
    itemdetailscreen.h \
    itemlistscreen.h \
    libro.h \
    loginscreen.h \
    mainwindow.h \
    mp4.h \
    vinile.h

FORMS +=

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target
