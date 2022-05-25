TARGET = pyatnashki

QT += core gui widgets
CONFIG += c++11

win32: COMPILE_DATE = $$system(date /T)
unix: COMPILE_DATE = $$system(date +%d.%m.%Y)
VERSION = $$sprintf("%1.%2.%3", $$section(COMPILE_DATE, ., 0, 0), $$section(COMPILE_DATE, ., 1, 1), $$section(COMPILE_DATE, ., 2, 2))

CONFIG(release, debug|release){
    DESTDIR = release
    MOC_DIR = release/moc
    OBJECTS_DIR = release/obj
    DEFINES += QT_NO_DEBUG_OUTPUT
} else {
    DESTDIR = debug
    MOC_DIR = debug/moc
    OBJECTS_DIR = debug/obj
}

SOURCES += \
    application.cpp \
    board.cpp \
    cell.cpp \
    dynamiccell.cpp \
    field.cpp \
    functions.cpp \
    main.cpp \
    mainwindow.cpp

HEADERS += \
    application.h \
    board.h \
    cell.h \
    dynamiccell.h \
    field.h \
    functions.h \
    mainwindow.h

FORMS += \
    mainwindow.ui

RESOURCES += \
    files.qrc
