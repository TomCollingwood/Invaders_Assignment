#include "include/InitializeInvaders.h"

// Initializes all invader positions
void initializeInvaders(Invader invaders[ROWS][COLS])
{
  SDL_Rect pos;
  pos.w=SPRITEWIDTH;
  pos.h=SPRITEHEIGHT;
  int ypos=130;
  int frameoffset = COLS*ROWS*3;

  for(int r=0; r<ROWS; ++r)
  {
    int xpos = GAP;
    // if(r == 0) xpos = GAP+3;
    frameoffset = (r)*11;
    for(int c=0; c<COLS; ++c)
    {
      pos.x=xpos+SPRITEWIDTH;
      pos.y=ypos+SPRITEHEIGHT;
      xpos+=(GAP+SPRITEWIDTH);
      invaders[r][c].pos=pos;
      invaders[r][c].active=1;
      invaders[r][c].frame=0;
      invaders[r][c].frame=frameoffset;
      frameoffset+=1;
      invaders[r][c].explosionframe=0;
      invaders[r][c].sprite=0;
      invaders[r][c].direction=FWD;
      if(r==0)
      {
        invaders[r][c].type=TYPE1;
      }
      else if(r==1 || r==2)
      {
        invaders[r][c].type=TYPE2;
      }
      else
      {
        invaders[r][c].type=TYPE3;
      }

      if(r!=4)
      {
        invaders[r][c].bottom=0;
      }
      else
      {
        invaders[r][c].bottom=1;
      }
    }
    ypos+=(GAP+SPRITEHEIGHT);
  }
}
