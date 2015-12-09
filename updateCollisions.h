#include <stdio.h>
#include <stdlib.h>
#include "Invader.h"
#include "Defender.h"
#include "Missile.h"

void updateCollisions(Missile missiles[], Invader invaders[ROWS][COLS], Defender *defender, \
                      int *freeze, int *score, int frame);
