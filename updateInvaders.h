#include <stdio.h>
#include <stdlib.h>
#include "invader.h"
#include "direction.h"
#include "Missile.h"

#define WIDTH 651
#define HEIGHT 744

void updateInvaders(Invader invaders[ROWS][COLS], Missile missiles[MISSILESNUMBER], \
                    int *freeze, int *howfast, int startscreen);
