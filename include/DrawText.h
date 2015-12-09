///
///  @file DrawText.h
///  @brief Header file for DrawText.c

#ifndef _DRAWTEXT_H_
#define _DRAWTEXT_H_

#include <SDL.h>
#include <SDL_image.h>
#include <stdio.h>
#include <stdlib.h>

#define LETTERHEIGHT 21
#define LETTERWIDTH 15

void drawText(SDL_Renderer *ren, SDL_Texture *tex, char text[], int x, int y, float multiplier);

#endif
