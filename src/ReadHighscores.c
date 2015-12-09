#include "include/ReadHighscores.h"

void readHighscores(Highscore highscores[3])
{
  FILE *file;
  if( (file=fopen("highscores","r")) ==NULL)
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
