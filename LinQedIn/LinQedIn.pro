#-------------------------------------------------
#
# Project created by QtCreator 2014-12-11T18:48:45
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

QT += xml

TARGET = LinQedIn
TEMPLATE = app


SOURCES += main.cpp\
        mainwindow.cpp \
    utente.cpp \
    utentebasic.cpp \
    utentebusiness.cpp \
    utenteexecutive.cpp \
    info.cpp \
    username.cpp \
    rete.cpp \
    linqedinclient.cpp \
    linqedinadmin.cpp \
    db.cpp \
    showprofile.cpp \
    usermainwindow.cpp \
    adminmainwindow.cpp \
    registrationwindow.cpp \
    modifyprofile.cpp \
    showprofilefind.cpp

HEADERS  += mainwindow.h \
    utente.h \
    utentebasic.h \
    utentebusiness.h \
    utenteexecutive.h \
    info.h \
    username.h \
    rete.h \
    linqedinclient.h \
    linqedinadmin.h \
    db.h \
    showprofile.h \
    usermainwindow.h \
    adminmainwindow.h \
    registrationwindow.h \
    modifyprofile.h \
    showprofilefind.h

FORMS    += mainwindow.ui \
    showprofile.ui \
    usermainwindow.ui \
    adminmainwindow.ui \
    registrationwindow.ui \
    modifyprofile.ui \
    showprofilefind.ui
