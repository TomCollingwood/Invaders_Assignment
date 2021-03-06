/// \file Invader.h
/// \brief struct for Invader
/// \author Jon Macey & Thomas Collingwood
/// \version 1.0
/// \date 9/12/15 Updated to NCCA Coding standard

#ifndef INVADER_H__
#define INVADER_H__

#include <SDL.h>
#include <SDL_image.h>

enum InvaderType{TYPE1,TYPE2,TYPE3,EXPLOSION};
enum DIR{FWD,BWD,DWNFWD,DWNBWD,UP,DOWN};

#define SPRITEWIDTH 36
#define SPRITEHEIGHT 24
#define COLS 11
#define ROWS 5
#define GAP 12

typedef struct
{
  SDL_Rect pos;
  int active;
  int frame;
  int sprite;
  enum DIR direction;
  enum InvaderType type;
  int explosionframe; /**< if 1 then invader is exploding */
  int bottom; /**< if 1 then invader is at bottom of column and can shoot */
}Invader;

#endif
