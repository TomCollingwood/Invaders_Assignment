/// \file BarrierFunctions.h
/// \brief all functions that operate on Barriers
/// \author Thomas Collingwood
/// \version 1.0
/// \date 8/1/16 put all Barriers functions into one file

#ifndef _BARRIERFUNCTIONS_H_
#define _BARRIERFUNCTIONS_H_

#include <SDL.h>
#include <SDL_image.h>
#include <stdio.h>
#include <stdlib.h>

#include "Invader.h"
#include "Missile.h"

#define BARRIERWIDTH 22
#define BARRIERHEIGHT 16
#define BARRIERGAP 60
#define BARRIERSTARTX 100
#define BARRIERSTARTY 550

//----------------------------------------------------------------------------------------------------------------------
/// \brief blastBarrier       creates a blast centered around barriers[barrier][y][x].
///                           A blast is the undrawn barrier pixels in a blast shape.
///                           The type of blast (invader or defender) depends on type.
/// \param[inout] io_barriers The array of barriers (3d array representation of 3x3 pixel blocks)
/// \param[in] _barrier       Which barrier to blast
/// \param[in] _x             Co-ordinate of blast of barrier
/// \param[in] _y             Co-ordinate of blast of barrier
/// \param[in] _type          If type is 0 then it's an invader blast,
///                           if 1 then a defender blast
//----------------------------------------------------------------------------------------------------------------------
void blastBarrier(int io_barriers[4][BARRIERHEIGHT][BARRIERWIDTH],int _barrier, int _x, int _y, int _type);

//----------------------------------------------------------------------------------------------------------------------
/// \brief drawBarriers   This draws the barriers using SDL_RenderFillRect
/// \param[in] _ren the   SDL_Renderer responsible for rendering images inside the window
/// \param[in] _barriers  the array of barriers (3d array representation of 3x3 pixel blocks)
//----------------------------------------------------------------------------------------------------------------------
void drawBarriers(SDL_Renderer *_ren, int _barriers[4][BARRIERHEIGHT][BARRIERWIDTH]);

//----------------------------------------------------------------------------------------------------------------------
/// \brief initializeBarriers Sets all the barriers to default unblasted state
/// \param[inout] io_barriers the array of barriers (3d array representation of 3x3 pixel blocks)
//----------------------------------------------------------------------------------------------------------------------
void initializeBarriers(int io_barriers[4][BARRIERHEIGHT][BARRIERWIDTH]);

//----------------------------------------------------------------------------------------------------------------------
/// \brief updateBarriers   checks for missile collisions to barrier and calls blastBarrier
///                         if they collide
/// \param[inout]   io_barriers the array of barriers (3d array representation of 3x3 pixel blocks)
/// \param[inout]   io_missiles the array of Missile structs (each can be of four different types)
//----------------------------------------------------------------------------------------------------------------------
void updateBarriers(int io_barriers[4][BARRIERHEIGHT][BARRIERWIDTH], Missile io_missiles[MISSILESNUMBER]);

#endif
