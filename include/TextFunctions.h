/// \file TextFunctions.h
/// \brief an assortment of functions used in main
/// \author Thomas Collingwood
/// \version 1.0
/// \date 9/12/15 Updated to NCCA Coding standard

#ifndef _OTHERFUNCTIONS_H_
#define _OTHERFUNCTIONS_H_

#include <SDL.h>
#include <SDL_image.h>
#include <stdio.h>
#include <stdlib.h>

#include "Direction.h"

#define LETTERHEIGHT 21
#define LETTERWIDTH 15

//----------------------------------------------------------------------------------------------------------------------
/// \brief drawText         draws the text on screen at _x, _y position. You can make the
///                         text bigger with the _multiplier input
/// \param[in] _ren         the SDL_Renderer responsible for rendering images inside the window
/// \param[in] _tex         the SDL_Texture texture image that contains the game's sprites
/// \param[in] _text        the char array that you want printed/drawn on screen
/// \param[in] _x           coordinate of text on screen
/// \param[in] _y           coordinate of text on screen
/// \param[in] _multiplier  determines how big the text is (1 being normal size where a pixel
///                         is actually 3x3 pixel)
//----------------------------------------------------------------------------------------------------------------------
void drawText(SDL_Renderer *_ren, SDL_Texture *_tex, char _text[], int _x, int _y, float _multiplier);

//----------------------------------------------------------------------------------------------------------------------
/// \brief selectLetter           gives the next asciinumber depending on input
///                               this function exists as we want only the upper caps alphabet
///                               and the numbers so this function only outputs those
///                               ascii numbers
/// \param[inout] io_asciinumber  the current asciinumber to be incremented/decremented/maintained
/// \param[in] _input             the input from user
/// \param[in] _previousinput     this is the input prior to the current input
///                               having this means that the asciinumber is only incremented once
///                               for one keydown for example: \n
///                               if (input==UPS and previousinput==NONE): \n
///                                 increment asciinumber and return it
//----------------------------------------------------------------------------------------------------------------------
void selectLetter(int *io_asciinumber, enum DIRECTION _input, enum DIRECTION _previousinput);

#endif
