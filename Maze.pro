greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++11

HEADERS += \
    src/gamescene.h \
    src/maze.h \
    src/view.h

SOURCES += \
    src/gamescene.cpp \
    src/main.cpp \
    src/maze.cpp \
    src/view.cpp
