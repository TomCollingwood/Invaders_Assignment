///
///  @file UpdateBarriers.h
///  @brief Header file for UpdateBarriers.c

#ifndef _UPDATEBARRIERS_H_
#define _UPDATEBARRIERS_H_

#include "DrawBarriers.h"
#include "InitializeBarriers.h"
#include "Invader.h"
#include "Missile.h"

void updateBarriers(int barriers[4][BARRIERHEIGHT][BARRIERWIDTH], Missile missiles[MISSILESNUMBER]);

#endif
