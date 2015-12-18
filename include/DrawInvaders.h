/// \file DrawInvaders.h
/// \brief draws the invaders
/// \author Thomas Collingwood
/// \version 1.0
/// \date 9/12/15 Updated to NCCA Coding standard

#ifndef _DRAWINVADERS_H_
#define _DRAWINVADERS_H_

#include <SDL.h>
#include <SDL_image.h>
#include <stdio.h>
#include <stdlib.h>

#include "Dimensions.h"
#include "Invader.h"

///
/// \brief drawInvaders
/// \param ren the SDL_Renderer responsible for rendering images inside the window
/// \param tex the SDL_Texture texture image that contains the game's sprites
/// \param invaders the 2d array of Invader struct objects
///
void drawInvaders(SDL_Renderer *ren, SDL_Texture *tex, Invader invaders[ROWS][COLS]);

#endif
