/// \file InitializeInvaders.h
/// \brief initializes all invaders to starting position and active state
/// \author Thomas Collingwood
/// \version 1.0
/// \date 9/12/15 Updated to NCCA Coding standard

#ifndef _INITIALIZEINVADERS_H_
#define _INITIALIZEINVADERS_H_

#include <SDL.h>
#include <SDL_image.h>
#include <stdio.h>
#include <stdlib.h>

#include "Invader.h"

///
/// \brief initializeInvaders
/// \param invaders the 2d array of Invader struct objects
///
void initializeInvaders(Invader invaders[ROWS][COLS]);

#endif
