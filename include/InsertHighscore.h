/// \file InsertHighscore.h
/// \brief inserts new highscore to highscore array while keeping ascending order
/// \author Thomas Collingwood
/// \version 1.0
/// \date 9/12/15 Updated to NCCA Coding standard

#ifndef _INSERTHIGHSCORE_H_
#define _INSERTHIGHSCORE_H_

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "Highscore.h"

///
/// \brief insertHighscore
/// \param highscores the ordered array of Highscore structs that are the highscores of the game
/// \param name the name to be inserted into highscores
/// \param score the score to be inserted into the highscores
///
void insertHighscore(Highscore highscores[3],char name[3], int score);

#endif
