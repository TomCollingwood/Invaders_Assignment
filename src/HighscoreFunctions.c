///
///  @file HighscoreFunctions.c
///  @brief

#include "include/HighscoreFunctions.h"

//void drawScore(SDL_Renderer *ren, SDL_Texture *tex,);

void initializeHighscores(Highscore highscores[3])
{
  for(int i=0; i<3; ++i)
  {
    strcpy(highscores[i].name,"---");
    highscores[i].score=0;
  }
}

void insertHighscore(Highscore highscores[3],char name[4], int score)
{
  if(score>highscores[0].score)
  {
    Highscore tmp = highscores[1];
    highscores[1]=highscores[0];
    highscores[2]=tmp;
    strcpy(highscores[0].name,name);
    highscores[0].score=score;
  }
  else if(score>highscores[1].score)
  {
    highscores[2]=highscores[1];
    strcpy(highscores[1].name,name);
    highscores[1].score=score;
  }
  else
  {
    strcpy(highscores[2].name,name);
    highscores[2].score=score;
  }
}

void readHighscores(Highscore highscores[3])
{
  FILE *file;
  if( (file=fopen("other/highscores","r")) ==NULL)
  {
    printf("could not open highscores file\n");
    exit(EXIT_FAILURE);
  }
  for(int i=0; i<3; ++i)
  {
    fread(&highscores[i].name,sizeof(highscores[i].name),1,file);
    fread(&highscores[i].score,sizeof(highscores[i].score),1,file);
  }
  fclose(file);
}

void writeHighscores(Highscore highscores[3])
{
  FILE *file;
  if( (file=fopen("other/highscores","w")) ==NULL)
  {
    printf("could not open highscores file\n");
    exit(EXIT_FAILURE);
  }
  for(int i=0; i<3; ++i)
  {
    fwrite(&highscores[i].name,sizeof(highscores[i].name),1,file);
    fwrite(&highscores[i].score,sizeof(highscores[i].score),1,file);
  }
  fclose(file);
}


