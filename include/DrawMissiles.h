/// \file DrawMissiles.h
/// \brief draws the missiles
/// \author Thomas Collingwood
/// \version 1.0
/// \date 9/12/15 Updated to NCCA Coding standard

#ifndef _DRAWMISSILES_H_
#define _DRAWMISSILES_H_

#include <SDL.h>
#include <SDL_image.h>
#include <stdio.h>
#include <stdlib.h>

#include "Missile.h"

///
/// \brief drawMissiles
/// \param ren the SDL_Renderer responsible for rendering images inside the window
/// \param tex the SDL_Texture texture image that contains the game's sprites
/// \param missiles the array of Missile structs (each can be of four different types)
///
void drawMissiles(SDL_Renderer *ren, SDL_Texture *tex, Missile missiles[]);

#endif
