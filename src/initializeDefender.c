#include "initializeDefender.h"

// Initializes defender starting position and size
void initializeDefender(Defender *defender)
{
  defender->pos.x=WIDTH/2 - SPRITEWIDTH/2;
  defender->pos.y=HEIGHT-80;
  defender->pos.w=39;
  defender->pos.h=24;
  defender->sprite=0;
  defender->active=1;
  defender->frame=0;
}
