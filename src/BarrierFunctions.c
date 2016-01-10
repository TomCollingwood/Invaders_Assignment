///
///  @file BarrierFunctions.c
///  @brief all the functions that operate directly on the barriers

#include "include/BarrierFunctions.h"

//----------------------------------------------------------------------------------------------------------------------
void blastBarrier(int io_barriers[4][BARRIERHEIGHT][BARRIERWIDTH],int _barrier, int _x, int _y, int _type)
{
  int invaderBlast[7][6] = { \
      {1,0,0,0,1,0},
      {0,0,1,1,0,1},
      {0,1,1,1,1,0},
      {1,0,1,1,1,0},
      {0,1,1,1,1,1},
      {1,0,1,1,1,0},
      {0,1,0,1,0,1}
    };
  int defenderBlast[8][8] = { \
      {1,0,0,0,1,0,0,1},
      {0,0,1,0,0,0,1,0},
      {0,1,1,1,1,1,1,0},
      {1,1,1,1,1,1,1,1},
      {1,1,1,1,1,1,1,1},
      {0,1,1,1,1,1,1,0},
      {0,0,0,0,0,0,0,0},
      {1,0,0,0,0,0,0,1}
    };
  if(_type==0)
  {
    int displacementx=0;
    int displacementy=0;

    // as x and y are in center of blast
    // we must find the top-left x and y to draw blast
    int topleftx=_x-3;
    int toplefty=_y-3;

    // the top-left coorindates may go off-screen (negative)
    // to correct this we set them to zero and offset the blast
    // so it still centers at x,y
    if(topleftx<0)
    {
      displacementx=abs(topleftx);
      topleftx=0;
    }
    if(toplefty<0)
    {
      displacementy=abs(toplefty);
      toplefty=0;
    }

    for(int j=displacementy; j<7; j++)
    {
      // the two if statements below make sure we don't go outside of array
      if((toplefty+j)<BARRIERHEIGHT)
      {
        for(int i=displacementx; i<6; i++)
        {
          if((topleftx+i)<BARRIERWIDTH)
          {
            // if both pixels for barrier and blast are set then
            // make barrier pixel 0
            if(io_barriers[_barrier][toplefty-displacementy+j][topleftx-displacementx+i] \
               &&invaderBlast[j][i])
            {
              io_barriers[_barrier][toplefty-displacementy+j][topleftx-displacementx+i]=0;
            }
          }
        }
      }
    }
  }
  else
  {
    int displacementx=0;
    int displacementy=0;
    int topleftx=_x-4;
    int toplefty=_y-4;
    if(topleftx<0)
    {
      displacementx=abs(topleftx);
      topleftx=0;
    }
    if(toplefty<0)
    {
      displacementy=abs(toplefty);
      toplefty=0;
    }
    for(int j=displacementy; j<8; j++)
    {
      if((toplefty+j)<BARRIERHEIGHT)
      {
        for(int i=displacementx; i<8; i++)
        {
          if((topleftx+i)<BARRIERWIDTH)
          {
            if(io_barriers[_barrier][toplefty-displacementy+j][topleftx-displacementx+i] \
               &&defenderBlast[j][i])
            {
              io_barriers[_barrier][toplefty-displacementy+j][topleftx-displacementx+i]=0;
            }
          }
        }
      }
    }
  }
}

//----------------------------------------------------------------------------------------------------------------------
void drawBarriers(SDL_Renderer *_ren, int _barriers[4][BARRIERHEIGHT][BARRIERWIDTH]){
  SDL_SetRenderDrawColor(_ren, 0, 255, 0, 255);
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
        if(_barriers[i][h][w])
        {
          // each 'pixel' in barrier array is actually 3x3 pixels
          SDL_Rect pixel = {x,y,3,3};
          SDL_RenderFillRect(_ren,&pixel);
        }
        x+=3;
      }
      x=initialX;
      y+=3;
    }
  }
}

//----------------------------------------------------------------------------------------------------------------------
void initializeBarriers(int io_barriers[4][BARRIERHEIGHT][BARRIERWIDTH])
{
  for(int i=0; i<4; ++i)
  {
    int barrier[BARRIERHEIGHT][BARRIERWIDTH]=\
    {
      {0,0,0,0,1,1,1,1,1,1,1,1,1,1,1,1,1,1,0,0,0,0},
      {0,0,0,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,0,0,0},
      {0,0,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,0,0},
      {0,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,0},
      {1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1},
      {1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1},
      {1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1},
      {1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1},
      {1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1},
      {1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1},
      {1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1},
      {1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1},
      {1,1,1,1,1,1,1,0,0,0,0,0,0,0,0,1,1,1,1,1,1,1},
      {1,1,1,1,1,1,0,0,0,0,0,0,0,0,0,0,1,1,1,1,1,1},
      {1,1,1,1,1,0,0,0,0,0,0,0,0,0,0,0,0,1,1,1,1,1},
      {1,1,1,1,1,0,0,0,0,0,0,0,0,0,0,0,0,1,1,1,1,1}
    };
    for(int j=0; j<BARRIERHEIGHT; ++j)
    {
      for(int k=0; k<BARRIERWIDTH; ++k)
      {
        io_barriers[i][j][k]=barrier[j][k];
      }
    }
  }
}

//----------------------------------------------------------------------------------------------------------------------
void updateBarriers(int io_barriers[4][BARRIERHEIGHT][BARRIERWIDTH], Missile io_missiles[MISSILESNUMBER])
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
          if(io_missiles[m].active)
          {
            // if missile direction is DOWN you need to check y values differently
            // from if it was UP
            if(io_missiles[m].dir==DOWN)
            {
              if(io_missiles[m].pos.x+3>=x && io_missiles[m].pos.x<x+3 && \
                 io_missiles[m].pos.y>y && io_barriers[i][h][w])
              {
                io_missiles[m].active=0;
                blastBarrier(io_barriers,i,w,h,0);
              }
            }
            else
            {
              if(io_missiles[m].pos.x+3>=x && io_missiles[m].pos.x<x+3 && \
                 io_missiles[m].pos.y-14<y && io_barriers[i][h][w])
              {
                io_missiles[m].active=0;
                blastBarrier(io_barriers,i,w,h,1);
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

