#include <SDL.h>
#include <SDL_image.h>
#include <stdio.h>
#include <stdlib.h>
#include "Invader.h"
#include "missile.h"
// include the map for the maze.
// the width of the screen
#define WIDTH 651
// the height of the screen
#define HEIGHT 744
// an enumeration for direction to move USE more enums!
enum DIRECTION{LEFT,RIGHT,FIRE,NONE,RESET,FREEZE};

void initializeInvaders(Invader invaders[ROWS][COLS]);
void initializeDefender(SDL_Rect *def);
void updateInvaders(Invader invaders[ROWS][COLS], Missile missiles[MISSILESNUMBER], enum DIRECTION input);
void drawInvaders(SDL_Renderer *ren,SDL_Texture *tex,Invader invaders[ROWS][COLS]);
void updateDefender(SDL_Rect *def, enum DIRECTION input, Missile missiles[]);
void drawDefender(SDL_Renderer *ren, SDL_Texture *tex, SDL_Rect *def);
void updateMissiles(Missile missiles[]);
void drawMissiles(SDL_Renderer *ren, SDL_Texture *tex, Missile missiles[]);
void updateCollisions(Missile missiles[], Invader invaders[ROWS][COLS]);

int freeze=0;
int freezeframe=0;
int howfast=55;

int main()
{
  Invader invaders[ROWS][COLS];
  Missile missiles[5];
  SDL_Rect def;
  initializeInvaders(invaders);
  initializeDefender(&def);
  // initialise SDL and check that it worked otherwise exit
  // see here for details http://wiki.libsdl.org/CategoryAPI
  if (SDL_Init(SDL_INIT_EVERYTHING) == -1)
  {
    printf("%s\n",SDL_GetError());
    return EXIT_FAILURE;
  }
  // we are now going to create an SDL window

  SDL_Window *win = 0;
  win = SDL_CreateWindow("Invaders", 100, 100, WIDTH, HEIGHT, SDL_WINDOW_SHOWN);
  if (win == 0)
  {
    printf("%s\n",SDL_GetError());
    return EXIT_FAILURE;
  }
  // the renderer is the core element we need to draw, each call to SDL for drawing will need the
  // renderer pointer
  SDL_Renderer *ren = 0;
  ren = SDL_CreateRenderer(win, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);
  // check to see if this worked
  if (ren == 0)
  {
    printf("%s\n",SDL_GetError() );
    return EXIT_FAILURE;
  }
  // this will set the background colour to white.
  // however we will overdraw all of this so only for reference
  SDL_SetRenderDrawColor(ren, 255, 255, 255, 255);

  // SDL image is an abstraction for all images
  SDL_Surface *image;
  // we are going to use the extension SDL_image library to load a png, documentation can be found here
  // http://www.libsdl.org/projects/SDL_image/
  image=IMG_Load("SpriteSheet.bmp");
  if(!image)
  {
    printf("IMG_Load: %s\n", IMG_GetError());
    return EXIT_FAILURE;
  }
  // SDL texture converts the image to a texture suitable for SDL rendering  / blitting
  // once we have the texture it will be store in hardware and we don't need the image data anymore

  // This makes the black on the surface transparent
  SDL_SetColorKey(image, SDL_TRUE, SDL_MapRGB(image->format, 0, 0, 0 ) );

  SDL_Texture *tex = 0;
  tex = SDL_CreateTextureFromSurface(ren, image);

  // free the image
  SDL_FreeSurface(image);

  int quit=0;
  enum DIRECTION input = NONE;
  // now we are going to loop forever, process the keys then draw

  while (quit !=1)
  {
    SDL_Event event;
    // grab the SDL even (this will be keys etc)
    while (SDL_PollEvent(&event))
    {
      // look for the x of the window being clicked and exit
      if (event.type == SDL_QUIT)
        quit = 1;
      // check for a key down
      if (event.type == SDL_KEYDOWN)
      {
        switch (event.key.keysym.sym)
        {
        // if we have an escape quit
        case SDLK_ESCAPE : quit=1; break;
        case SDLK_RIGHT : input = RIGHT; break;
        case SDLK_LEFT : input = LEFT; break;
        case SDLK_SPACE : input = FIRE; break;
        case SDLK_r : input = RESET; break;
        case SDLK_f : input = FREEZE; break;
        default : input = NONE; break;
        }
      }
      else if (event.type == SDL_KEYUP)
      {
        // this stops the defender moving without keypresses
        input = NONE;
      }
    }

    if(input == FREEZE){
      if(freeze==0)
        freeze=1;
      else
        freeze=0;
    }

    // now we clear the screen (will use the clear colour set previously)
    SDL_SetRenderDrawColor(ren, 0, 0, 0, 255);

    SDL_RenderClear(ren);

    updateDefender(&def,input,missiles);
    drawDefender(ren,tex,&def);

    updateMissiles(missiles);
    drawMissiles(ren,tex,missiles);

    updateCollisions(missiles,invaders);

    updateInvaders(invaders,missiles,input);
    drawInvaders(ren,tex,invaders);

    // printf("%d",freeze);

    // Up until now everything was drawn behind the scenes.
    // This will show the new, red contents of the window.
    SDL_RenderPresent(ren);
  }

  SDL_Quit();
  return 0;
}

