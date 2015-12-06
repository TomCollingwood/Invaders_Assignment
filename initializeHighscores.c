#include "initializeHighscores.h"

void initializeHighscores(Highscore highscores[3]){
  for(int i=0; i<3; i++){
    strcpy(highscores[i].name,"---");
    highscores[i].score=0;
  }
}
