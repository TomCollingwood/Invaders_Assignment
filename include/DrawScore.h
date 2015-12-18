/// \file DrawScore.h
/// \brief draws the current score and highscore
/// \author Thomas Collingwood
/// \version 1.0
/// \date 9/12/15 Updated to NCCA Coding standard

#ifndef _DRAWHIGHSCORE_H_
#define _DRAWHIGHSCORE_H_

#include <SDL.h>
#include <SDL_image.h>
#include <stdio.h>
#include <stdlib.h>

#include "Highscore.h"


///
/// \brief drawScore
/// \param highscores
///
void drawScore(Highscore highscores[5]);

#endif
