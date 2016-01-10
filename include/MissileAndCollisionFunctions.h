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

//----------------------------------------------------------------------------------------------------------------------
/// \brief drawMissiles   draws the missiles on screen depending on missile type and SDL_Rect
/// \param[in] _ren       the SDL_Renderer responsible for rendering images inside the window
/// \param[in] _tex       the SDL_Texture texture image that contains the game's sprites
/// \param[in] _missiles  the array of Missile structs (each can be of four different types)
//----------------------------------------------------------------------------------------------------------------------
void drawMissiles(SDL_Renderer *_ren, SDL_Texture *_tex, Missile _missiles[]);

//----------------------------------------------------------------------------------------------------------------------
/// \brief updateCollisions   this checks to see if missiles have collided with
///                           defender or invaders. When collided it makes the invader
///                           or defender destroyed and adds to the current score.
/// \param[inout] io_missiles the array of Missile structs (each can be of four different types)
/// \param[inout] io_invaders the 2d array of Invader struct objects
/// \param[inout] io_defender the player controlled object that fires at space invaders
/// \param[out] o_freeze      if freeze==1 then no collisions are updated
/// \param[out] o_score       the current score of the session (this is incremented when invader
///                           collisions happen)
/// \param[in] _frame         the score of each invader killed is dependant on the time spent
///                           in the game session. We measure time with frames.
//----------------------------------------------------------------------------------------------------------------------
void updateCollisions(Missile missiles[], Invader invaders[ROWS][COLS], Defender *defender, \
                      int *freeze, int *score, int frame);

//----------------------------------------------------------------------------------------------------------------------
/// \brief updateMissiles     updates all active missiles' position: going up or down
/// \param[inout] io_missiles the array of Missile structs (each can be of four different types)
//----------------------------------------------------------------------------------------------------------------------
void updateMissiles(Missile io_missiles[]);

#endif
