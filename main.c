#include <SDL.h>
#include <SDL_image.h>
#include <stdio.h>
#include <stdlib.h>
#include "drawText.h"
#include "updateInvaders.h"
#include "defender.h"
#include "initializeInvaders.h"
#include "drawHighscore.h"
#include "initializeHighscores.h"
#include "direction.h"
#include "selectLetter.h"
#include "insertHighscore.h"

// include the map for the maze.
// the width of the screen
#define WIDTH 651
// the height of the screen
#define HEIGHT 744
// an enumeration for direction to move USE more enums!

void initializeDefender(Defender *defender);
void drawInvaders(SDL_Renderer *ren,SDL_Texture *tex,Invader invaders[ROWS][COLS]);
void updateDefender(Defender *defender, enum DIRECTION input, Missile missiles[], int *freeze);
void drawDefender(SDL_Renderer *ren, SDL_Texture *tex, Defender *defender);
void updateMissiles(Missile missiles[]);
void drawMissiles(SDL_Renderer *ren, SDL_Texture *tex, Missile missiles[]);
void updateCollisions(Missile missiles[], Invader invaders[ROWS][COLS], Defender *defender, \
                      int *freeze, int *score, int frame);

int main()
{
  int freeze = 0;
  int howfast = 55;
  int frame=0;
  Invader invaders[ROWS][COLS];
  Missile missiles[5];
  Missile startscreenmissiles[40];
  Defender defender;
  Highscore highscores[3];
  int score = 0;

  initializeHighscores(highscores);
  initializeInvaders(invaders);
  initializeDefender(&defender);

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
  // below sets black to transparent
  SDL_SetColorKey(image, SDL_TRUE, SDL_MapRGB(image->format, 0, 0, 0 ) );


  // SDL texture converts the image to a texture suitable for SDL rendering  / blitting
  // once we have the texture it will be store in hardware and we don't need the image data anymore

  SDL_Texture *tex = 0;
  tex = SDL_CreateTextureFromSurface(ren, image);

  // free the image
  SDL_FreeSurface(image);

  int quit=0;
  int menu=0;
  int previousmenu=0;
  int menuselect=0;
  enum DIRECTION input = NONE;
  enum DIRECTION startscreeninput = NONE;

  int red = 0;
  int green = 0;
  int blue = 0;

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
        case SDLK_RETURN : input = FIRE; break;
        case SDLK_UP : input = UPS; break;
        case SDLK_DOWN : input = DOWNS; break;
        case SDLK_r : input = RESET; break;
        default : input = NONE; break;
        }
      }
      else if (event.type == SDL_KEYUP)
      {
        // this stops the defender moving without keypresses
        input = NONE;
      }
    }

    // now we clear the screen (will use the clear colour set previously)

