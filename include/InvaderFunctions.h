/// \file InvaderFunctions.h
/// \brief put all invader functions into this header and c file
/// \author Thomas Collingwood
/// \version 1.0
/// \date 8/1/16 Updated to NCCA Coding standard

#ifndef _INVADERFUNCTIONS_H_
#define _INVADERFUNCTIONS_H_

#include <stdio.h>
#include <stdlib.h>

#include <SDL.h>
#include <SDL_image.h>

#include "Dimensions.h"
#include "Direction.h"
#include "HowManyActive.h"
#include "Invader.h"
#include "Missile.h"

#define WIDTH 651
#define HEIGHT 744
// This WIDTH & HEIGHT are same aspect ratio as original game
// the "pixels" of sprites are same size in relation to aspect ratio

///
/// \brief drawInvaders
/// \param ren the SDL_Renderer responsible for rendering images inside the window
/// \param tex the SDL_Texture texture image that contains the game's sprites
/// \param invaders the 2d array of Invader struct objects
///
void drawInvaders(SDL_Renderer *ren, SDL_Texture *tex, Invader invaders[ROWS][COLS]);

///
/// \brief initializeInvaders
/// \param invaders the 2d array of Invader struct objects
///
void initializeInvaders(Invader invaders[ROWS][COLS]);

///
/// \brief updateInvaders
/// \param invaders     the 2d array of Invader struct objects
/// \param missiles     the array of Missile structs (each can be of four different types)
/// \param freeze       if freeze==1 the invaders do no move their position
/// \param howfast      the lower howfast is, the faster the invaders move
/// \param startscreen if startscreen==1 then the invader's y position is not incremented
///
void updateInvaders(Invader invaders[ROWS][COLS], Missile missiles[MISSILESNUMBER], \
                    int *_freeze, int *howfast, int startscreen);

#endif
