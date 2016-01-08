///
///  @file InvaderFunctions.c
///  @brief

#include "include/InvaderFunctions.h"

void drawInvaders(SDL_Renderer *ren, SDL_Texture *tex, Invader invaders[ROWS][COLS])
{
  SDL_Rect SrcExplode;
  SrcExplode.x=0;
  SrcExplode.y=24;
  SrcExplode.w=39;
  SrcExplode.h=24;

  // I've made SpriteSheet.bmp image size same as render size
  SDL_Rect SrcTYPE1S0;
  SrcTYPE1S0.x=111;
  SrcTYPE1S0.y=0;
  SrcTYPE1S0.w=SPRITEWIDTH;
  SrcTYPE1S0.h=SPRITEHEIGHT;

  SDL_Rect SrcTYPE1S1;
  SrcTYPE1S1.x=147;
  SrcTYPE1S1.y=0;
  SrcTYPE1S1.w=SPRITEWIDTH;
  SrcTYPE1S1.h=SPRITEHEIGHT;

  SDL_Rect SrcTYPE2S0;
  SrcTYPE2S0.x=39;
  SrcTYPE2S0.y=0;
  SrcTYPE2S0.w=SPRITEWIDTH;
  SrcTYPE2S0.h=SPRITEHEIGHT;

  SDL_Rect SrcTYPE2S1;
  SrcTYPE2S1.x=75;
  SrcTYPE2S1.y=0;
  SrcTYPE2S1.w=SPRITEWIDTH;
  SrcTYPE2S1.h=SPRITEHEIGHT;

  SDL_Rect SrcTYPE3S0;
  SrcTYPE3S0.x=39;
  SrcTYPE3S0.y=24;
  SrcTYPE3S0.w=SPRITEWIDTH;
  SrcTYPE3S0.h=SPRITEHEIGHT;

  SDL_Rect SrcTYPE3S1;
  SrcTYPE3S1.x=75;
  SrcTYPE3S1.y=24;
  SrcTYPE3S1.w=SPRITEWIDTH;
  SrcTYPE3S1.h=SPRITEHEIGHT;

  for(int r=0; r<ROWS; ++r)
  {
    for(int c=0; c<COLS; ++c)
    {
      if(invaders[r][c].active == 1){
        switch(invaders[r][c].type)
        {
        case TYPE1 :
          if(invaders[r][c].sprite == 0)
          {
            SDL_RenderCopy(ren, tex,&SrcTYPE1S0,&invaders[r][c].pos);
          }
          else {SDL_RenderCopy(ren, tex,&SrcTYPE1S1,&invaders[r][c].pos);}
          break;
        case TYPE2 :
          if(invaders[r][c].sprite == 0)
          {
            SDL_RenderCopy(ren, tex,&SrcTYPE2S0,&invaders[r][c].pos);
          }
          else {SDL_RenderCopy(ren, tex,&SrcTYPE2S1,&invaders[r][c].pos);}
          break;
        case TYPE3 :
          if(invaders[r][c].sprite == 0)
          {
            SDL_RenderCopy(ren, tex,&SrcTYPE3S0,&invaders[r][c].pos);
          }
          else {SDL_RenderCopy(ren, tex,&SrcTYPE3S1,&invaders[r][c].pos);}
          break;
        case EXPLOSION :
          SDL_RenderCopy(ren, tex,&SrcExplode,&invaders[r][c].pos);
        }
      }
    }
  }
}

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

void initializeInvaders(Invader invaders[ROWS][COLS])
{
  SDL_Rect pos;
  pos.w=SPRITEWIDTH;
  pos.h=SPRITEHEIGHT;
  int ypos=130;
  int frameoffset = COLS*ROWS*3;

  for(int r=0; r<ROWS; ++r)
  {
    int xpos = GAP;
    frameoffset = (r)*11;
    for(int c=0; c<COLS; ++c)
    {
      pos.x=xpos+SPRITEWIDTH;
      pos.y=ypos+SPRITEHEIGHT;
      xpos+=(GAP+SPRITEWIDTH);
      invaders[r][c].pos=pos;
      invaders[r][c].active=1;
      invaders[r][c].frame=0;
      invaders[r][c].frame=frameoffset;
      frameoffset+=1;
      invaders[r][c].explosionframe=0;
      invaders[r][c].sprite=0;
      invaders[r][c].direction=FWD;
      if(r==0)
      {
        invaders[r][c].type=TYPE1;
      }
      else if(r==1 || r==2)
      {
        invaders[r][c].type=TYPE2;
      }
      else
      {
        invaders[r][c].type=TYPE3;
      }

      if(r!=4)
      {
        invaders[r][c].bottom=0;
      }
      else
      {
        invaders[r][c].bottom=1;
      }
    }
    ypos+=(GAP+SPRITEHEIGHT);
  }
}

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

