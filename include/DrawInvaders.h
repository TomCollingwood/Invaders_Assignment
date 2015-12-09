///
///  @file DrawInvaders.h
///  @brief Header file for DrawInvaders.c

#ifndef _DRAWINVADERS_H_
#define _DRAWINVADERS_H_

#include <SDL.h>
#include <SDL_image.h>
#include <stdio.h>
#include <stdlib.h>

#include "Dimensions.h"
#include "Invader.h"

void drawInvaders(SDL_Renderer *ren, SDL_Texture *tex, Invader invaders[ROWS][COLS]);

#endif
