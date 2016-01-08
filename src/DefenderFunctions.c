///
///  @file DefenderFunctions.c
///  @brief

#include "include/DefenderFunctions.h"

void drawDefender(SDL_Renderer *ren, SDL_Texture *tex, Defender *defender)
{
  SDL_Rect SrcRS0;
  SrcRS0.x=0;
  SrcRS0.y=0;
  SrcRS0.w=DEFENDERWIDTH;
  SrcRS0.h=DEFENDERHEIGHT;

  SDL_Rect SrcRS1;
  SrcRS1.x=111;
  SrcRS1.y=27;
  SrcRS1.w=EXPLODEDDEFENDERWIDTH;
  SrcRS1.h=DEFENDERHEIGHT;

  SDL_Rect SrcRS2;
  SrcRS2.x=69;
  SrcRS2.y=105;
  SrcRS2.w=EXPLODEDDEFENDERWIDTH;
  SrcRS2.h=DEFENDERHEIGHT;

  if(defender->sprite==0)
  {
    SDL_RenderCopy(ren,tex,&SrcRS0,&defender->pos);
  }
  else
  {
    if(defender->sprite==1)
    {
      SDL_RenderCopy(ren,tex,&SrcRS1,&defender->pos);
    }
    else {
      SDL_RenderCopy(ren,tex,&SrcRS2,&defender->pos);
    }
  }
}

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
