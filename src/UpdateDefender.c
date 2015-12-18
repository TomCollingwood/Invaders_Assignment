///
///  @file UpdateDefender.c
///  @brief updates defender position depending on input - also updates sprite when exploded

#include "include/UpdateDefender.h"
// Updates defender position and creates new defender missiles if SPACE bar hit
void updateDefender(Defender *defender, enum DIRECTION input, Missile missiles[], int *freeze)
{
  if(defender->active)
  {
    if(input == RIGHT)
    {
      defender->pos.x += 5;
    }
    else if (input == LEFT)
    {
      defender->pos.x += -5;
    }

    // below makes defender come out at other side when gone too far off screen
    if(defender->pos.x<-DEFENDERWIDTH)
    {
      defender->pos.x=WIDTH+DEFENDERWIDTH;
    }
    else if(defender->pos.x>WIDTH+DEFENDERWIDTH)
    {
      defender->pos.x=-DEFENDERWIDTH;
    }

    // Here we create a new missile
    else if (input == FIRE && missiles[0].active==0 && *freeze==0)
    {
      Missile newmissile;
      newmissile.dir = UP;
      newmissile.pos.x = defender->pos.x + 18;
      newmissile.pos.y = defender->pos.y - 10;
      newmissile.pos.w = 3;
      newmissile.pos.h = 14;
      newmissile.active = 1;
      newmissile.type = DEFENDER;
      missiles[0] = newmissile;
    }
  }
  else
  {
    // here we animate the exploded defender (not draw just update sprite)
    defender->frame++;
    if(defender->frame%5==0) (defender->sprite == 1) ? (defender->sprite=2) : (defender->sprite=1);
  }
}
