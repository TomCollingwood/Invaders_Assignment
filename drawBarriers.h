#include <SDL.h>
#include <SDL_image.h>
#include <stdio.h>
#include <stdlib.h>
#include "initializeBarriers.h"

#define BARRIERGAP 60
#define BARRIERSTARTX 100

void drawBarriers(SDL_Renderer *ren, int barriers[4][BARRIERHEIGHT][BARRIERWIDTH]);
