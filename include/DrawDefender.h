/// \file DrawDefender.h
/// \brief draws the defender
/// \author Thomas Collingwood
/// \version 1.0
/// \date 9/12/15 Updated to NCCA Coding standard

#ifndef _DRAWDEFENDER_H_
#define _DRAWDEFENDER_H_

#include <SDL.h>
#include <SDL_image.h>
#include <stdio.h>
#include <stdlib.h>

#include "Defender.h"

///
/// \brief drawDefender
/// \param ren the SDL_Renderer responsible for rendering images inside the window
/// \param tex the SDL_Texture texture image that contains the game's sprites
/// \param defender the player controlled object that fires at space invaders
///
void drawDefender(SDL_Renderer *ren, SDL_Texture *tex, Defender *defender);

#endif
