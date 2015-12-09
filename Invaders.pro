#QT -=gui
#TARGET=Invaders
#DESTDIR=./
#SOURCES+=main.c
#HEADERS+=Invader.h \
#    Missile.h
#cache()
#QMAKE_CFLAGS+=-std=c99
#QMAKE_CFLAGS+=$$system(sdl2-config  --cflags)
#message(output from sdl2-config --cflags added to CXXFLAGS= $$QMAKE_CFLAGS)
#INCLUDEPATH+=/usr/local/include/SDL2
#LIBS+=$$system(sdl2-config  --libs)
#message(output from sdl2-config --libs added to LIB=$$LIBS)
#LIBS+=-lSDL2_image
#macx:DEFINES+=MAC_OS_X_VERSION_MIN_REQUIRED=1060
#CONFIG += console
#CONFIG -= app_bundle

TEMPLATE = app
CONFIG += console
CONFIG -= app_bundle
CONFIG -= qt

SOURCES += main.c \
    drawText.c \
    updateInvaders.c \
    initializeInvaders.c \
    initializeHighscores.c \
    selectLetter.c \
    insertHighscore.c \
    initializeBarriers.c \
    drawBarriers.c \
    updateBarriers.c \
    blastBarrier.c \
    readHighscores.c \
    writeHighscores.c \
    updateCollisions.c \
    initializeDefender.c \
    drawMissiles.c \
    updateMissiles.c \
    updateDefender.c \
    drawInvaders.c \
    drawDefender.c
QMAKE_LFLAGS += -F/Library/Frameworks
LIBS += -framework SDL2
LIBS += -framework SDL2_image
LIBS += -framework SDL2_mixer
INCLUDEPATH += /Library/Frameworks/SLD2_image.framework
INCLUDEPATH += /Library/Frameworks/SLD2_mixer.framework
INCLUDEPATH += /Library/Frameworks/SDL2.framework/Headers
INCLUDEPATH += /usr/local/include

HEADERS += \
    Defender.h \
    drawText.h \
    updateInvaders.h \
    initializeInvaders.h \
    drawHighscore.h \
    highscore.h \
    initializeHighscores.h \
    direction.h \
    selectLetter.h \
    insertHighscore.h \
    initializeBarriers.h \
    drawBarriers.h \
    updateBarriers.h \
    blastBarrier.h \
    readHighscores.h \
    writeHighscores.h \
    Missile.h \
    updateCollisions.h \
    initializeDefender.h \
    headers.h \
    drawMissiles.h \
    updateMissiles.h \
    dir.h \
    Invader.h \
    dimensions.h \
    updateDefender.h \
    drawInvaders.h \
    drawDefender.h

DISTFILES +=

