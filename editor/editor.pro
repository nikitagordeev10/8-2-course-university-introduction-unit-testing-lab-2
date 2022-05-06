TEMPLATE = app

CONFIG += console
CONFIG -= app_bundle
CONFIG -= qt

SOURCES = editor.c \
            load.c \
            move.c \
            mpweb.c \
            remove_next.c \
            save.c \
            show.c \
            showunderscores.c

INCLUDEPATH += ../text

HEADERS = common.h

LIBS += -L../text -ltext
TARGET = editor
