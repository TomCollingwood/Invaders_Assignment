#ifndef MISSILE_H__
#define MISSILE_H__

#define MISSILESNUMBER 5

enum MissileType{DEFENDER,LETTERT,ZIGZAG,SNAKE};
enum MISSILEDIR{UP,DOWN};

typedef struct
{
  SDL_Rect pos;
  int active;
  int frame;
  enum MissileType type;
  enum MISSILEDIR dir;
  int sprite;
}Missile;

#endif
