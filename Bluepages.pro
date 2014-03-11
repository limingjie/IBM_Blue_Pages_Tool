# -------------------------------------------------
# Project created by QtCreator 2010-07-01T14:26:00
# -------------------------------------------------
QT += network
TARGET = Bluepages
TEMPLATE = app
SOURCES += main.cpp \
    mainwindow.cpp \
    bluepages.cpp \
    progressdialog.cpp \
    headerdialog.cpp
HEADERS += mainwindow.h \
    bluepages.h \
    progressdialog.h \
    headerdialog.h
RESOURCES += icons.qrc
RC_FILE = icon.rc
OTHER_FILES += icon.rc \
    Changes.txt \
    Readme.txt

CONFIG(release, debug|release) {
    CONFIG += static
    DEFINES += STATIC
    message( "release" )
}

CONFIG(debug, debug|release) {
    message( "debug" )
}
