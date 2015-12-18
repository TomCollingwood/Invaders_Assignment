/// \file UpdateBarriers.h
/// \brief updates barriers to get blasted when missile collides with barrier
/// \author Thomas Collingwood
/// \version 1.0
/// \date 9/12/15 Updated to NCCA Coding standard

#ifndef _UPDATEBARRIERS_H_
#define _UPDATEBARRIERS_H_

#include "DrawBarriers.h"
#include "InitializeBarriers.h"
#include "Invader.h"
#include "Missile.h"

///
/// \brief updateBarriers
/// \param barriers the array of barriers (3d array representation of 3x3 pixel blocks)
/// \param missiles the array of Missile structs (each can be of four different types)
///
void updateBarriers(int barriers[4][BARRIERHEIGHT][BARRIERWIDTH], Missile missiles[MISSILESNUMBER]);

#endif
