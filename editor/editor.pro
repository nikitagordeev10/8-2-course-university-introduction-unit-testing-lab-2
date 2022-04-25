TEMPLATE = app

CONFIG -= app_bundle
CONFIG -= qt

SOURCES = editor.c \
            load.c \
            save.c \
            show.c

INCLUDEPATH += ../text

HEADERS = common.h

LIBS += -L../text -ltext
TARGET = editor
