/// \file BlastBarrier.h
/// \brief updates a barriers to have a crater spreading outwards from coordinates given
/// \author Thomas Collingwood
/// \version 1.0
/// \date 9/12/15 Updated to NCCA Coding standard

#ifndef _BLASTBARRIER_H_
#define _BLASTBARRIER_H_

#include <stdio.h>
#include <stdlib.h>

#include "InitializeBarriers.h"

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
