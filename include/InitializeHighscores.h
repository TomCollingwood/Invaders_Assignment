/// \file InitializeHighscores.h
/// \brief initializes all highscores to 0 and names to "---"
/// \author Thomas Collingwood
/// \version 1.0
/// \date 9/12/15 Updated to NCCA Coding standard

#ifndef _INITIALIZEHIGHSCORES_H_
#define _INITIALIZEHIGHSCORES_H_

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "Highscore.h"

///
/// \brief initializeHighscores
/// \param highscores an ordered array of Highscore struct objects that are the highscores in the game
///
void initializeHighscores(Highscore highscores[3]);

#endif
