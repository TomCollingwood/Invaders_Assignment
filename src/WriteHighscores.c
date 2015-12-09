#include "include/WriteHighscores.h"

void writeHighscores(Highscore highscores[3])
{
  FILE *file;
  if( (file=fopen("highscores","w")) ==NULL)
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
