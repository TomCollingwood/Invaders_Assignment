///
///  @file MissileAndCollisionFunctions.c
///  @brief

#include "include/MissileAndCollisionFunctions.h"

void drawMissiles(SDL_Renderer *ren, SDL_Texture *tex, Missile missiles[])
{
  SDL_Rect SrcZIGZAGS0;
  SrcZIGZAGS0.x=0;
  SrcZIGZAGS0.y=54;
  SrcZIGZAGS0.w=9;
  SrcZIGZAGS0.h=24;

  SDL_Rect SrcZIGZAGS1;
  SrcZIGZAGS1.x=12;
  SrcZIGZAGS1.y=54;
  SrcZIGZAGS1.w=9;
  SrcZIGZAGS1.h=24;

  SDL_Rect SrcZIGZAGS2;
  SrcZIGZAGS2.x=24;
  SrcZIGZAGS2.y=54;
  SrcZIGZAGS2.w=9;
  SrcZIGZAGS2.h=24;

  SDL_Rect SrcZIGZAGS3;
  SrcZIGZAGS3.x=36;
  SrcZIGZAGS3.y=54;
  SrcZIGZAGS3.w=9;
  SrcZIGZAGS3.h=24;

  SDL_Rect SrcLETTERTS0;
  SrcLETTERTS0.x=48;
  SrcLETTERTS0.y=54;
  SrcLETTERTS0.w=9;
  SrcLETTERTS0.h=24;

  SDL_Rect SrcLETTERTS1;
  SrcLETTERTS1.x=60;
  SrcLETTERTS1.y=54;
  SrcLETTERTS1.w=9;
  SrcLETTERTS1.h=24;

  SDL_Rect SrcLETTERTS2;
  SrcLETTERTS2.x=72;
  SrcLETTERTS2.y=54;
  SrcLETTERTS2.w=9;
  SrcLETTERTS2.h=24;

  SDL_Rect SrcLETTERTS3;
  SrcLETTERTS3.x=84;
  SrcLETTERTS3.y=54;
  SrcLETTERTS3.w=9;
  SrcLETTERTS3.h=24;

  SDL_Rect SrcSNAKES0;
  SrcSNAKES0.x=96;
  SrcSNAKES0.y=54;
  SrcSNAKES0.w=9;
  SrcSNAKES0.h=24;

  SDL_Rect SrcSNAKES1;
  SrcSNAKES1.x=108;
  SrcSNAKES1.y=54;
  SrcSNAKES1.w=9;
  SrcSNAKES1.h=24;

  SDL_Rect SrcSNAKES2;
  SrcSNAKES2.x=120;
  SrcSNAKES2.y=54;
  SrcSNAKES2.w=9;
  SrcSNAKES2.h=24;

  SDL_Rect SrcSNAKES3;
  SrcSNAKES3.x=132;
  SrcSNAKES3.y=54;
  SrcSNAKES3.w=9;
  SrcSNAKES3.h=24;


  SDL_SetRenderDrawColor(ren, 255, 255, 255, 255);

  for(int m=0; m<MISSILESNUMBER; ++m)
  {
    if(missiles[m].active)
    {
      if(missiles[m].type == DEFENDER)
      {
        SDL_SetRenderDrawColor(ren, 0, 255, 0, 255);
        SDL_RenderFillRect(ren,&missiles[m].pos);
      }

      else if(missiles[m].type == ZIGZAG)
      {
        if(missiles[m].sprite==0)
        {
          SDL_RenderCopy(ren, tex,&SrcZIGZAGS0,&missiles[m].pos);
        }
        else if(missiles[m].sprite==1)
        {
          SDL_RenderCopy(ren, tex,&SrcZIGZAGS1,&missiles[m].pos);
        }
        else if(missiles[m].sprite==2)
        {
          SDL_RenderCopy(ren, tex,&SrcZIGZAGS2,&missiles[m].pos);
        }
        else
        {
          SDL_RenderCopy(ren, tex,&SrcZIGZAGS3,&missiles[m].pos);
        }
      }

      else if(missiles[m].type == LETTERT)
      {
        if(missiles[m].sprite==0)
        {
          SDL_RenderCopy(ren, tex,&SrcLETTERTS0,&missiles[m].pos);
        }
        else if(missiles[m].sprite==1)
        {
          SDL_RenderCopy(ren, tex,&SrcLETTERTS1,&missiles[m].pos);
        }
        else if(missiles[m].sprite==2)
        {
          SDL_RenderCopy(ren, tex,&SrcLETTERTS2,&missiles[m].pos);
        }
        else
        {
          SDL_RenderCopy(ren, tex,&SrcLETTERTS3,&missiles[m].pos);
        }
      }

      else
      {
        if(missiles[m].sprite==0)
        {
          SDL_RenderCopy(ren, tex,&SrcSNAKES0,&missiles[m].pos);
        }
        else if(missiles[m].sprite==1)
        {
          SDL_RenderCopy(ren, tex,&SrcSNAKES1,&missiles[m].pos);
        }
        else if(missiles[m].sprite==2)
        {
          SDL_RenderCopy(ren, tex,&SrcSNAKES2,&missiles[m].pos);
        }
        else
        {
          SDL_RenderCopy(ren, tex,&SrcSNAKES3,&missiles[m].pos);
        }
      }
    }
  }
}

