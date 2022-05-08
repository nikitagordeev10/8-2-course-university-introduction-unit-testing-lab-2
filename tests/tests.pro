include(gtest_dependency.pri)

TEMPLATE = app
CONFIG += console
CONFIG -= app_bundle
CONFIG += thread
CONFIG -= qt

QMAKE_CXXFLAGS += -Wall -Wextra
QMAKE_CFLAGS += -Wall -Wextra

# gcov
QMAKE_CXXFLAGS += -fprofile-arcs -ftest-coverage
QMAKE_CFLAGS += -fprofile-arcs -ftest-coverage
LIBS += -lgcov

DEFINES += INPUTDIR=\\\"$$PWD/\\\"

HEADERS += tests.h \
        ../editor/common.h \
        ../text/text.h \
        ../text/_text.h

SOURCES +=  main.cpp \
        ../editor/load.c \
        ../editor/move.c \
        ../editor/mpweb.c \
        ../editor/remove_next.c \
        ../editor/save.c \
        ../editor/show.c \
        ../editor/showunderscores.c \
        ../text/append_line.c \
        ../text/create_text.c \
        ../text/process_forward.c \
        ../text/remove_all.c

DISTFILES += ..tests/input/input.txt

INCLUDEPATH += ../text \
        ../editor
