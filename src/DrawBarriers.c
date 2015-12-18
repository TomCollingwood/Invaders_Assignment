///
///  @file DrawBarriers.c
///  @brief draws the four barriers from an 3d int array

#include "include/DrawBarriers.h"

void drawBarriers(SDL_Renderer *ren, int barriers[4][BARRIERHEIGHT][BARRIERWIDTH]){
  SDL_SetRenderDrawColor(ren, 0, 255, 0, 255);
  for(int i=0; i<4; ++i)
  {
    int initialX=BARRIERSTARTX+3*BARRIERWIDTH*i+BARRIERGAP*i;
    int initialY=BARRIERSTARTY;
    int x = initialX;
    int y = initialY;
    for(int h=0; h<BARRIERHEIGHT; ++h)
    {
      for(int w=0; w<BARRIERWIDTH; ++w)
      {
        if(barriers[i][h][w])
        {
          // each 'pixel' in barrier array is actually 3x3 pixels
          SDL_Rect pixel = {x,y,3,3};
          SDL_RenderFillRect(ren,&pixel);
        }
        x+=3;
      }
      x=initialX;
      y+=3;
    }
  }
}
