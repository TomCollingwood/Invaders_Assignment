///
///  @file InitializeHighscores.c
///  @brief initializes all highscores to 0 and names to "---"

#include "include/InitializeHighscores.h"

///
/// \brief initializeHighscores
/// \param highscores the array of Highscore structs used for the highscores of the game
///
void initializeHighscores(Highscore highscores[3])
{
  for(int i=0; i<3; ++i)
  {
    strcpy(highscores[i].name,"---");
    highscores[i].score=0;
  }
}
