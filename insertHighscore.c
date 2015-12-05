#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "highscore.h"

void insertHighscore(Highscore highscores[3],char name[3], int score){
  if(score>highscores[0].score){
    Highscore tmp = highscores[1];
    highscores[1]=highscores[0];
    highscores[2]=tmp;
    strcpy(highscores[0].name,name);
    highscores[0].score=score;
  }
  else if(score>highscores[1].score){
    highscores[2]=highscores[1];
    strcpy(highscores[1].name,name);
    highscores[1].score=score;
  }
  else{
    strcpy(highscores[2].name,name);
    highscores[2].score=score;
  }
}
