///
///  @file DrawMissiles.h
///  @brief Header file for DrawMissiles.c

#ifndef _DRAWMISSILES_H_
#define _DRAWMISSILES_H_

#include <SDL.h>
#include <SDL_image.h>
#include <stdio.h>
#include <stdlib.h>

#include "Missile.h"

void drawMissiles(SDL_Renderer *ren, SDL_Texture *tex, Missile missiles[]);

#endif
