///
///  @file InvaderFunctions.c
///  @brief all the functions that operate directly on the invaders

#include "include/InvaderFunctions.h"

//----------------------------------------------------------------------------------------------------------------------
void drawInvaders(SDL_Renderer *_ren, SDL_Texture *_tex, Invader io_invaders[ROWS][COLS])
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
      if(io_invaders[r][c].active == 1){
        switch(io_invaders[r][c].type)
        {
        case TYPE1 :
          if(io_invaders[r][c].sprite == 0)
          {
            SDL_RenderCopy(_ren, _tex,&SrcTYPE1S0,&io_invaders[r][c].pos);
          }
          else {SDL_RenderCopy(_ren, _tex,&SrcTYPE1S1,&io_invaders[r][c].pos);}
          break;
        case TYPE2 :
          if(io_invaders[r][c].sprite == 0)
          {
            SDL_RenderCopy(_ren, _tex,&SrcTYPE2S0,&io_invaders[r][c].pos);
          }
          else {SDL_RenderCopy(_ren, _tex,&SrcTYPE2S1,&io_invaders[r][c].pos);}
          break;
        case TYPE3 :
          if(io_invaders[r][c].sprite == 0)
          {
            SDL_RenderCopy(_ren, _tex,&SrcTYPE3S0,&io_invaders[r][c].pos);
          }
          else {SDL_RenderCopy(_ren, _tex,&SrcTYPE3S1,&io_invaders[r][c].pos);}
          break;
        case EXPLOSION :
          SDL_RenderCopy(_ren, _tex,&SrcExplode,&io_invaders[r][c].pos);
        }
      }
    }
  }
}

//----------------------------------------------------------------------------------------------------------------------
int getLowestY(Invader io_invaders[ROWS][COLS])
{
  for(int r=ROWS-1; r>-1; --r){
    for(int c=0; c<COLS; ++c){
     if(io_invaders[r][c].active==1){
       return io_invaders[r][c].pos.y;
     }
    }
  }
  return HEIGHT;
}

//----------------------------------------------------------------------------------------------------------------------
int howManyActive(Invader _invaders[ROWS][COLS])
{
  int numberactive=0;
  for(int r=0; r<ROWS; ++r)
  {
    for(int c=0; c<COLS; ++c)
    {
      if(_invaders[r][c].active) {numberactive++;}
    }
  }
  return numberactive;
}

//----------------------------------------------------------------------------------------------------------------------
void initializeInvaders(Invader o_invaders[ROWS][COLS])
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
      o_invaders[r][c].pos=pos;
      o_invaders[r][c].active=1;
      o_invaders[r][c].frame=0;
      o_invaders[r][c].frame=frameoffset;
      frameoffset+=1;
      o_invaders[r][c].explosionframe=0;
      o_invaders[r][c].sprite=0;
      o_invaders[r][c].direction=FWD;
      if(r==0)
      {
        o_invaders[r][c].type=TYPE1;
      }
      else if(r==1 || r==2)
      {
        o_invaders[r][c].type=TYPE2;
      }
      else
      {
        o_invaders[r][c].type=TYPE3;
      }

      if(r!=4)
      {
        o_invaders[r][c].bottom=0;
      }
      else
      {
        o_invaders[r][c].bottom=1;
      }
    }
    ypos+=(GAP+SPRITEHEIGHT);
  }
}

