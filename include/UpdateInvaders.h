/// \file UpdateInvaders.h
/// \brief updates invaders' position and sprite
/// \author Thomas Collingwood
/// \version 1.0
/// \date 9/12/15 Updated to NCCA Coding standard

#ifndef _UPDATEINVADERS_H_
#define _UPDATEINVADERS_H_

#include <stdio.h>
#include <stdlib.h>

#include "Direction.h"
#include "HowManyActive.h"
#include "Invader.h"
#include "Missile.h"

#define WIDTH 651
#define HEIGHT 744

///
/// \brief updateInvaders
/// \param invaders the 2d array of Invader struct objects
/// \param missiles the array of Missile structs (each can be of four different types)
/// \param freeze if freeze==1 the invaders do no move their position
/// \param howfast the lower howfast is, the faster the invaders move
/// \param startscreen if startscreen==1 then the invader's y position is not incremented
///
void updateInvaders(Invader invaders[ROWS][COLS], Missile missiles[MISSILESNUMBER], \
                    int *freeze, int *howfast, int startscreen);

#endif
