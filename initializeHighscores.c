#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "highscore.h"

void initializeHighscores(Highscore highscores[3]){
  for(int i=0; i<3; i++){
    strcpy(highscores[i].name,"---");
    highscores[i].score=0;
  }
}
