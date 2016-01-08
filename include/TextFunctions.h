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

///
/// \brief selectLetter
/// \param asciinumber the current asciinumber to be incremented/decremented/left alone
/// \param input this is the
/// \param previousinput This is the input prior to the current input.
/// having this means that the asciinumber is only incremented once for one keydown
/// for example: when input==UPS and previousinput==NONE : increment asciinumber and return it
/// \return the incremented/decremented/same asciinumber
///
void selectLetter(int *asciinumber, enum DIRECTION input, enum DIRECTION previousinput);

///
/// \brief drawText
/// \param ren the SDL_Renderer responsible for rendering images inside the window
/// \param tex the SDL_Texture texture image that contains the game's sprites
/// \param text the char array that you want printed/drawn on screen
/// \param x coordinate of text on screen
/// \param y coordinate of text on screen
/// \param multiplier determines how big the text is (1 being normal size where a pixel is actually 3x3 pixel)
///
void drawText(SDL_Renderer *ren, SDL_Texture *tex, char text[], int x, int y, float multiplier);

#endif