void updateCollisions(Missile missiles[], Invader invaders[ROWS][COLS], Defender *defender, \
                      int *freeze, int *score, int frame)
{
  for(int m=0; m<MISSILESNUMBER; ++m)
  {
    if(missiles[m].type == DEFENDER && missiles[m].active)
    {
      int hit = 0;
      for(int r=0; r<ROWS; ++r)
      {
        for(int c=0; c<COLS; ++c)
        {
          if(invaders[r][c].active)
          {
            int misX = missiles[m].pos.x;
            int invX = invaders[r][c].pos.x;
            int invW = invaders[r][c].pos.w;
            int misY = missiles[m].pos.y;
            int invY = invaders[r][c].pos.y;
            int misH = missiles[m].pos.h;

            // we check the hit variable below as this makes sure only one invader is
            // destroyed per missile
            if ((misX > invX) && (misX < invX+invW) && (misY-misH < invY) && hit ==0)
            {
              // add to score here
              if(invaders[r][c].type==TYPE1)
              {
                (frame<3000) ? (*score)+=((-0.1)*frame+400) : (*score+=100);
              }
              else if(invaders[r][c].type==TYPE2)
              {
                (frame<3000) ? (*score)+=((-0.05)*frame+200) : (*score+=50);
              }
              else
              {
                (frame<3000) ? (*score)+=((-0.025)*frame+100) : (*score+=25);
              }

              invaders[r][c].type = EXPLOSION;
              (*freeze) = 1;
              missiles[m].active = 0;
              hit = 1;

              // below updates the bottom variable for the invader
              // above the one destroyed
              if(r!=0)
              {
                for(int i=r-1; i>=0; --i)
                {
                  if(invaders[i][c].active)
                  {
                    invaders[i][c].bottom=1;
                    break;
                  }
                }
              }
            }
          }
        }
      }
    }
    // else missile's direction is DOWN
    // we check defender collision
    else if (missiles[m].active)
    {
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
        // exploded sprite is slightly wider than normal sprite
        defender->pos.w=EXPLODEDDEFENDERWIDTH;
        missiles[m].active = 0;

      }
    }
  }
}

void updateMissiles(Missile missiles[])
{
  for(int m=0; m<MISSILESNUMBER; ++m)
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

      // animate sprites
      if(missiles[m].frame%3==0)
      {
        if(missiles[m].sprite==3)
        {
          missiles[m].sprite=0;
        }
        else{
          missiles[m].sprite++;
        }
      }
    }
  }
}