//    if(red>0) red++;
//    else if (red>255) red=0;
//    if(green>0) green++;
//    else if (green>255) green=0;
//    if(blue>0) blue++;
//    else if (blue>255) blue=0;

    SDL_SetRenderDrawColor(ren, red, green, blue, 255);

    SDL_RenderClear(ren);

    static enum DIRECTION previousinput = NONE;

    if(input==RESET){
      defender.active=1;
      defender.sprite=0;
      freeze=0;
      initializeInvaders(invaders);
      menu=0;
    }

    if(menu==2){
      if(defender.active==0){
        previousmenu=2;
        menu=3;
      }

      updateDefender(&defender,input,missiles,&freeze);
      drawDefender(ren,tex,&defender);

      updateMissiles(missiles);
      drawMissiles(ren,tex,missiles);

      updateCollisions(missiles,invaders,&defender,&freeze,&score,frame);

      if(numberactive(invaders)>0) updateInvaders(invaders,missiles,&freeze,&howfast,0);
      else{
        previousmenu=2;
        menu=3;
      }

      drawInvaders(ren,tex,invaders);

      char scoretext[50];
      sprintf(scoretext,"HIGHSCORE= 0000 Score= %d",score);

      drawText(ren,tex,scoretext,80,30,1);

      frame++;

//      char stringframe[10];
//      sprintf(stringframe,"%d",frame);
//      drawText(ren,tex,stringframe,0,30,1);

//      printf("%d",frame);

//      int inttype0, inttype1, inttype2;

//      if(frame<3000){
//        inttype0 = (-0.025)*frame+100;
//        inttype1 = (-0.05)*frame+200;
//        inttype2 = (-0.1)*frame+400;
//      }
//      else{
//        inttype0 = 25;
//        inttype1 = 50;
//        inttype2 = 100;
//      }


//      char stringtype[100];

//      sprintf(stringtype,"%d   %d   %d",inttype0,inttype1,inttype2);

//      drawText(ren,tex,stringtype,60,30,1);
//      drawText(ren,tex,stringframe,0,30,1);
    }
    else if(menu==0 || menu==1){
      howfast=55;
      //initializedefender(&defender);
      drawText(ren,tex,"SPACE INVADERS",7,50,2.9);
      frame = 0;
      if(menu==0){
        drawText(ren,tex,"START GAME",(WIDTH/2)-100,370,1);
        drawText(ren,tex,"HIGHSCORES",(WIDTH/2)-100,470,1);
        drawText(ren,tex,"EXIT",WIDTH/2-35,570,1);

        if(input==UPS && previousinput==NONE){
          //SDL_Delay(150);
          if(menuselect!=0) menuselect--;
        }
        else if (input==DOWNS && previousinput==NONE){
          //SDL_Delay(150);
          if(menuselect!=2) menuselect++;
        }
        else if (input==FIRE && previousinput==NONE){
          if(menuselect==0){
            menu=2;
          }
          else if (menuselect==1) menu=1;
          else if (menuselect==2) quit=1;
        }
        if(menuselect==0){
          drawText(ren,tex,">",(WIDTH/2)-115,370,1);
        }
        else if(menuselect==1){
          drawText(ren,tex,">",(WIDTH/2)-100-15,470,1);
        }
        else{
          drawText(ren,tex,">",(WIDTH/2)-100-15,570,1);
        }
      }
      else {
        drawText(ren,tex,"HIGHSCORES",(WIDTH/2)-100,370,1);
        drawText(ren,tex,"EXIT",WIDTH/2-35,570,1);
        drawText(ren,tex,">",(WIDTH/2)-100-15,570,1);

        FILE *file;
        if( (file=fopen("highscores","w+")) ==NULL)
        {
          printf("could not open highscores file\n");
          exit(EXIT_FAILURE);
        }
        //fwrite(highscores,sizeof(Highscore),3,file);
        //reads highscores
        fread(highscores,sizeof(Highscore),3,file);
        fclose(file);

        int yvalue = 420;
        for(int i=0; i<3; i++){
          char highscore[10];
          sprintf(highscore,"%s - %d",highscores[i].name,highscores[i].score);
          drawText(ren,tex,highscore,270,yvalue,1);
          yvalue+=50;
        }

        if(input==FIRE && previousinput==NONE){
          menu=0;
        }
      }



      updateDefender(&defender,startscreeninput,startscreenmissiles,&freeze);
      drawDefender(ren,tex,&defender);

      updateMissiles(startscreenmissiles);
      drawMissiles(ren,tex,startscreenmissiles);

      updateInvaders(invaders,startscreenmissiles,&freeze,&howfast,1);
      drawInvaders(ren,tex,invaders);

      previousinput = input;
    }

    else if(menu==3){
      drawDefender(ren,tex,&defender);
      updateDefender(&defender,NONE,missiles,&freeze);
      FILE *file;
      if( (file=fopen("highscores","w+")) ==NULL)
      {
        printf("could not open highscores file\n");
        exit(EXIT_FAILURE);
      }
      //reads highscores
      fread(highscores,sizeof(Highscore),3,file);
      fclose(file);

      int newhighscore = 0;

      for(int i=0; i<3; i++){
        if(highscores[i].score<score){
          drawText(ren,tex,"NEW HIGHSCORE",20,30,3);
          newhighscore=1;
          break;
        }
      }

      if(newhighscore){
        static int selectposition=0;
        int xpivot=50;
        int ypivot=200;
        static enum DIRECTION previousinput = NONE;
        static int letter1int=65;
        static int letter2int=65;
        static int letter3int=65;

        if(previousmenu!=3){
          letter1int=65;
          letter2int=65;
          letter3int=65;
        }

        char letter1char[5];
        char letter2char[5];
        char letter3char[5];

        sprintf(letter1char,"%c",(char)letter1int);
        sprintf(letter2char,"%c",(char)letter2int);
        sprintf(letter3char,"%c",(char)letter3int);

        if(input==RIGHT && previousinput==NONE) selectposition++;
        if(input==LEFT && previousinput==NONE) selectposition--;

        if(selectposition<0) selectposition=3;
        if(selectposition>3) selectposition=0;

        if(selectposition!=3){
          if(selectposition==0){
            letter1int=selectLetter(letter1int,input,previousinput);
          }
          else if(selectposition==1){
            letter2int=selectLetter(letter2int,input,previousinput);
            printf("(2:%d)",letter2int);
          }
          else if(selectposition==2){
            letter3int=selectLetter(letter3int,input,previousinput);
            printf("(3:%d)",letter3int);
          }
          drawText(ren,tex,"u",xpivot+selectposition*100-15,ypivot-75,5);
          drawText(ren,tex,"d",xpivot+selectposition*100-15,ypivot+125,5);
        }
        if(selectposition==3){
          drawText(ren,tex,"u",xpivot+220,ypivot+290,5);
        }
        drawText(ren,tex,letter1char,xpivot,ypivot,5);
        drawText(ren,tex,letter2char,xpivot+100,ypivot,5);
        drawText(ren,tex,letter3char,xpivot+200,ypivot,5);
        drawText(ren,tex,"ENTER",xpivot+150,ypivot+200,3);
        char scorestring[10];
        sprintf(scorestring,"%d",score);
        drawText(ren,tex,"SCORE",xpivot+350,ypivot+30,2);
        drawText(ren,tex,scorestring,xpivot+350,ypivot+80,1.5);
        previousinput = input;

        //here we submit the score
        if(selectposition==3 && input==FIRE){
          char name1[10];
          sprintf(name1,"%s%s%s",letter1char,letter2char,letter3char);
          char name2[3];

          for(int i=0;i<3;i++){
            name2[i]=name1[i];
          }

          insertHighscore(highscores,name2,score);
          FILE *file;
          if( (file=fopen("highscores","w+")) ==NULL)
          {
            printf("could not open highscores file\n");
            exit(EXIT_FAILURE);
          }
          //reads highscores
          fwrite(highscores,sizeof(Highscore),3,file);
          fclose(file);
          menu=0;
        }

      }
      previousmenu=3;
    }
    // Up until now everything was drawn behind the scenes.
    // This will show the new, red contents of the window.
    SDL_RenderPresent(ren);
  }
  SDL_Quit();
  return 0;
}