//----------------------------------------------------------------------------------------------------------------------
void updateInvaders(Invader io_invaders[ROWS][COLS], Missile io_missiles[MISSILESNUMBER], \
                    int *io_freeze, int *io_howfast, int _startscreen)
{
  int freezelagfix = *io_freeze;

  // find leftmost & rightmost column with at least one active invader
  int lcol = 0;
  int rcol = COLS-1;
  for(int c=0; c<COLS; ++c)
  {
    int counter = 0;
    for(int r=0; r<ROWS; ++r)
    {
      if(io_invaders[r][c].active) {counter++;}
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
      if(io_invaders[r][c].active) counter++;
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
      if(hasfirstbeenfound==0 && io_invaders[r][c].active)
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
  // this comparison is made as io_invaders[firstr][firstc] is first to move
  if(io_invaders[firstr][firstc].frame%*io_howfast==0)
  {
    cycleover = 1;
  }

  // Because I want to make the invaders move as in the original
  // game I have come up with the method below

  // io_howfast is how many frames it takes a cycle
  // a cycle is from one frame when all invaders are alligned
  // to the next when it's all alligned

  // the invaders are not always alligned as the invaders take turns
  // to move each frame

  // we need io_howfast to be the number of frames between the first invader
  // to move to the last invader to move

  // io_howfast is the number of invaders active as we update the position of
  // one invader per frame

  // we want the invaders to go quicker, the fewer there are

  // we cannot update io_howfast in the middle of a cycle, this would make
  // the movement of invaders to be out of sync - or march so to speak

  // so we decrease io_howfast to how many invaders active when
  // cycleover==1

  // here we redistribute the frames and update io_howfast
  if(cycleover && *io_freeze==0 && !_startscreen)
  {
    int howmanyactive = howManyActive(io_invaders);
    *io_howfast = howmanyactive;
    howmanyactive--;
    for(int r=ROWS-1; r>=0; --r)
    {
      for(int c=COLS-1; c>=0; --c)
      {
        if(io_invaders[r][c].active)
        {
          io_invaders[r][c].frame=howmanyactive;
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
      if(io_invaders[i][rcol].active)
      {
        toprightr=i;
        break;
      }
    }
    for(int i=0; i<ROWS; ++i)
    {
      if(io_invaders[i][lcol].active)
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
    if(io_invaders[topleftr][lcol].pos.x <= SPRITEWIDTH) moveright=1;
    if(io_invaders[toprightr][rcol].pos.x >= WIDTH-(2*SPRITEWIDTH)) moveleft=1;
  }

  // changes direction when all rows of leftmost/rightmost column are outside
  // respective boundaries when all invaders are alligned (cycleover=1)
  if(moveleft && cycleover)
    {
    for(int r=0; r<ROWS; ++r)
    {
      for(int c=0; c<COLS; ++c)
      {
          if(io_invaders[r][c].direction==FWD && !_startscreen)
          {
            // I used DWNBWD to save the info that it will then go BWD after
            // moving downwards
            io_invaders[r][c].direction=DWNBWD;
            // if on startscreen then invaders wouldn't move down
          }
          else
          {
            // this else clause happens when direction==BWD
            // the direction BWD is assigned further below in code
            // this stops invaders moving downwards indefinately
            io_invaders[r][c].direction=BWD;
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
          if(io_invaders[r][c].direction==BWD && !_startscreen)
          {
            io_invaders[r][c].direction=DWNFWD;
          }
          else
          {
            io_invaders[r][c].direction=FWD;
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
      if(*io_freeze==0)
      {
        io_invaders[r][c].frame++;
      }
      // the explosion frame measures how long the explosion has been active
      if(io_invaders[r][c].type == EXPLOSION)
      {
        io_invaders[r][c].explosionframe++;
      }
      // we limit the explosion to 3 frames below
      if(io_invaders[r][c].type == EXPLOSION && io_invaders[r][c].explosionframe > 15 && io_invaders[r][c].active)
      {
        io_invaders[r][c].active = 0;
        // If I update freeze directly in middle of iterating through invaders
        // the rest of the invaders will be ofset from the others so I use freezelag
        // I assign freeze to freezelagfix at bottom of updateinvaders function
        freezelagfix = 0;
      }

      if(io_invaders[r][c].frame%*io_howfast==0 && *io_freeze==0 && io_invaders[r][c].active)
      {
        // moves the invader depending on direction
        if(io_invaders[r][c].direction==FWD)
        {
          io_invaders[r][c].pos.x+=10;
        }
        else if(io_invaders[r][c].direction==BWD)
        {
          io_invaders[r][c].pos.x-=10;
        }
        else if(io_invaders[r][c].direction==DWNBWD)
        {
          io_invaders[r][c].pos.y+=20;
          io_invaders[r][c].direction=BWD;
        }
        else if(io_invaders[r][c].direction==DWNFWD)
        {
          io_invaders[r][c].pos.y+=20;
          io_invaders[r][c].direction=FWD;
        }

        if(io_invaders[r][c].sprite==0){
          io_invaders[r][c].sprite=1;
        }
        else{
          io_invaders[r][c].sprite=0;
        }
        // fires missile
        if(io_invaders[r][c].bottom)
        {
          int random = rand();
          // if _startscreen then the missiles must not fire in front of the text
          if((!_startscreen && random%2==0) || (random%2==0 && _startscreen && (io_invaders[r][c].pos.x>410 || \
                                               io_invaders[r][c].pos.x<(WIDTH/2)-115))){
            for(int m=1; m<MISSILESNUMBER; ++m)
            {
              if(io_missiles[m].active==0){
                Missile newinvadermissile;
                newinvadermissile.pos.x = io_invaders[r][c].pos.x;
                newinvadermissile.pos.y = io_invaders[r][c].pos.y;
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
                io_missiles[m]=newinvadermissile;
                break;
              }
            }
          }
        }
      }
    }
  }
  *io_freeze = freezelagfix;
}

