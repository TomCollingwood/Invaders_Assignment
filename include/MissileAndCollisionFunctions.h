/// \file MissileAndCollisionFunctions.h
/// \brief put all Missile and Collision functions in this header and c file
/// \author Thomas Collingwood
/// \version 1.0
/// \date 8/1/16 Merged all related functions

#ifndef _MISSILEANDCOLLISIONFUNCTION_H_
#define _MISSILEANDCOLLISIONFUNCTION_H_

#include <SDL.h>
#include <SDL_image.h>
#include <stdio.h>
#include <stdlib.h>

#include "Dimensions.h"
#include "Missile.h"
#include "Defender.h"

///
/// \brief updateMissiles
/// \param missiles the array of Missile structs (each can be of four different types)
///
void updateMissiles(Missile missiles[]);

///
/// \brief updateCollisions
/// \param missiles the array of Missile structs (each can be of four different types)
/// \param invaders the 2d array of Invader struct objects
/// \param defender the player controlled object that fires at space invaders
/// \param freeze if freeze==1 then no collisions are updated
/// \param score the current score of the session (this is incremented when invader
/// collisions happen)
/// \param frame the score of each invader killed is dependant on the time spent
/// in the game session. We measure time with frames.
///
void updateCollisions(Missile missiles[], Invader invaders[ROWS][COLS], Defender *defender, \
                      int *freeze, int *score, int frame);

///
/// \brief drawMissiles
/// \param ren the SDL_Renderer responsible for rendering images inside the window
/// \param tex the SDL_Texture texture image that contains the game's sprites
/// \param missiles the array of Missile structs (each can be of four different types)
///
void drawMissiles(SDL_Renderer *ren, SDL_Texture *tex, Missile missiles[]);

#endif
