TEMPLATE = lib

CONFIG -= app_bundle
CONFIG -= qt
CONFIG += staticlib

SOURCES += append_line.c \
            create_text.c \
            move_crsr.c \
            process_forward.c \
            remove_all.c

HEADERS += text.h
