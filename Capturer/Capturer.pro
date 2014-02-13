#-------------------------------------------------
#
# Project created by QtCreator 2013-02-15T00:47:09
#
#-------------------------------------------------

QT       += core gui
QT       += multimedia multimediawidgets

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = Capturer
TEMPLATE = app


SOURCES += main.cpp\
        imageviewerwindow.cpp \
    acercadedialog.cpp \
    capturebuffer.cpp \
    preferencesdialog.cpp

HEADERS  += imageviewerwindow.h \
    acercadedialog.h \
    capturebuffer.h \
    preferencesdialog.h

FORMS    += imageviewerwindow.ui \
    acercadedialog.ui \
    preferencesdialog.ui
