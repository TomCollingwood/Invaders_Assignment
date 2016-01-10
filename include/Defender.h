/// \file Defender.h
/// \brief structure for Defender - the object the player controls and shoots from
/// \author Jon Macey & Thomas Collingwood
/// \version 1.0
/// \date 9/12/15 Updated to NCCA Coding standard

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
  SDL_Rect pos;   /**< SDL_Rect containing defender's position and dimensions 1 */
  int active;     /**< if 1 then defender can move and has undestroyed sprite */
  int sprite;     /**< determines which sprite to display for drawDefender */
  int frame;      /**< is used for alternating between destroyed sprites */
}Defender;

#endif
