///
///  @file BlastBarrier.c
///  @brief updates a barriers to have a crater spreading outwards from (x,y)

#include "include/BlastBarrier.h"

void blastBarrier(int barriers[4][BARRIERHEIGHT][BARRIERWIDTH],int barrier, int x, int y, int type)
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
  if(type==0)
  {
    int displacementx=0;
    int displacementy=0;

    // as x and y are in center of blast
    // we must find the top-left x and y to draw blast
    int topleftx=x-3;
    int toplefty=y-3;

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
      // two if statements below make sure we don't go outside of array
      if((toplefty+j)<BARRIERHEIGHT)
      {
        for(int i=displacementx; i<6; i++)
        {
          if((topleftx+i)<BARRIERWIDTH)
          {
            // if both pixels for barrier and blast are set then
            // make barrier pixel 0
            if(barriers[barrier][toplefty-displacementy+j][topleftx-displacementx+i] \
               &&invaderBlast[j][i])
            {
              barriers[barrier][toplefty-displacementy+j][topleftx-displacementx+i]=0;
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
    int topleftx=x-4;
    int toplefty=y-4;
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
            if(barriers[barrier][toplefty-displacementy+j][topleftx-displacementx+i] \
               &&defenderBlast[j][i])
            {
              barriers[barrier][toplefty-displacementy+j][topleftx-displacementx+i]=0;
            }
          }
        }
      }
    }
  }
}
