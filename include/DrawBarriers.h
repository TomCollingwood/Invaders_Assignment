///
///  @file DrawBarriers.h
/// \file DrawBarriers.h
/// \brief draws the four barriers from an 3d int array
/// \author Thomas Collingwood
/// \version 1.0
/// \date 9/12/15 Updated to NCCA Coding standard
/// Revision History :
/// Initial Version 6/12/15
/// \todo

#ifndef _DRAWBARRIERS_H_
#define _DRAWBARRIERS_H_

#include <SDL.h>
#include <SDL_image.h>
#include <stdio.h>
#include <stdlib.h>

#include "InitializeBarriers.h"

#define BARRIERGAP 60
#define BARRIERSTARTX 100
#define BARRIERSTARTY 550

void drawBarriers(SDL_Renderer *ren, int barriers[4][BARRIERHEIGHT][BARRIERWIDTH]);

#endif
