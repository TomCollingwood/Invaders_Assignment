#ifndef MISSILE_H__
#define MISSILE_H__

#define MISSILESNUMBER 5

#include "invader.h"

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
