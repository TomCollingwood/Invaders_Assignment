#include "blastBarrier.h"

void blastBarrier(int barriers[4][BARRIERHEIGHT][BARRIERWIDTH],int barrier, int x, int y, int type)
{
  if(x>BARRIERWIDTH-4) printf("YO MOMMA");
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
  if(type==0)
  {
    int displacementx=0;
    int displacementy=0;
    int toprightx=x-3;
    int toprighty=y-3;
    if(toprightx<0)
    {
      displacementx=abs(toprightx);
      toprightx=0;
    }
    if(toprighty<0)
    {
      displacementy=abs(toprighty);
      toprighty=0;
    }
    for(int j=displacementy; j<7; j++)
    {
      if((toprighty+j)<BARRIERHEIGHT)
      {
        for(int i=displacementx; i<6; i++)
        {
          if((toprightx+i)<BARRIERWIDTH)
          {
            if(barriers[barrier][toprighty-displacementy+j][toprightx-displacementx+i] \
               &&invaderBlast[j][i])
            {
              barriers[barrier][toprighty-displacementy+j][toprightx-displacementx+i]=0;
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
    int toprightx=x-4;
    int toprighty=y-4;
    if(toprightx<0)
    {
      displacementx=abs(toprightx);
      toprightx=0;
    }
    if(toprighty<0)
    {
      displacementy=abs(toprighty);
      toprighty=0;
    }
    for(int j=displacementy; j<8; j++)
    {
      if((toprighty+j)<BARRIERHEIGHT)
      {
        for(int i=displacementx; i<8; i++)
        {
          if((toprightx+i)<BARRIERWIDTH)
          {
            if(barriers[barrier][toprighty-displacementy+j][toprightx-displacementx+i] \
               &&defenderBlast[j][i])
            {
              barriers[barrier][toprighty-displacementy+j][toprightx-displacementx+i]=0;
            }
          }
        }
      }
    }
  }
}
