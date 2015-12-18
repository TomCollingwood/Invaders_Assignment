/// \file Missile.h
/// \brief struct for missile
/// \author Thomas Collingwood
/// \version 1.0
/// \date 9/12/15 Updated to NCCA Coding standard

#ifndef MISSILE_H__
#define MISSILE_H__

#include "Invader.h"

#define MISSILESNUMBER 5

enum MissileType{DEFENDER,LETTERT,ZIGZAG,SNAKE};

typedef struct
{
  SDL_Rect pos;
  int active;
  int frame;
  enum MissileType type;
  enum DIR dir;
  int sprite;
}Missile;

#endif
