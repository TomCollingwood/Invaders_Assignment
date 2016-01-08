///
///  @file UpdateInvaders.c
///  @brief updates invaders' position and sprite

#include "include/InvaderFunctions.h"

void updateInvaders(Invader invaders[ROWS][COLS], Missile missiles[MISSILESNUMBER], \
                    int *freeze, int *howfast, int startscreen)
{
  int freezelagfix = *freeze;

  // find leftmost & rightmost column with at least one active invader
  int lcol = 0;
  int rcol = COLS-1;
  for(int c=0; c<COLS; ++c)
  {
    int counter = 0;
    for(int r=0; r<ROWS; ++r)
    {
      if(invaders[r][c].active) {counter++;}
    }
    if (counter==0 && lcol==c)
    {
      lcol=c+1;
    }
  }

  for(int c=COLS-1; c>-1; --c)
  {
    int counter = 0;
    for(int r=0; r<ROWS; ++r)
    {
      if(invaders[r][c].active) counter++;
    }
    if (counter==0 && rcol==c)
    {
      rcol=c-1;
    }
  }

  // to find the first space invader that moves
  int hasfirstbeenfound=0;
  int firstr = 0;
  int firstc = 0;
  for(int r=0; r<ROWS; ++r)
  {
    for(int c=0; c<COLS; ++c)
    {
      if(hasfirstbeenfound==0 && invaders[r][c].active)
      {
        firstr = r;
        firstc = c;
        hasfirstbeenfound=1;
      }
      if(hasfirstbeenfound) {break;}
    }
    if(hasfirstbeenfound) {break;}
  }

  // cycleover==1 when all invaders are alligned in a rectangle
  int cycleover = 0;
  // this comparison is made as invaders[firstr][firstc] is first to move
  if(invaders[firstr][firstc].frame%*howfast==0)
  {
    cycleover = 1;
  }

  // Because I want to make the invaders move as in the original
  // game I have come up with the method below

  // howfast is how many frames it takes a cycle
  // a cycle is from one frame when all invaders are alligned
  // to the next when it's all alligned

  // we need howfast to be the number of frames between the first invader
  // to move to the last invader to move

  // howfast is the number of invaders active as we update the position of
  // one invader per frame

  // we want the invaders to go quicker, the fewer there are

  // we cannot update howfast in the middle of a cycle, this would make
  // the movement of invaders to be out of sync - or march so to speak

  // so we decrease howfast to how many invaders there are when
  // cycleover==1

  // here we redistribute the frames and update howfast
  if(cycleover && *freeze==0 && !startscreen)
  {
    int howmanyactive = howManyActive(invaders);
    *howfast = howmanyactive;
    howmanyactive--;
    for(int r=ROWS-1; r>=0; --r)
    {
      for(int c=COLS-1; c>=0; --c)
      {
        if(invaders[r][c].active)
        {
          invaders[r][c].frame=howmanyactive;
          howmanyactive--;
        }
      }
    }
  }

  // the last to reach the boundary is always the highest on lefmost column
  // (lcol) and rightmost column (rcol)
  static int toprightr=0;
  static int topleftr=0;

  if(cycleover==1)
  {
    for(int i=0; i<ROWS; ++i)
    {
      if(invaders[i][rcol].active)
      {
        toprightr=i;
        break;
      }
    }
    for(int i=0; i<ROWS; ++i)
    {
      if(invaders[i][lcol].active)
      {
        topleftr=i;
        break;
      }
    }
  }

  // so here we check to see if the last to reach the boundary has reached it
  int moveleft=0;
  int moveright=0;
  if(cycleover)
  {
    if(invaders[topleftr][lcol].pos.x <= SPRITEWIDTH) moveright=1;
    if(invaders[toprightr][rcol].pos.x >= WIDTH-(2*SPRITEWIDTH)) moveleft=1;
  }

  // changes direction when all rows of leftmost/rightmost are outside
  // respective boundaries when all invaders are alligned (cycleover=1)
  if(moveleft && cycleover)
    {
    for(int r=0; r<ROWS; ++r)
    {
      for(int c=0; c<COLS; ++c)
      {
          if(invaders[r][c].direction==FWD && !startscreen)
          {
            // I used DWNBWD to save the info that it will then go BWD after
            // moving downwards
            invaders[r][c].direction=DWNBWD;
          }
          else
          {
            // this else clause happens when direction==BWD
            // the direction BWD is assigned further below in code
            // this stops invaders moving downwards indefinately
            invaders[r][c].direction=BWD;
          }
      }
    }
  }
  // below is same for DWNFWD
  else if(moveright && cycleover)
  {
    for(int r=0; r<ROWS; ++r)
    {
      for(int c=0; c<COLS; ++c)
      {
          if(invaders[r][c].direction==BWD && !startscreen)
          {
            invaders[r][c].direction=DWNFWD;
          }
          else
          {
            invaders[r][c].direction=FWD;
          }
      }
    }
  }

  // for each invader
  for(int r=0; r<ROWS; ++r)
  {
    for(int c=0; c<COLS; ++c)
    {
      // below if statement stops invaders from moving when invader explodes
      if(*freeze==0)
      {
        invaders[r][c].frame++;
      }
      // the explosion frame measures how long the explosion has been active
      if(invaders[r][c].type == EXPLOSION)
      {
        invaders[r][c].explosionframe++;
      }
      // we limit the explosion to 3 frames below
      if(invaders[r][c].type == EXPLOSION && invaders[r][c].explosionframe > 3 && invaders[r][c].active)
      {
        invaders[r][c].active = 0;
        // If I update freeze directly in middle of iterating through invaders
        // the rest of the invaders will be ofset from the others so I use freezelag
        // I assign freeze to freezelagfix at bottom of updateinvaders function
        freezelagfix = 0;
      }

      if(invaders[r][c].frame%*howfast==0 && *freeze==0 && invaders[r][c].active)
      {
        // moves the invader depending on direction
        if(invaders[r][c].direction==FWD)
        {
          invaders[r][c].pos.x+=10;
        }
        else if(invaders[r][c].direction==BWD)
        {
          invaders[r][c].pos.x-=10;
        }
        else if(invaders[r][c].direction==DWNBWD)
        {
          invaders[r][c].pos.y+=20;
          invaders[r][c].direction=BWD;
        }
        else if(invaders[r][c].direction==DWNFWD)
        {
          invaders[r][c].pos.y+=20;
          invaders[r][c].direction=FWD;
        }

        if(invaders[r][c].sprite==0){
          invaders[r][c].sprite=1;
        }
        else{
          invaders[r][c].sprite=0;
        }
        // fires missile
        if(invaders[r][c].bottom)
        {
          int random = rand();
          // if startscreen then the missiles must not fire in front of the text
          if((!startscreen && random%2==0) || (random%2==0 && startscreen && (invaders[r][c].pos.x>410 || \
                                               invaders[r][c].pos.x<(WIDTH/2)-115))){
            for(int m=1; m<MISSILESNUMBER; ++m)
            {
              if(missiles[m].active==0){
                Missile newinvadermissile;
                newinvadermissile.pos.x = invaders[r][c].pos.x;
                newinvadermissile.pos.y = invaders[r][c].pos.y;
                newinvadermissile.pos.w = 9;
                newinvadermissile.pos.h = 24;
                newinvadermissile.dir = DOWN;
                newinvadermissile.sprite=0;
                if(random%100>66)
                {
                  newinvadermissile.type = LETTERT;
                }
                else if(random%100>33)
                {
                  newinvadermissile.type = SNAKE;
                }
                else
                {
                  newinvadermissile.type = ZIGZAG;
                }
                newinvadermissile.frame=0;
                newinvadermissile.active=1;
                missiles[m]=newinvadermissile;
                break;
              }
            }
          }
        }
      }
    }
  }
  *freeze = freezelagfix;
}
