/// \file DefenderFunctions.h
/// \brief put all Defender functions into this header and c file
/// \author Thomas Collingwood
/// \version 1.0
/// \date 9/12/15 Updated to NCCA Coding standard

#ifndef _DEFENDERFUNCTIONS_H_
#define _DEFENDERFUNCTIONS_H_

#include <stdio.h>
#include <stdlib.h>

#include <SDL.h>
#include <SDL_image.h>

#include "Defender.h"
#include "Dimensions.h"
#include "Direction.h"
#include "Missile.h"

//----------------------------------------------------------------------------------------------------------------------
/// \brief drawDefender draws the Defender with SDL_RenderCopy
/// \param[in] _ren           the SDL_Renderer responsible for rendering images inside the window
/// \param[in] _tex           the SDL_Texture texture image that contains the game's sprites
/// \param[inout] io_defender the player controlled object that fires at space invaders
//----------------------------------------------------------------------------------------------------------------------
void drawDefender(SDL_Renderer *_ren, SDL_Texture *_tex, Defender *io_defender);

//----------------------------------------------------------------------------------------------------------------------
/// \brief initializeDefender initializes Defender's position and active state
/// \param[out] o_defender    the player controlled object that fires at space invaders
//----------------------------------------------------------------------------------------------------------------------
void initializeDefender(Defender *o_defender);

//----------------------------------------------------------------------------------------------------------------------
/// \brief updateDefender     updates the defender's position and creates missiles depending
/// on input
/// \param[inout] io_defender the player controlled object that fires at space invaders
/// \param[in] _input         the input from the player
/// \param[inout] io_missiles the array of Missile structs (each can be of four different types)
/// \param[in] _freeze        if freeze==1 a new missile cannot be fired from defender
//----------------------------------------------------------------------------------------------------------------------
void updateDefender(Defender *io_defender, enum DIRECTION _input, Missile io_missiles[], int _freeze);

#endif
