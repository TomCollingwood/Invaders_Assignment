#ifndef DEFENDER_H__
#define DEFENDER_H__

#define DEFENDERWIDTH 39
#define DEFENDERHEIGHT 24
#define EXPLODEDDEFENDERWIDTH 48

#include <SDL.h>
#include <SDL_image.h>
#include "Invader.h"

typedef struct
{
  SDL_Rect pos;
  int active;
  int sprite;
  enum DIR direction;
  int frame;
}Defender;

#endif