// Initializes defender starting position and size
void initializeDefender(SDL_Rect *def)
{
  def->x=400;
  def->y=550;
  def->w=39;
  def->h=29;
}

// Initializes all invader positions
void initializeInvaders(Invader invaders[ROWS][COLS])
{
  SDL_Rect pos;
  pos.w=SPRITEWIDTH;
  pos.h=SPRITEHEIGHT;
  int ypos=36;
  int frameoffset = COLS*ROWS*3;

  for(int r=0; r<ROWS; r++)
  {
    int xpos = GAP;
    // if(r == 0) xpos = GAP+3;
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
        invaders[r][c].type=TYPE1;
      else if(r==1 || r==2)
        invaders[r][c].type=TYPE2;
      else
        invaders[r][c].type=TYPE3;

    }
    ypos+=(GAP+SPRITEHEIGHT);
  }
  //printf("%d",invaders[ROWS-1][COLS-1].pos.x-invaders[0][0].pos.x);
}

// Draws the defender texture onto the defender
void drawDefender(SDL_Renderer *ren, SDL_Texture *tex, SDL_Rect *def)
{
  SDL_Rect SrcR;
  SrcR.x=0;
  SrcR.y=0;
  SrcR.w=39;
  SrcR.h=24;
  SDL_RenderCopy(ren,tex,&SrcR,def);
}

// Draws the invaders using RenderCopy and the texture
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
          else SDL_RenderCopy(ren, tex,&SrcTYPE1S1,&invaders[r][c].pos);
          break;
        case TYPE2 :
          if(invaders[r][c].sprite == 0)
          {
            SDL_RenderCopy(ren, tex,&SrcTYPE2S0,&invaders[r][c].pos);
          }
          else SDL_RenderCopy(ren, tex,&SrcTYPE2S1,&invaders[r][c].pos);
          break;
        case TYPE3 :
          if(invaders[r][c].sprite == 0)
          {
            SDL_RenderCopy(ren, tex,&SrcTYPE3S0,&invaders[r][c].pos);
          }
          else SDL_RenderCopy(ren, tex,&SrcTYPE3S1,&invaders[r][c].pos);
          break;
        case EXPLOSION :
          SDL_RenderCopy(ren, tex,&SrcExplode,&invaders[r][c].pos);
        }
      }
    }
  }
}

