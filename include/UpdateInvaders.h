///
///  @file UpdateInvaders.h
///  @brief Header file for UpdateInvaders.c

#ifndef _UPDATEINVADERS_H_
#define _UPDATEINVADERS_H_

#include <stdio.h>
#include <stdlib.h>

#include "Direction.h"
#include "Invader.h"
#include "Missile.h"

#define WIDTH 651
#define HEIGHT 744

void updateInvaders(Invader invaders[ROWS][COLS], Missile missiles[MISSILESNUMBER], \
                    int *freeze, int *howfast, int startscreen);

#endif
