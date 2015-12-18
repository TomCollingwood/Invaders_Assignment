/// \file WriteHighscores.h
/// \brief writes the highscores to highscores save file
/// \author Thomas Collingwood
/// \version 1.0
/// \date 9/12/15 Updated to NCCA Coding standard

#ifndef _WRITEHIGHSCORES_H_
#define _WRITEHIGHSCORES_H_

#include <stdio.h>
#include <stdlib.h>

#include "Highscore.h"

///
/// \brief writeHighscores
/// \param highscores an ordered array of Highscore structs that are the highscores in the game
///
void writeHighscores(Highscore highscores[3]);

#endif
