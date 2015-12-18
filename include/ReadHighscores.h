/// \file ReadHighscores.h
/// \brief reads highscore from highscores file and updates highscores array
/// \author Thomas Collingwood
/// \version 1.0
/// \date 9/12/15 Updated to NCCA Coding standard

#ifndef _READHIGHSCORES_H_
#define _READHIGHSCORES_H_

#include <stdio.h>
#include <stdlib.h>

#include "Highscore.h"

///
/// \brief readHighscores
/// \param highscores an ordered array of Highscore structs that are the highscores in the game
///
void readHighscores(Highscore highscores[3]);

#endif
