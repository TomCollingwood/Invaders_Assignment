#include <SDL.h>
#include <SDL_image.h>
#include <stdio.h>
#include <stdlib.h>
#include <invader.h>
#include <missile.h>

void updateInvaders(Invader invaders[ROWS][COLS], Missile missiles[MISSILESNUMBER], \
                    int *freeze, int *howfast, int startscreen);
