///
///  @file Missile.h
///  @brief Contains the structure for Missile

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
