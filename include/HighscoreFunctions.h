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
#include "TextFunctions.h"

//----------------------------------------------------------------------------------------------------------------------
/// \brief drawScore      Draws the current and highest score on top of screen.
/// \param[in] _ren       the SDL_Renderer responsible for rendering images inside the window
/// \param[in] _tex       the SDL_Texture texture image that contains the game's sprites
/// \param[in] _score     current game score
/// \param[in]_highscores takes the top highscore from this array and draws it along with
///                       current score
//----------------------------------------------------------------------------------------------------------------------
void drawScore(SDL_Renderer *_ren, SDL_Texture *_tex, int score, Highscore _highscores[5]);

//----------------------------------------------------------------------------------------------------------------------
/// \brief initializeHighscores sets all highscores in highscore array to
///                             name "---" and score 0
/// \param[out] o_highscores    an ordered array of Highscore struct objects
///                             that are the highscores in the game
//----------------------------------------------------------------------------------------------------------------------
void initializeHighscores(Highscore o_highscores[3]);

//----------------------------------------------------------------------------------------------------------------------
/// \brief insertHighscore      inserts highscore into highscores array while
///                             keeping right order
/// \param[inout] io_highscores the ordered array of Highscore structs that are the
///                             highscores of the game
/// \param[in] _name            the name to be inserted into highscores
/// \param[in] _score           the score to be inserted into the highscores
//----------------------------------------------------------------------------------------------------------------------
void insertHighscore(Highscore io_highscores[3],char _name[3], int _score);

//----------------------------------------------------------------------------------------------------------------------
/// \brief readHighscores     reads highscores from "other/highscores" and writes to
///                           io_highscores array
/// \param[in] io_highscores  an ordered array of Highscore structs that are the
///                           highscores in the game
//----------------------------------------------------------------------------------------------------------------------
void readHighscores(Highscore io_highscores[3]);

//----------------------------------------------------------------------------------------------------------------------
/// \brief writeHighscores  takes the highscores from io_highscores and writes them
///                         to file "other/highscores"
/// \param[in] _highscores  an ordered array of Highscore structs that are the highscores
///                         in the game
//----------------------------------------------------------------------------------------------------------------------
void writeHighscores(Highscore _highscores[3]);

#endif