int numberactive(Invader invaders[ROWS][COLS]){
  int numberactive=0;
  for(int r=0; r<ROWS;r++){
    for(int c=0; c<COLS; c++){
      if(invaders[r][c].active) numberactive++;
    }
  }
  return numberactive;
}

// Initializes defender starting position and size
void initializeDefender(Defender *defender)
{
  defender->pos.x=WIDTH/2 - SPRITEWIDTH/2;
  defender->pos.y=HEIGHT-80;
  defender->pos.w=39;
  defender->pos.h=24;
  defender->sprite=0;
  defender->active=1;
  defender->frame=0;
}

// Draws the defender texture onto the defender
void drawDefender(SDL_Renderer *ren, SDL_Texture *tex, Defender *defender)
{
  SDL_Rect SrcRS0;
  SrcRS0.x=0;
  SrcRS0.y=0;
  SrcRS0.w=DEFENDERWIDTH;
  SrcRS0.h=DEFENDERHEIGHT;

  SDL_Rect SrcRS1;
  SrcRS1.x=111;
  SrcRS1.y=27;
  SrcRS1.w=EXPLODEDDEFENDERWIDTH;
  SrcRS1.h=DEFENDERHEIGHT;

  SDL_Rect SrcRS2;
  SrcRS2.x=69;
  SrcRS2.y=105;
  SrcRS2.w=EXPLODEDDEFENDERWIDTH;
  SrcRS2.h=DEFENDERHEIGHT;

  if(defender->sprite==0)
    SDL_RenderCopy(ren,tex,&SrcRS0,&defender->pos);
  else{
    defender->pos.w=EXPLODEDDEFENDERWIDTH;
    if(defender->sprite==1)
    {
      SDL_RenderCopy(ren,tex,&SrcRS1,&defender->pos);
    }
    else{
      SDL_RenderCopy(ren,tex,&SrcRS2,&defender->pos);
    }
  }
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

// Updates defender position and creates new defender missiles if SPACE bar hit
void updateDefender(Defender *defender, enum DIRECTION input, Missile missiles[], int *freeze)
{
  if(defender->active){
    if(input == RIGHT)
    {
      defender->pos.x += 5;
    }
    else if (input == LEFT)
    {
      defender->pos.x += -5;
    }
    // Here we create a new missile
    else if (input == FIRE && missiles[0].active==0 && *freeze==0)
    {
      Missile newmissile;
      newmissile.dir = UP;
      newmissile.pos.x = defender->pos.x + 18;
      newmissile.pos.y = defender->pos.y - 10;
      newmissile.pos.w = 3;
      newmissile.pos.h = 14;
      newmissile.active = 1;
      newmissile.type = DEFENDER;
      missiles[0] = newmissile;
    }
  }
  else{
    defender->frame++;
    if(defender->frame%5==0) (defender->sprite == 1) ? (defender->sprite=2) : (defender->sprite=1);
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

void updateCollisions(Missile missiles[], Invader invaders[ROWS][COLS], Defender *defender, int *freeze, int *score, int frame)
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
