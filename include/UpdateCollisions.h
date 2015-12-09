///
///  @file UpdateCollisions.h
///  @brief Header file for UpdateCollisions.c

#ifndef _UPDATECOLLISIONS_H_
#define _UPDATECOLLISIONS_H_

#include <stdio.h>
#include <stdlib.h>

#include "Defender.h"
#include "Invader.h"
#include "Missile.h"

void updateCollisions(Missile missiles[], Invader invaders[ROWS][COLS], Defender *defender, \
                      int *freeze, int *score, int frame);

#endif
