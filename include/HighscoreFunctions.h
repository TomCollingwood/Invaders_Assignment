/// \file HighscoreFunctions.h
/// \brief put all Highscore related functions in this header and c file
/// \author Thomas Collingwood
/// \version 1.0
/// \date 9/12/15 Updated to NCCA Coding standard

#ifndef _HIGHSCOREFUNCTIONS_H_
#define _HIGHSCOREFUNCTIONS_H_

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include <SDL.h>
#include <SDL_image.h>

#include "Highscore.h"

///
/// \brief drawScore
/// \param highscores
///
void drawScore(Highscore highscores[5]);

///
/// \brief initializeHighscores
/// \param highscores an ordered array of Highscore struct objects that are the highscores in the game
///
void initializeHighscores(Highscore highscores[3]);

///
/// \brief insertHighscore
/// \param highscores the ordered array of Highscore structs that are the highscores of the game
/// \param name the name to be inserted into highscores
/// \param score the score to be inserted into the highscores
///
void insertHighscore(Highscore highscores[3],char name[3], int score);

///
/// \brief readHighscores
/// \param highscores an ordered array of Highscore structs that are the highscores in the game
///
void readHighscores(Highscore highscores[3]);

///
/// \brief writeHighscores
/// \param highscores an ordered array of Highscore structs that are the highscores in the game
///
void writeHighscores(Highscore highscores[3]);

#endif
