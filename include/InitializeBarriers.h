/// \file InitializeBarriers.h
/// \brief initializes barriers to unblasted state
/// \author Thomas Collingwood
/// \version 1.0
/// \date 9/12/15 Updated to NCCA Coding standard


#ifndef _INITIALIZEBARRIERS_H_
#define _INITIALIZEBARRIERS_H_

#include <SDL.h>
#include <SDL_image.h>
#include <stdio.h>
#include <stdlib.h>

#define BARRIERWIDTH 22
#define BARRIERHEIGHT 16

///
/// \brief initializeBarriers
/// \param barriers the array of barriers (3d array representation of 3x3 pixel blocks)
///
void initializeBarriers(int barriers[4][BARRIERHEIGHT][BARRIERWIDTH]);

#endif