// updates invader's positions
void updateInvaders(Invader invaders[ROWS][COLS], Missile missiles[MISSILESNUMBER], enum DIRECTION input)
{
  if(input == RESET){
    freeze=0;
    initializeInvaders(invaders);
  }

  int freezelagfix = freeze;

  // find leftmost & rightmost column with at least one active invader

  int lcol = 0;
  int rcol = COLS-1;
  for(int c=0; c<COLS; c++){
    int counter = 0;
    for(int r=0; r<ROWS; r++){
      if(invaders[r][c].active) counter++;
    }
    if (counter==0 && lcol==c){
      lcol=c+1;
    }
  }

  for(int c=COLS-1; c>-1; --c){
    int counter = 0;
    for(int r=0; r<ROWS; ++r){
      if(invaders[r][c].active) counter++;
    }
    if (counter==0 && rcol==c){
      rcol=c-1;
    }
  }

  int hasfirstbeenfound=0;
  int firstr = 0;
  int firstc = 0;
  for(int r=0; r<ROWS;r++){
    for(int c=0; c<COLS; c++){
      if(hasfirstbeenfound==0 && invaders[r][c].active){
        firstr = r;
        firstc = c;
        hasfirstbeenfound=1;
      }
    }
  }

  // cycleover==1 when all invaders are alligned in a square
  int cycleover = 0;
  // this comparison is made as invaders[firstr][firstc] is first to move
  if(invaders[firstr][firstc].frame%howfast==0){
    cycleover = 1;
  }

  // howfast is how many frames it takes a cycle
  // a cycle is from one frame when all invaders are alligned
  // to the next when it's all alligned

  // we need howfast to be the range of the first invader to move to
  // the last invader to move (the frames change after a collision
  // when cycleover==1). This makes speed gradually quicker as number
  // of active invaders decreases

  int howmanyactive=0;
  for(int r=0; r<ROWS; ++r){
    for(int c=0; c<COLS; ++c){
      if(invaders[r][c].active){
        howmanyactive++;
      }
    }
  }


  if(cycleover && freeze==0){
    howfast = howmanyactive;
    //printf("!!!! %d !!!!",howmanyactive);
    howmanyactive--;
    for(int r=ROWS-1; r>=0; --r){
      for(int c=COLS-1; c>=0; --c){
        if(invaders[r][c].active){
          //printf("%d,",invaders[r][c].frame);
          invaders[r][c].frame=howmanyactive;
          //printf("%d,",howmanyactive);
          howmanyactive--;
        }
      }
    }
  }


  // the last to reach the boundary is always the highest on lefmost column
  // (lcol) and rightmost column (rcol)
  static int toprightr=0;
  static int topleftr=0;

  if(cycleover==1){
    for(int i=0;i<ROWS;i++){
      if(invaders[i][rcol].active){
        toprightr=i;
        break;
      }
    }
    for(int i=0;i<ROWS;i++){
      if(invaders[i][lcol].active){
        topleftr=i;
        break;
      }
    }
  }

  // so here we check to see if the last to reach the boundary has reached it
  int moveleft=0;
  int moveright=0;
  if(cycleover){
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
          if(invaders[r][c].direction==FWD){
            // I used DWNBWD to save the info that it will then go BWD after
            // moving downwards
            invaders[r][c].direction=DWNBWD;
          }
          else{
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
          if(invaders[r][c].direction==BWD){
            invaders[r][c].direction=DWNFWD;
          }
          else{
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
      if(freeze==0){
        invaders[r][c].frame++;
      }
      // the explosion frame measures how long the explosion has been active
      if(invaders[r][c].type == EXPLOSION){
        invaders[r][c].explosionframe++;
      }
      // we limit the explosion to 3 frames below
      if(invaders[r][c].type == EXPLOSION && invaders[r][c].explosionframe > 3 && invaders[r][c].active){
        invaders[r][c].active = 0;
        // If I update freeze directly in middle of iterating through invaders
        // the rest of the invaders will be ofset from the others so I use freezelag
        // I assign freeze to freezelagfix at bottom of updateinvaders function
        freezelagfix = 0;
      }

      if(invaders[r][c].frame%howfast==0 && freeze==0 && invaders[r][c].active){
        // moves the invader depending on direction
        if(invaders[r][c].direction==FWD){
          invaders[r][c].pos.x+=10;
        }
        else if(invaders[r][c].direction==BWD){
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
        int random = rand();
        if(random%20==0){
          for(int m=1; m<MISSILESNUMBER; m++)
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
                newinvadermissile.type = LETTERT;
              else if(random%100>33)
                newinvadermissile.type = SNAKE;
              else{
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


  freeze = freezelagfix;
}

// Updates defender position and creates new defender missiles if SPACE bar hit
void updateDefender(SDL_Rect *def, enum DIRECTION input, Missile missiles[])
{
  if(input == RIGHT)
  {
    def->x += 5;
  }
  else if (input == LEFT)
  {
    def->x += -5;
  }
  // Here we create a new missile
  else if (input == FIRE && missiles[0].active==0 && freeze==0)
  {
    Missile newmissile;
    newmissile.dir = UP;
    newmissile.pos.x = def->x + 18;
    newmissile.pos.y = def->y - 10;
    newmissile.pos.w = 3;
    newmissile.pos.h = 14;
    newmissile.active = 1;
    newmissile.type = DEFENDER;
    missiles[0] = newmissile;
  }
}

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

// draws missiles - using SDL_RenderFillRect()
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
  for(int m=0; m<MISSILESNUMBER; m++)
  {
    if(missiles[m].active)
    {
      if(missiles[m].type == DEFENDER){
        SDL_RenderFillRect(ren,&missiles[m].pos);
      }
      else if(missiles[m].type == ZIGZAG){
        if(missiles[m].sprite==0)
          SDL_RenderCopy(ren, tex,&SrcZIGZAGS0,&missiles[m].pos);
        else if(missiles[m].sprite==1)
          SDL_RenderCopy(ren, tex,&SrcZIGZAGS1,&missiles[m].pos);
        else if(missiles[m].sprite==2)
          SDL_RenderCopy(ren, tex,&SrcZIGZAGS2,&missiles[m].pos);
        else
          SDL_RenderCopy(ren, tex,&SrcZIGZAGS3,&missiles[m].pos);
      }
      else if(missiles[m].type == LETTERT){
        if(missiles[m].sprite==0)
          SDL_RenderCopy(ren, tex,&SrcLETTERTS0,&missiles[m].pos);
        else if(missiles[m].sprite==1)
          SDL_RenderCopy(ren, tex,&SrcLETTERTS1,&missiles[m].pos);
        else if(missiles[m].sprite==2)
          SDL_RenderCopy(ren, tex,&SrcLETTERTS2,&missiles[m].pos);
        else
          SDL_RenderCopy(ren, tex,&SrcLETTERTS3,&missiles[m].pos);
      }
      else{
        if(missiles[m].sprite==0)
          SDL_RenderCopy(ren, tex,&SrcSNAKES0,&missiles[m].pos);
        else if(missiles[m].sprite==1)
          SDL_RenderCopy(ren, tex,&SrcSNAKES1,&missiles[m].pos);
        else if(missiles[m].sprite==2)
          SDL_RenderCopy(ren, tex,&SrcSNAKES2,&missiles[m].pos);
        else
          SDL_RenderCopy(ren, tex,&SrcSNAKES3,&missiles[m].pos);
      }
    }
  }
}

void updateCollisions(Missile missiles[], Invader invaders[ROWS][COLS])
{
  int freezelag = freeze;
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
              invaders[r][c].type = EXPLOSION;
              freezelag = 1;
              missiles[m].active = 0;
              hit = 1;
            }
          }
        }
      }
    }
  }
  freeze=freezelag;
}

