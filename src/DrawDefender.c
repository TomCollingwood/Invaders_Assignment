#include "include/DrawDefender.h"
// Draws the defender texture onto the defender
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
    defender->pos.w=EXPLODEDDEFENDERWIDTH;
    if(defender->sprite==1)
    {
      SDL_RenderCopy(ren,tex,&SrcRS1,&defender->pos);
    }
    else {
      SDL_RenderCopy(ren,tex,&SrcRS2,&defender->pos);
    }
  }
}

