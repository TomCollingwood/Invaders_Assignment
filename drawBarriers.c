#include "drawBarriers.h"

void drawBarriers(SDL_Renderer *ren, int barriers[4][BARRIERHEIGHT][BARRIERWIDTH]){
  SDL_SetRenderDrawColor(ren, 72, 252, 0, 255);
  for(int i=0;i<4;i++){
    int initialX=100+3*BARRIERWIDTH*i+60*i;
    int initialY=550;
    int x = initialX;
    int y = initialY;
    for(int h=0;h<BARRIERHEIGHT;h++){
      for(int w=0;w<BARRIERWIDTH;w++){
        if(barriers[i][h][w]){
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
