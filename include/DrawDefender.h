/// \file DrawDefender.h
/// \brief draws the defender on screen
/// \author Thomas Collingwood
/// \version 1.0
/// \date 9/12/15 Updated to NCCA Coding standard
/// Revision History :
/// Initial Header Version 6/12/15
/// Initial Code Version
/// \todo

#ifndef _DRAWDEFENDER_H_
#define _DRAWDEFENDER_H_

#include <SDL.h>
#include <SDL_image.h>
#include <stdio.h>
#include <stdlib.h>

#include "Defender.h"

void drawDefender(SDL_Renderer *ren, SDL_Texture *tex, Defender *defender);

#endif
