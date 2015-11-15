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
void updateInvaders(Invader invaders[ROWS][COLS], enum DIRECTION input);
void drawInvaders(SDL_Renderer *ren,SDL_Texture *tex,Invader invaders[ROWS][COLS]);
void updateDefender(SDL_Rect *def, enum DIRECTION input, Missile missiles[]);
void drawDefender(SDL_Renderer *ren, SDL_Texture *tex, SDL_Rect *def);
void updateMissiles(Missile missiles[]);
void drawMissiles(SDL_Renderer *ren, Missile missiles[]);
void updateCollisions(Missile missiles[], Invader invaders[ROWS][COLS]);

int freeze=0;

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
      if(freeze==0){
        freeze=1;
      }
      else{
        freeze=0;
      }
    }

    // now we clear the screen (will use the clear colour set previously)
    SDL_SetRenderDrawColor(ren, 0, 0, 0, 255);

    SDL_RenderClear(ren);

    updateDefender(&def,input,missiles);
    drawDefender(ren,tex,&def);

    updateMissiles(missiles);
    drawMissiles(ren,missiles);

    updateCollisions(missiles,invaders);

    updateInvaders(invaders,input);
    drawInvaders(ren,tex,invaders);

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
    frameoffset = r*11;
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

// Updates invaders positions
void updateInvaders(Invader invaders[ROWS][COLS], enum DIRECTION input)
{
  int howfast = 55;

  int freezelagfix = freeze;

  if(input == RESET){
    initializeInvaders(invaders);
  }

  enum DIR{FWD,BWD};
  int yinc=0;
  static int DIRECTION=FWD;

  // find leftmost & rightmost column with at least one active invader
  int lcol = 0;
  int rcol = COLS-1;
  for(int c=0; c<COLS; c++){
    int counter = 0;
    for(int r=0; r<ROWS; r++){
      if(invaders[r][c].active==1) counter++;
    }
    if (counter==0 && lcol==c && lcol != rcol){
      lcol=c+1;
    }
    else if (counter==0 && rcol==c && lcol != rcol){
      rcol=c-1;
    }
  }

  int rcolcounter=0;
  for(int i=0; i<ROWS; ++i){
    if(invaders[i][rcol].pos.x>=WIDTH-(2*SPRITEWIDTH)){
      rcolcounter++;
    }
  }

  int lcolcounter=0;
  for(int i=0; i<ROWS; ++i){
    if(invaders[i][lcol].pos.x<=SPRITEWIDTH){
      lcolcounter++;
    }
  }

  int cycleover = 0;
  if(invaders[0][0].pos.x==invaders[ROWS-1][0].pos.x){
    cycleover = 1;
  }

  // mark the side columns before moving them
  if(rcolcounter==ROWS && cycleover==1)
    {
    DIRECTION=BWD;
    //freeze = 1;
    yinc=GAP;
  }
  else if(lcolcounter==ROWS && cycleover==1)
  {
    DIRECTION=FWD;
    yinc=GAP;
  }

  // for each invader
  for(int r=0; r<ROWS; ++r)
  {
    for(int c=0; c<COLS; ++c)
    {
      invaders[r][c].frame++;
      if(invaders[r][c].frame%howfast==0){
        if(freeze==0){
          if(DIRECTION==FWD)
            invaders[r][c].pos.x+=10;
          else
            invaders[r][c].pos.x-=10;

          //invaders[r][c].pos.y+=yinc;

          if(invaders[r][c].sprite==0){
            invaders[r][c].sprite=1;
          }
          else{
            invaders[r][c].sprite=0;
          }
        }

        if(invaders[r][c].type == EXPLOSION && invaders[r][c].frame > 1 && invaders[r][c].active==1){
          invaders[r][c].active = 0;
          // If I update freeze directly in middle of iterating through invaders
          // the rest of the invaders will be ofset from the others so I use
          // freezelag fix
          freezelagfix = 0;
        }
      }
    }
  }
  freeze = freezelagfix;
}

// Checks missiles list for an active defender missile
int activedefmissile(Missile missiles[]){
  int activedefmissile = 0;
  for(int m=0; m<MISSILESNUMBER; m++){
    if(missiles[m].active ==1 && missiles[m].type == DEFENDER){
      activedefmissile = 1;
    }
  }
  return activedefmissile;
}

// Updates defender position and creates new defender missiles if SPACE bar hit
void updateDefender(SDL_Rect *def, enum DIRECTION input, Missile missiles[]) {
  if(input == RIGHT)
  {
    def->x += 5;
  }
  else if (input == LEFT)
  {
    def->x += -5;
  }
  // Here we create a new missile
  else if (input == FIRE && activedefmissile(missiles)==0 && freeze==0)
  {
    Missile newmissile;
    newmissile.dir = UP;
    newmissile.pos.x = def->x + 18;
    newmissile.pos.y = def->y - 10;
    newmissile.pos.w = 3;
    newmissile.pos.h = 14;
    newmissile.active = 1;
    newmissile.type = DEFENDER;
    for(int m=0; m<MISSILESNUMBER; m++){
      if(missiles[m].active ==0){
        missiles[m] = newmissile;
        break;
      }
    }
  }
}

// Updates missile position depending on direction and activity
void updateMissiles(Missile missiles[]){
  for(int m=0; m<MISSILESNUMBER; m++){
    if(missiles[m].pos.y < 0 || missiles[m].pos.y >800){
      missiles[m].active = 0;
    }
    if(missiles[m].active ==1){
      if(missiles[m].dir == UP){
        missiles[m].pos.y += -15;
      }
      else if (missiles[m].dir == DOWN){
        missiles[m].pos.y += 15;
      }
    }
  }
}

// draws missiles - using SDL_RenderFillRect()
void drawMissiles(SDL_Renderer *ren, Missile missiles[])
{
  SDL_SetRenderDrawColor(ren, 255, 255, 255, 255);
  for(int m=0; m<MISSILESNUMBER; m++){
    if(missiles[m].active ==1){
      SDL_RenderFillRect(ren,&missiles[m].pos);
    }
  }
}

void updateCollisions(Missile missiles[], Invader invaders[ROWS][COLS]){
  for(int m=0; m<MISSILESNUMBER; m++){
    if(missiles[m].type == DEFENDER && missiles[m].active ==1){
      int hit = 0;
      for(int r=0; r<ROWS; r++){
        for(int c=0; c<COLS; c++){
          if(invaders[r][c].active ==1){
            int misX = missiles[m].pos.x;
            int invX = invaders[r][c].pos.x;
            int invW = invaders[r][c].pos.w;
            int misY = missiles[m].pos.y;
            int invY = invaders[r][c].pos.y;
            int misH = missiles[m].pos.h;
            if ((misX > invX) && (misX < invX+invW) && (misY-misH < invY) && hit ==0){
              invaders[r][c].type = EXPLOSION;
              freeze = 1;
              invaders[r][c].frame = 0;
              missiles[m].active = 0;
              hit = 1;
            }
          }
        }
      }
    }
  }
}

