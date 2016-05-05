#-------------------------------------------------
#
# Project created by QtCreator 2016-04-13T19:48:29
#
#-------------------------------------------------

QT       += core gui opengl
#LIBS += -lopengl32

QMAKE_CXXFLAGS += -std=c++0x

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = QtOpenGl
TEMPLATE = app


SOURCES += main.cpp\
    scene.cpp \
    field.cpp \
    object.cpp \
    liveobject.cpp \
    gamefield.cpp

HEADERS  += scene.h \
    field.h \
    object.h \
    liveobject.h \
    gamefield.h
