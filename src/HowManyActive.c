///
///  @file HowManyActive.c
///  @brief returns int of how many invaders active

#include "include/HowManyActive.h"

int howManyActive(Invader invaders[ROWS][COLS])
{
  int numberactive=0;
  for(int r=0; r<ROWS; ++r)
  {
    for(int c=0; c<COLS; ++c)
    {
      if(invaders[r][c].active) {numberactive++;}
    }
  }
  return numberactive;
}
