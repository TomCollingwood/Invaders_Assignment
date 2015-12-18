/// \file UpdateCollisions.h
/// \brief updates invader's / defender's active variable when missile collides with it
/// \author Thomas Collingwood
/// \version 1.0
/// \date 9/12/15 Updated to NCCA Coding standard

#ifndef _UPDATECOLLISIONS_H_
#define _UPDATECOLLISIONS_H_

#include <stdio.h>
#include <stdlib.h>

#include "Defender.h"
#include "Invader.h"
#include "Missile.h"

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

#endif
