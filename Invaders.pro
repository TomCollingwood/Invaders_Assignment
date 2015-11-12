#QT -=gui
#TARGET=Invaders
#DESTDIR=./
#SOURCES+=main.c
#HEADERS+=Invader.h
#cache()
#QMAKE_CFLAGS+=-std=c99
#QMAKE_CFLAGS+=$$system(sdl2-config  --cflags)
#QMAKE_CFLAGS+= -F/Library/Frameworks
#message(output from sdl2-config --cflags added to CXXFLAGS= $$QMAKE_CFLAGS)
#INCLUDEPATH+=/usr/local/include/SDL2
#LIBS+=$$system(sdl2-config  --libs)
#message(output from sdl2-config --libs added to LIB=$$LIBS)
##LIBS+=-lSDL2_image

#LIBS+= -framework SDL2
#LIBS+= -framework SDL2_image
#INCLUDEPATH += /Library/Frameworks/SLD2_image.framework
#INCLUDEPATH += /Library/Frameworks/SDL2.framework/Headers

#macx:DEFINES+=MAC_OS_X_VERSION_MIN_REQUIRED=1060
#CONFIG += console
#CONFIG -= app_bundle

TEMPLATE = app
CONFIG += console
CONFIG -= app_bundle
CONFIG -= qt

SOURCES += main.c
QMAKE_LFLAGS += -F/Library/Frameworks
LIBS += -framework SDL2
LIBS += -framework SDL2_image
INCLUDEPATH += /Library/Frameworks/SLD2_image.framework
INCLUDEPATH += /Library/Frameworks/SDL2.framework/Headers
INCLUDEPATH += /usr/local/include

#include(deployment.pri)
#qtcAddDeployment()

HEADERS += invader.h
