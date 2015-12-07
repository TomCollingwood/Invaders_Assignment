#include "updateBarriers.h"

void updateBarriers(int barriers[4][BARRIERHEIGHT][BARRIERWIDTH], Missile missiles[MISSILESNUMBER]){
  for(int i=0;i<4;i++){
    int initialX=BARRIERSTARTX+3*BARRIERWIDTH*i+BARRIERGAP*i;
    int initialY=550;
    int x = initialX;
    int y = initialY;
    for(int h=0;h<BARRIERHEIGHT;h++){
      for(int w=0;w<BARRIERWIDTH;w++){
        for(int m=0; m<MISSILESNUMBER; m++){
          if(missiles[m].active && missiles[m].dir==DOWN){
            if(missiles[m].pos.x>x && missiles[m].pos.x<x+3 && missiles[m].pos.y>y){
              missiles[m].active=0;
              barriers[i][h][w]=0;
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

