/// \file DefenderFunctions.h
/// \brief put all Defender functions into this header and c file
/// \author Thomas Collingwood
/// \version 1.0
/// \date 9/12/15 Updated to NCCA Coding standard

#ifndef _DEFENDERFUNCTIONS_H_
#define _DEFENDERFUNCTIONS_H_

#include <stdio.h>
#include <stdlib.h>

#include "Defender.h"
#include "Dimensions.h"
#include "Direction.h"
#include "Missile.h"

///
/// \brief initializeDefender
/// \param defender the player controlled object that fires at space invaders
///
void initializeDefender(Defender *defender);

///
/// \brief updateDefender
/// \param defender the player controlled object that fires at space invaders
/// \param input the input from the player
/// \param missiles the array of Missile structs (each can be of four different types)
/// \param [inout] freeze if freeze==1 a new missile cannot be fired from defender
///
void updateDefender(Defender *defender, enum DIRECTION input, Missile missiles[], int *freeze);

///
/// \brief drawDefender
/// \param ren the SDL_Renderer responsible for rendering images inside the window
/// \param tex the SDL_Texture texture image that contains the game's sprites
/// \param defender the player controlled object that fires at space invaders
///
void drawDefender(SDL_Renderer *ren, SDL_Texture *tex, Defender *defender);

#endif
