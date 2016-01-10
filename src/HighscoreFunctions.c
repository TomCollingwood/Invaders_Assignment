///
///  @file HighscoreFunctions.c
///  @brief all the functions that operate on the highscores

#include "include/HighscoreFunctions.h"

//----------------------------------------------------------------------------------------------------------------------
void drawScore(SDL_Renderer *_ren, SDL_Texture *_tex, int _score, Highscore _highscores[3])
{
  char scoretext[50];
  sprintf(scoretext,"HIGHSCORE= %d SCORE= %d",_highscores[0].score,_score);
  drawText(_ren,_tex,scoretext,80,30,1);
}

//----------------------------------------------------------------------------------------------------------------------
void initializeHighscores(Highscore _highscores[3])
{
  for(int i=0; i<3; ++i)
  {
    strcpy(_highscores[i].name,"---");
    _highscores[i].score=0;
  }
}

//----------------------------------------------------------------------------------------------------------------------
void insertHighscore(Highscore io_highscores[3],char _name[4], int _score)
{
  if(_score>io_highscores[0].score)
  {
    Highscore tmp = io_highscores[1];
    io_highscores[1]=io_highscores[0];
    io_highscores[2]=tmp;
    strcpy(io_highscores[0].name,_name);
    io_highscores[0].score=_score;
  }
  else if(_score>io_highscores[1].score)
  {
    io_highscores[2]=io_highscores[1];
    strcpy(io_highscores[1].name,_name);
    io_highscores[1].score=_score;
  }
  else
  {
    strcpy(io_highscores[2].name,_name);
    io_highscores[2].score=_score;
  }
}

//----------------------------------------------------------------------------------------------------------------------
void readHighscores(Highscore io_highscores[3])
{
  FILE *file;
  if( (file=fopen("other/highscores","r")) ==NULL)
  {
    perror("Error: Could not open highscores file\n");
    exit(EXIT_FAILURE);
  }
  for(int i=0; i<3; ++i)
  {
    fread(&io_highscores[i].name,sizeof(io_highscores[i].name),1,file);
    fread(&io_highscores[i].score,sizeof(io_highscores[i].score),1,file);
  }
  fclose(file);
}

//----------------------------------------------------------------------------------------------------------------------
void writeHighscores(Highscore _highscores[3])
{
  FILE *file;
  if( (file=fopen("other/highscores","w")) ==NULL)
  {
    perror("Error: Could not open highscores file\n");
    exit(EXIT_FAILURE);
  }
  for(int i=0; i<3; ++i)
  {
    fwrite(&_highscores[i].name,sizeof(_highscores[i].name),1,file);
    fwrite(&_highscores[i].score,sizeof(_highscores[i].score),1,file);
  }
  fclose(file);
}


