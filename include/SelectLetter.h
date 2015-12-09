///
///  @file SelectLetter.h
///  @brief Header file for SelectLetter.c

#ifndef _SELECTLETTER_H_
#define _SELECTLETTER_H_

#include <SDL.h>
#include <SDL_image.h>
#include <stdio.h>
#include <stdlib.h>

#include "Direction.h"
#include "DrawText.h"

int selectLetter(int asciinumber, enum DIRECTION input, enum DIRECTION previousinput);

#endif
