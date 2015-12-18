/// \file DrawText.h
/// \brief draws the input string onto screen at (x,y) position
/// \author Thomas Collingwood
/// \version 1.0
/// \date 9/12/15 Updated to NCCA Coding standard


#ifndef _DRAWTEXT_H_
#define _DRAWTEXT_H_

#include <SDL.h>
#include <SDL_image.h>
#include <stdio.h>
#include <stdlib.h>

#define LETTERHEIGHT 21
#define LETTERWIDTH 15

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
