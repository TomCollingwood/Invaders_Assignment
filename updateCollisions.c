#include "updateCollisions.h"

void updateCollisions(Missile missiles[], Invader invaders[ROWS][COLS], Defender *defender, \
                      int *freeze, int *score, int frame)
{
  int freezelag = *freeze;
  for(int m=0; m<MISSILESNUMBER; m++)
  {
    if(missiles[m].type == DEFENDER && missiles[m].active)
    {
      int hit = 0;
      for(int r=0; r<ROWS; r++)
      {
        for(int c=0; c<COLS; c++)
        {
          if(invaders[r][c].active)
          {
            int misX = missiles[m].pos.x;
            int invX = invaders[r][c].pos.x;
            int invW = invaders[r][c].pos.w;
            int misY = missiles[m].pos.y;
            int invY = invaders[r][c].pos.y;
            int misH = missiles[m].pos.h;
            if ((misX > invX) && (misX < invX+invW) && (misY-misH < invY) && hit ==0)
            {
              // add to score here
              if(invaders[r][c].type==TYPE1){
                (frame<3000) ? (*score)+=((-0.1)*frame+400) : (*score+=100);
              }
              else if(invaders[r][c].type==TYPE2){
                (frame<3000) ? (*score)+=((-0.05)*frame+200) : (*score+=50);
              }
              else{
                (frame<3000) ? (*score)+=((-0.025)*frame+100) : (*score+=25);
              }

              invaders[r][c].type = EXPLOSION;
              freezelag = 1;
              missiles[m].active = 0;
              hit = 1;
              if(r!=0)
                for(int i=r-1;i>=0;i--){
                  if(invaders[i][c].active){
                    invaders[i][c].bottom=1;
                    break;
                  }
                }

            }
          }
        }
      }
    }
    else if (missiles[m].active){
      int misX = missiles[m].pos.x;
      int misY = missiles[m].pos.y;
      int defX = defender->pos.x;
      int defY = defender->pos.y;
      int defW = defender->pos.w;
      int defH = defender->pos.h;

      if ((misX > defX) && (misX < defX+defW) && (misY < defY +defH) && (misY > defY) && defender->active)
      {
        defender->sprite = 1;
        defender->active=0;
        missiles[m].active = 0;
      }
    }
  }
  *freeze=freezelag;
}
