QT -=gui
TARGET=Invaders
DESTDIR=./
SOURCES += \
    src/BlastBarrier.c \
    src/DrawBarriers.c \
    src/DrawDefender.c \
    src/DrawInvaders.c \
    src/DrawMissiles.c \
    src/DrawText.c \
    src/InitializeBarriers.c \
    src/InitializeDefender.c \
    src/InitializeHighscores.c \
    src/InitializeInvaders.c \
    src/InsertHighscore.c \
    src/Main.c \
    src/ReadHighscores.c \
    src/SelectLetter.c \
    src/UpdateBarriers.c \
    src/UpdateCollisions.c \
    src/UpdateDefender.c \
    src/UpdateInvaders.c \
    src/UpdateMissiles.c \
    src/WriteHighscores.c \
    src/HowManyActive.c
HEADERS += \
    include/Defender.h \
    include/Missile.h \
    include/Invader.h \
    include/Dimensions.h \
    include/Dir.h \
    include/Direction.h \
    include/DrawText.h \
    include/Headers.h \
    include/Highscore.h \
    include/SelectLetter.h \
    include/HowManyActive.h \
    include/InvaderFunctions.h \
    include/DefenderFunctions.h \
    include/BarrierFunctions.h \
    include/MissileAndCollisionFunctions.h \
    include/HighscoreFunctions.h
cache()
QMAKE_CFLAGS+=-std=c99
QMAKE_CFLAGS+=$$system(sdl2-config  --cflags)
message(output from sdl2-config --cflags added to CXXFLAGS= $$QMAKE_CFLAGS)
INCLUDEPATH+=/usr/local/include/SDL2
LIBS+=$$system(sdl2-config  --libs)
message(output from sdl2-config --libs added to LIB=$$LIBS)
LIBS+=-lSDL2_image

CONFIG += console
CONFIG -= app_bundle

macx: {
  DEFINES+=MAC_OS_X_VERSION_MIN_REQUIRED=1060
  QMAKE_LFLAGS += -F/Library/Frameworks
  LIBS += -framework SDL2
  LIBS += -framework SDL2_image
  LIBS += -framework SDL2_mixer
  INCLUDEPATH += /Library/Frameworks/SLD2_image.framework
  INCLUDEPATH += /Library/Frameworks/SLD2_mixer.framework
  INCLUDEPATH += /Library/Frameworks/SDL2.framework/Headers
  INCLUDEPATH += /usr/local/include
}

DISTFILES +=
