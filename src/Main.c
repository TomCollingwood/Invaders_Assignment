///
///  @file    Main.c
///  @brief   contains the main method - creates window and runs the game
///  @author  John Macey & Thomas Collingwood
///
// README!!!
// The invader's movement is deliberately jagged and ripples
// because in the ORIGINAL game the invaders move in a ripple effect
//
// Also my take on io_ and _o parameters is that if the input is used in as a
// conditional inside the function, as an input to another function inside the
// function and/or as output then it's io_.
//

#include "include/Headers.h"

int main()
{
  int freeze = 0;
  int howfast = 55;
  int frame=0;
  Invader invaders[ROWS][COLS];
  Missile missiles[5];
  Missile startscreenmissiles[40];
  Defender defender;
  int barriers[4][BARRIERHEIGHT][BARRIERWIDTH];
  Highscore highscores[3];
  int score = 0;

  readHighscores(highscores);
  initializeInvaders(invaders);
  initializeDefender(&defender);
  initializeBarriers(barriers);

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

  // we are going to use the extension SDL_image library to load a bmp, documentation can be found here
  // http://www.libsdl.org/projects/SDL_image/
  image=IMG_Load("textures/SpriteSheet.bmp");
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

  // menu==0 MAIN MENU
  // menu==1 HIGHSCORES
  // menu==2 GAME
  // menu==3 GAMEOVER / NEW HIGHSCORE

  int previousmenu=0;
  int menuselect=0;
  enum DIRECTION input = NONE;
  enum DIRECTION startscreeninput = NONE;

  int red = 0;
  int green = 0;
  int blue = 0;

  // now we are going to loop until quit, process the keys then draw
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

    SDL_SetRenderDrawColor(ren, red, green, blue, 255);

    SDL_RenderClear(ren);

    static enum DIRECTION previousinput = NONE;

    if(input==RESET)
    {
      initializeDefender(&defender);
      initializeInvaders(invaders);
      freeze=0;
      menu=0;
    }

    //-------------------------------GAME-------------------------------------------------
    if(menu==2)
    {
      // if defender is dead go to GAMEOVER SCREEN
      if(defender.active==0) {menu=3;}

      // if first frame of INGAME MODE
      if(previousmenu==0 || previousmenu==3)
      {
        score = 0;
        initializeBarriers(barriers);
      }
      // this allows movement from main menu to game
      // to be smooth (invaders are same position)
      else if(previousmenu!=2){
        initializeInvaders(invaders);
        initializeDefender(&defender);
      }

      //leftover missiles from startscreen
      updateMissiles(startscreenmissiles);
      drawMissiles(ren,tex,startscreenmissiles);

      updateBarriers(barriers,missiles);
      drawBarriers(ren,barriers);

      updateDefender(&defender,input,missiles,freeze);
      drawDefender(ren,tex,&defender);

      updateMissiles(missiles);
      drawMissiles(ren,tex,missiles);

      updateCollisions(missiles,invaders,&defender,&freeze,&score,frame);

      // only update invaders if there are any invaders otherwise quit to gameover
      if(howManyActive(invaders)>0) {updateInvaders(invaders,missiles,&freeze,&howfast,0);}
      else {menu=3;}

      drawInvaders(ren,tex,invaders);

      // quit if invaders are on level with defender
      if(getLowestY(invaders)>HEIGHT-120) { menu=3; }

      drawScore(ren,tex,score,highscores);

      frame++;

      previousmenu=2;
    }

    //-------------------------------MAIN MENU/HIGHSCORES---------------------------------
    else if(menu==0 || menu==1){
      howfast=55;
      drawText(ren,tex,"SPACE INVADERS",7,50,2.9);
      frame = 0;

      // the code below makes invaders move in background
      if(previousmenu!=0)
      {
        initializeDefender(&defender);
        initializeInvaders(invaders);
      }

      updateDefender(&defender,startscreeninput,startscreenmissiles,freeze);
      drawDefender(ren,tex,&defender);

      updateMissiles(startscreenmissiles);
      drawMissiles(ren,tex,startscreenmissiles);

      updateInvaders(invaders,startscreenmissiles,&freeze,&howfast,1);
      drawInvaders(ren,tex,invaders);

      //-------------------------------MAIN MENU------------------------------------------
      if(menu==0){
        drawText(ren,tex,"SPACE INVADERS",7,50,2.9);
        drawText(ren,tex,"START GAME",(WIDTH/2)-100,370,1);
        drawText(ren,tex,"HIGHSCORES",(WIDTH/2)-100,470,1);
        drawText(ren,tex,"EXIT",WIDTH/2-35,570,1);

        // without previousinput the menuselect would
        // cycle very very quickly on keypress
        // this way it moves once per keypress
        if(input==UPS && previousinput==NONE)
        {
          if(menuselect!=0) menuselect--;
        }
        else if (input==DOWNS && previousinput==NONE)
        {
          if(menuselect!=2) menuselect++;
        }
        else if (input==FIRE && previousinput==NONE)
        {
          if(menuselect==0) menu=2;
          else if (menuselect==1) menu=1;
          else if (menuselect==2) quit=1;
        }

        if(menuselect==0)
          drawText(ren,tex,">",(WIDTH/2)-115,370,1);
        else if(menuselect==1)
          drawText(ren,tex,">",(WIDTH/2)-100-15,470,1);
        else
          drawText(ren,tex,">",(WIDTH/2)-100-15,570,1);
      }

      //-------------------------------HIGHSCORES-----------------------------------------
      else
      {
        drawText(ren,tex,"SPACE INVADERS",7,50,2.9);
        drawText(ren,tex,"HIGHSCORES",(WIDTH/2)-100,370,1);

        readHighscores(highscores);

        int yvalue = 420;
        for(int i=0; i<3; ++i)
        {
          char highscore[100];
          sprintf(highscore,"%s - %d",highscores[i].name,highscores[i].score);
          drawText(ren,tex,highscore,(WIDTH/2)-95,yvalue,1);
          yvalue+=50;
        }

        static int highscoresSelectPosition = 0;

        drawText(ren,tex,">",240,560+highscoresSelectPosition*50,1);
        drawText(ren,tex,"RESET",260,560,1);
        drawText(ren,tex,"BACK",260,610,1);

        if(input==UPS && previousinput==NONE) {
          if(highscoresSelectPosition==1){
            highscoresSelectPosition--;
          }
        }

        else if(input==DOWNS && previousinput==NONE) {
          if(highscoresSelectPosition==0){
            highscoresSelectPosition++;
          }
        }

        if(input==FIRE && previousinput==NONE && highscoresSelectPosition == 1)
        {
          menu=0;
        }
        else if (input==FIRE && previousinput==NONE && highscoresSelectPosition==0)
        {
          initializeHighscores(highscores);
          writeHighscores(highscores);
        }
      }
      previousinput = input;
      previousmenu=0;
    }

    //-------------------------------GAMEOVER/NEWHIGHSCORE--------------------------------
    else if(menu==3)
    {
      drawDefender(ren,tex,&defender);
      updateDefender(&defender,NONE,missiles,freeze);

      readHighscores(highscores);

      int newhighscore = 0;

      // checks if score is a new highscore
      for(int i=0; i<3; ++i){
        if(highscores[i].score<score)
        {
          newhighscore=1;
          break;
        }
      }

      //-------------------------------NEW HIGHSCORE--------------------------------------
      if(newhighscore){
        drawText(ren,tex,"NEW HIGHSCORE",20,30,3);
        static int selectposition=0;
        int xpivot=50;
        int ypivot=200;
        static enum DIRECTION previousinput = NONE;
        static int letter1int=65;
        static int letter2int=65;
        static int letter3int=65;

        // the code below allows user to input 3 letter name

        // This resets to AAA if just opened
        if(previousmenu!=3)
        {
          letter1int=65;
          letter2int=65;
          letter3int=65;
        }

        // chars to store the letters
        char letter1char[5];
        char letter2char[5];
        char letter3char[5];

        // converting int to char and put into the chars
        sprintf(letter1char,"%c",(char)letter1int);
        sprintf(letter2char,"%c",(char)letter2int);
        sprintf(letter3char,"%c",(char)letter3int);

        if(input==RIGHT && previousinput==NONE) {selectposition++;}
        if(input==LEFT && previousinput==NONE) {selectposition--;}

        if(selectposition<0) {selectposition=3;}
        if(selectposition>3) {selectposition=0;}

        if(selectposition!=3)
        {
          // when select position is on one of the three letters
          // change the letter depending on input
          if(selectposition==0)
          {
            selectLetter(&letter1int,input,previousinput);
          }
          else if(selectposition==1)
          {
            selectLetter(&letter2int,input,previousinput);
          }
          else if(selectposition==2)
          {
            selectLetter(&letter3int,input,previousinput);
          }
          // "u" and "d" are up and down arrow heads
          // they are positioned above/below the selected letter
          drawText(ren,tex,"u",xpivot+selectposition*100-15,ypivot-75,5);
          drawText(ren,tex,"d",xpivot+selectposition*100-15,ypivot+125,5);
        }
        if(selectposition==3)
        {
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

        //here we submit and write the score
        if(selectposition==3 && input==FIRE)
        {
          char name[4];
          sprintf(name,"%c%c%c",letter1char[0],letter2char[0],letter3char[0]);
          insertHighscore(highscores,name,score);
          writeHighscores(highscores);
          selectposition=0;
          menu=0;
        }

      }
      //-------------------------------GAMEOVER-------------------------------------------
      else
      {
        drawText(ren,tex,"GAME OVER",5,270,4.6);
        drawText(ren,tex,"RESTART",100,400,2);
        drawText(ren,tex,"MAIN MENU",100,450,2);
        static int selectpositionGameover =0;
        drawText(ren,tex,">",80,400+(selectpositionGameover%2)*50,2);

        if(((input==UPS) || (input==DOWNS)) && previousinput==NONE)
        {
          selectpositionGameover++;
        }

        if(selectpositionGameover%2==0 && input==FIRE) {
          selectpositionGameover=0;
          menu=2;
        }
        else if (input==FIRE)
        {
          selectpositionGameover=0;
          menu=0;
        }
        previousinput=input;
      }
      previousmenu=3;
    }
    // Up until now everything was drawn behind the scenes.
    // This will show the new, rendered contents of the window.
    SDL_RenderPresent(ren);
  }
  SDL_Quit();
  return 0;
}
