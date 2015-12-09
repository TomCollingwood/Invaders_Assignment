#include "updateMissiles.h"
// Updates missile position depending on direction and activity
void updateMissiles(Missile missiles[])
{
  for(int m=0; m<MISSILESNUMBER; m++)
  {
    if((missiles[m].pos.y < 0 || missiles[m].pos.y >HEIGHT) && missiles[m].active)
    {
      missiles[m].active = 0;
    }
    if(missiles[m].active)
    {
      missiles[m].frame++;
      if(missiles[m].dir == UP)
      {
        missiles[m].pos.y += -15;
      }
      else if (missiles[m].dir == DOWN)
      {
        missiles[m].pos.y += 5;
      }
      if(missiles[m].frame%3==0){
        if(missiles[m].sprite==3){
          missiles[m].sprite=0;
        }
        else{
          missiles[m].sprite++;
        }
      }
    }
  }
}

