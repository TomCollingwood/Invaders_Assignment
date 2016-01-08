/// \file BarrierFunctions.h
/// \brief put all Barrier related functions into this header and c file
/// \author Thomas Collingwood
/// \version 1.0
/// \date 9/12/15 Updated to NCCA Coding standard

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

///
/// \brief initializeBarriers
/// \param barriers the array of barriers (3d array representation of 3x3 pixel blocks)
///
void initializeBarriers(int barriers[4][BARRIERHEIGHT][BARRIERWIDTH]);

///
/// \brief updateBarriers
/// \param barriers the array of barriers (3d array representation of 3x3 pixel blocks)
/// \param missiles the array of Missile structs (each can be of four different types)
///
void updateBarriers(int barriers[4][BARRIERHEIGHT][BARRIERWIDTH], Missile missiles[MISSILESNUMBER]);

///
/// \brief drawBarriers
/// \param ren the SDL_Renderer responsible for rendering images inside the window
/// \param barriers the array of barriers (3d array representation of 3x3 pixel blocks)
///
void drawBarriers(SDL_Renderer *ren, int barriers[4][BARRIERHEIGHT][BARRIERWIDTH]);

///
/// \brief blastBarrier
/// blastBarrier creates a blast centered around barriers[barrier][y][x].
/// A blast is undrawn barrier pixels in a blast shape.
/// The type of blast (invader or defender) depends on type.
/// \param barriers the array of barriers (3d array representation of 3x3 pixel blocks)
/// \param barrier which barrier to blast
/// \param x coordinate of blast of barrier
/// \param y coordinate of blast of barrier
/// \param type if type is 0 then it's an invader blast, if 1 then a defender blast
///
void blastBarrier(int barriers[4][BARRIERHEIGHT][BARRIERWIDTH],int barrier, int x, int y, int type);


#endif
