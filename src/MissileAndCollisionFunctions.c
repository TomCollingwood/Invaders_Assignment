///
///  @file MissileAndCollisionFunctions.c
///  @brief all the functions that operate directly with the missiles

#include "include/MissileAndCollisionFunctions.h"

//----------------------------------------------------------------------------------------------------------------------
void drawMissiles(SDL_Renderer *_ren, SDL_Texture *_tex, Missile _missiles[])
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


  SDL_SetRenderDrawColor(_ren, 255, 255, 255, 255);

  for(int m=0; m<MISSILESNUMBER; ++m)
  {
    if(_missiles[m].active)
    {
      if(_missiles[m].type == DEFENDER)
      {
        SDL_SetRenderDrawColor(_ren, 0, 255, 0, 255);
        SDL_RenderFillRect(_ren,&_missiles[m].pos);
      }

      else if(_missiles[m].type == ZIGZAG)
      {
        if(_missiles[m].sprite==0)
        {
          SDL_RenderCopy(_ren, _tex,&SrcZIGZAGS0,&_missiles[m].pos);
        }
        else if(_missiles[m].sprite==1)
        {
          SDL_RenderCopy(_ren, _tex,&SrcZIGZAGS1,&_missiles[m].pos);
        }
        else if(_missiles[m].sprite==2)
        {
          SDL_RenderCopy(_ren, _tex,&SrcZIGZAGS2,&_missiles[m].pos);
        }
        else
        {
          SDL_RenderCopy(_ren, _tex,&SrcZIGZAGS3,&_missiles[m].pos);
        }
      }

      else if(_missiles[m].type == LETTERT)
      {
        if(_missiles[m].sprite==0)
        {
          SDL_RenderCopy(_ren, _tex,&SrcLETTERTS0,&_missiles[m].pos);
        }
        else if(_missiles[m].sprite==1)
        {
          SDL_RenderCopy(_ren, _tex,&SrcLETTERTS1,&_missiles[m].pos);
        }
        else if(_missiles[m].sprite==2)
        {
          SDL_RenderCopy(_ren, _tex,&SrcLETTERTS2,&_missiles[m].pos);
        }
        else
        {
          SDL_RenderCopy(_ren, _tex,&SrcLETTERTS3,&_missiles[m].pos);
        }
      }

      else
      {
        if(_missiles[m].sprite==0)
        {
          SDL_RenderCopy(_ren, _tex,&SrcSNAKES0,&_missiles[m].pos);
        }
        else if(_missiles[m].sprite==1)
        {
          SDL_RenderCopy(_ren, _tex,&SrcSNAKES1,&_missiles[m].pos);
        }
        else if(_missiles[m].sprite==2)
        {
          SDL_RenderCopy(_ren, _tex,&SrcSNAKES2,&_missiles[m].pos);
        }
        else
        {
          SDL_RenderCopy(_ren, _tex,&SrcSNAKES3,&_missiles[m].pos);
        }
      }
    }
  }
}

//----------------------------------------------------------------------------------------------------------------------
void updateCollisions(Missile io_missiles[], Invader io_invaders[ROWS][COLS], Defender *io_defender, \
                      int *o_freeze, int *o_score, int _frame)
{
  for(int m=0; m<MISSILESNUMBER; ++m)
  {
    if(io_missiles[m].type == DEFENDER && io_missiles[m].active)
    {
      int hit = 0;
      for(int r=0; r<ROWS; ++r)
      {
        for(int c=0; c<COLS; ++c)
        {
          if(io_invaders[r][c].active)
          {
            int misX = io_missiles[m].pos.x;
            int invX = io_invaders[r][c].pos.x;
            int invW = io_invaders[r][c].pos.w;
            int misY = io_missiles[m].pos.y;
            int invY = io_invaders[r][c].pos.y;
            int misH = io_missiles[m].pos.h;

            // we check the hit variable below as this makes sure only one invader is
            // destroyed per missile
            if ((misX > invX) && (misX < invX+invW) && (misY-misH < invY) && hit ==0)
            {
              // add to score here
              if(io_invaders[r][c].type==TYPE1)
              {
                (_frame<3000) ? (*o_score)+=((-0.1)*_frame+400) : (*o_score+=100);
              }
              else if(io_invaders[r][c].type==TYPE2)
              {
                (_frame<3000) ? (*o_score)+=((-0.05)*_frame+200) : (*o_score+=50);
              }
              else
              {
                (_frame<3000) ? (*o_score)+=((-0.025)*_frame+100) : (*o_score+=25);
              }

              io_invaders[r][c].type = EXPLOSION;
              (*o_freeze) = 1;
              io_missiles[m].active = 0;
              hit = 1;

              // sound effect - be sure to "Run in terminal" to hear it
              printf("\a");
              fflush(stdout);

              // below updates the bottom variable for the invader
              // above the one destroyed
              if(r!=0)
              {
                for(int i=r-1; i>=0; --i)
                {
                  if(io_invaders[i][c].active)
                  {
                    io_invaders[i][c].bottom=1;
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
    else if (io_missiles[m].active)
    {
      int misX = io_missiles[m].pos.x;
      int misY = io_missiles[m].pos.y;
      int defX = io_defender->pos.x;
      int defY = io_defender->pos.y;
      int defW = io_defender->pos.w;
      int defH = io_defender->pos.h;

      if ((misX > defX) && (misX < defX+defW) && (misY < defY +defH) && (misY > defY) && io_defender->active)
      {
        io_defender->sprite = 1;
        io_defender->active=0;
        // exploded sprite is slightly wider than normal sprite
        io_defender->pos.w=EXPLODEDDEFENDERWIDTH;
        io_missiles[m].active = 0;

      }
    }
  }
}

//----------------------------------------------------------------------------------------------------------------------
void updateMissiles(Missile io_missiles[])
{
  for(int m=0; m<MISSILESNUMBER; ++m)
  {
    if((io_missiles[m].pos.y < 0 || io_missiles[m].pos.y >HEIGHT) && io_missiles[m].active)
    {
      io_missiles[m].active = 0;
    }
    if(io_missiles[m].active)
    {
      io_missiles[m].frame++;
      if(io_missiles[m].dir == UP)
      {
        io_missiles[m].pos.y += -15;
      }
      else if (io_missiles[m].dir == DOWN)
      {
        io_missiles[m].pos.y += 5;
      }

      // animate sprites
      if(io_missiles[m].frame%3==0)
      {
        if(io_missiles[m].sprite==3)
        {
          io_missiles[m].sprite=0;
        }
        else{
          io_missiles[m].sprite++;
        }
      }
    }
  }
}

