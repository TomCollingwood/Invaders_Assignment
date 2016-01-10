///
///  @file DefenderFunctions.c
///  @brief all the functions that operate directly on the defender

#include "include/DefenderFunctions.h"

//----------------------------------------------------------------------------------------------------------------------
void drawDefender(SDL_Renderer *_ren, SDL_Texture *_tex, Defender *io_defender)
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

  if(io_defender->sprite==0)
  {
    SDL_RenderCopy(_ren,_tex,&SrcRS0,&io_defender->pos);
  }
  else
  {
    if(io_defender->sprite==1)
    {
      SDL_RenderCopy(_ren,_tex,&SrcRS1,&io_defender->pos);
    }
    else {
      SDL_RenderCopy(_ren,_tex,&SrcRS2,&io_defender->pos);
    }
  }
}

//----------------------------------------------------------------------------------------------------------------------
void initializeDefender(Defender *o_defender)
{
  o_defender->pos.x=WIDTH/2 - SPRITEWIDTH/2;
  o_defender->pos.y=HEIGHT-80;
  o_defender->pos.w=39;
  o_defender->pos.h=24;
  o_defender->sprite=0;
  o_defender->active=1;
  o_defender->frame=0;
}

//----------------------------------------------------------------------------------------------------------------------
void updateDefender(Defender *io_defender, enum DIRECTION _input, Missile io_missiles[], int _freeze)
{
  if(io_defender->active)
  {
    if(_input == RIGHT)
    {
      io_defender->pos.x += 5;
    }
    else if (_input == LEFT)
    {
      io_defender->pos.x += -5;
    }

    // below makes defender come out at other side when gone too far off screen
    if(io_defender->pos.x<-DEFENDERWIDTH)
    {
      io_defender->pos.x=WIDTH+DEFENDERWIDTH;
    }
    else if(io_defender->pos.x>WIDTH+DEFENDERWIDTH)
    {
      io_defender->pos.x=-DEFENDERWIDTH;
    }

    // Here we create a new missile
    else if (_input == FIRE && io_missiles[0].active==0 && _freeze==0)
    {
      Missile newmissile;
      newmissile.dir = UP;
      newmissile.pos.x = io_defender->pos.x + 18;
      newmissile.pos.y = io_defender->pos.y - 10;
      newmissile.pos.w = 3;
      newmissile.pos.h = 14;
      newmissile.active = 1;
      newmissile.type = DEFENDER;
      io_missiles[0] = newmissile;
    }
  }
  else
  {
    // here we animate the exploded defender (not draw just update sprite)
    io_defender->frame++;
    if(io_defender->frame%5==0) {
      (io_defender->sprite == 1) ? (io_defender->sprite=2) : (io_defender->sprite=1);
    }
  }
}
