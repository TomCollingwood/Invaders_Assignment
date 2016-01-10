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
#include "TextFunctions.h"
#include "Invader.h"
#include "Missile.h"


#define WIDTH 651
#define HEIGHT 744
// This WIDTH & HEIGHT are same aspect ratio as original game
// the "pixels" of sprites are same size in relation to aspect ratio

//----------------------------------------------------------------------------------------------------------------------
/// \brief drawInvaders       Draws the invaders on screen using their SDL_Rect, active
///                           and type variables inside the invader struct
/// \param[in] _ren           the SDL_Renderer responsible for rendering images inside the window
/// \param[in] _tex           the SDL_Texture texture image that contains the game's sprites
/// \param[inout] io_invaders the 2d array of Invader struct objects
//----------------------------------------------------------------------------------------------------------------------
void drawInvaders(SDL_Renderer *_ren, SDL_Texture *_tex, Invader io_invaders[ROWS][COLS]);

//----------------------------------------------------------------------------------------------------------------------
/// \brief getHighestY   returns the highest value of Y out of all active invaders
/// \param io_invaders   the 2d array of Invader struct objects
/// \return              the highest value of Y out of all active invaders
//----------------------------------------------------------------------------------------------------------------------
int getLowestY(Invader io_invaders[ROWS][COLS]);

//----------------------------------------------------------------------------------------------------------------------
/// \brief initializeInvaders Initializes invaders to a starting position and making them
///                           all active.
/// \param[out] invaders       the 2d array of Invader struct objects
//----------------------------------------------------------------------------------------------------------------------
void initializeInvaders(Invader o_invaders[ROWS][COLS]);

//----------------------------------------------------------------------------------------------------------------------
/// \brief updateInvaders
/// \param io_invaders  the 2d array of Invader struct objects
/// \param io_missiles  the array of Missile structs (each can be of four different types)
/// \param io_freeze    if freeze==1 the invaders do no move their position.
///                     I will also update freeze.
///                     However if I update freeze directly, in middle of iterating through
///                     invaders the rest of the invaders will be ofset from the others so
///                     I use a new variable: freezelagfix. I assign freeze to freezelagfix
///                     at bottom of updateinvaders function.
/// \param io_howfast   the lower howfast is, the faster the invaders move
/// \param _startscreen if startscreen==1 then the invader's y position is not incremented
//----------------------------------------------------------------------------------------------------------------------
void updateInvaders(Invader io_invaders[ROWS][COLS], Missile io_missiles[MISSILESNUMBER], \
                    int *io_freeze, int *io_howfast, int _startscreen);

//----------------------------------------------------------------------------------------------------------------------
/// \param invaders the 2d array of Invader struct objects
/// \return the number of active invaders
//----------------------------------------------------------------------------------------------------------------------
int howManyActive(Invader invaders[ROWS][COLS]);


#endif
