///
///  @file InitializeBarriers.h
///  @brief Header file for InitializeBarriers.c

#ifndef _INITIALIZEBARRIERS_H_
#define _INITIALIZEBARRIERS_H_

#include <SDL.h>
#include <SDL_image.h>
#include <stdio.h>
#include <stdlib.h>

#define BARRIERWIDTH 22
#define BARRIERHEIGHT 16

void initializeBarriers(int barriers[4][BARRIERHEIGHT][BARRIERWIDTH]);

#endif
