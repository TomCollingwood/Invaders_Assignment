#ifndef INVADER_H__
#define INVADER_H__

enum InvaderType{TYPE1,TYPE2,TYPE3,EXPLOSION};
enum DIR{FWD,BWD,DWNFWD,DWNBWD,UP,DOWN};

#define SPRITEWIDTH 36
#define SPRITEHEIGHT 24
#define COLS 11
#define ROWS 5
#define GAP 12

#include <SDL.h>
#include <SDL_image.h>
#include "dir.h"

typedef struct
{
  SDL_Rect pos;
  int active;
  int frame;
  int sprite;
  enum DIR direction;
  enum InvaderType type;
  int explosionframe;
  int bottom;
}Invader;

#endif
