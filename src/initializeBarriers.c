#include "initializeBarriers.h"

void initializeBarriers(int barriers[4][BARRIERHEIGHT][BARRIERWIDTH])
{
  for(int i=0; i<4; i++)
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
    for(int j =0; j<BARRIERHEIGHT;j++)
    {
      for(int k =0; k<BARRIERWIDTH; k++)
      {
        barriers[i][j][k]=barrier[j][k];
      }
    }
  }
}