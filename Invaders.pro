QT -=gui
TARGET=Invaders
DESTDIR=./
SOURCES += \
    src/Main.c \
    src/TextFunctions.c \
    src/InvaderFunctions.c \
    src/BarrierFunctions.c \
    src/DefenderFunctions.c \
    src/MissileAndCollisionFunctions.c \
    src/HighscoreFunctions.c
HEADERS += \
    include/Defender.h \
    include/Missile.h \
    include/Invader.h \
    include/Dimensions.h \
    include/Direction.h \
    include/Headers.h \
    include/Highscore.h \
    include/InvaderFunctions.h \
    include/DefenderFunctions.h \
    include/BarrierFunctions.h \
    include/MissileAndCollisionFunctions.h \
    include/HighscoreFunctions.h \
    include/TextFunctions.h
cache()
QMAKE_CFLAGS+=-std=c99

CONFIG += console
CONFIG -= app_bundle

linux: {
  QMAKE_CFLAGS+=$$system(sdl2-config  --cflags)
  message(output from sdl2-config --cflags added to CXXFLAGS= $$QMAKE_CFLAGS)
  INCLUDEPATH+=/usr/local/include/SDL2
  LIBS+=$$system(sdl2-config  --libs)
  message(output from sdl2-config --libs added to LIB=$$LIBS)
  LIBS+=-lSDL2_image
}

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
