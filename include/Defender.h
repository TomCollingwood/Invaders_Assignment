/// \file Defender.h
/// \brief structure for Defender - the object the player controls and shoots from
/// \author Thomas Collingwood
/// \version 1.0
/// \date 9/12/15 Updated to NCCA Coding standard
/// Revision History :
/// Initial Version 19/11/15
/// \todo

#ifndef DEFENDER_H__
#define DEFENDER_H__

#include <SDL.h>
#include <SDL_image.h>

#include "Invader.h"

#define DEFENDERWIDTH 39
#define DEFENDERHEIGHT 24
#define EXPLODEDDEFENDERWIDTH 48

typedef struct
{
  SDL_Rect pos;
  int active;
  int sprite;
  enum DIR direction;
  int frame;
}Defender;

#endif
