#include "include/UpdateBarriers.h"
#include "BlastBarrier.c"

void updateBarriers(int barriers[4][BARRIERHEIGHT][BARRIERWIDTH], Missile missiles[MISSILESNUMBER])
{
  for(int i=0; i<4; ++i)
  {
    int initialX=BARRIERSTARTX+3*BARRIERWIDTH*i+BARRIERGAP*i;
    int initialY=550;
    int x = initialX;
    int y = initialY;
    for(int h=0;h<BARRIERHEIGHT;h++)
    {
      for(int w=0;w<BARRIERWIDTH;w++)
      {
        for(int m=0; m<MISSILESNUMBER; m++)
        {
          if(missiles[m].active)
          {
            if(missiles[m].dir==DOWN)
            {
              if(missiles[m].pos.x+3>=x && missiles[m].pos.x<x+3 && \
                 missiles[m].pos.y>y && barriers[i][h][w])
              {
                missiles[m].active=0;
                blastBarrier(barriers,i,w,h,0);
              }
            }
            else
            {
              if(missiles[m].pos.x+3>=x && missiles[m].pos.x<x+3 && \
                 missiles[m].pos.y-14<y && barriers[i][h][w])
              {
                missiles[m].active=0;
                blastBarrier(barriers,i,w,h,1);
              }
            }
          }
        }
        x+=3;
      }
      x=initialX;
      y+=3;
    }
  }
}

