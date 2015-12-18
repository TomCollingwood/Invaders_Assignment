/// \file UpdateDefender.h
/// \brief updates defender position depending on input - also updates sprite when exploded
/// \author Thomas Collingwood
/// \version 1.0
/// \date 9/12/15 Updated to NCCA Coding standard

#ifndef _UPDATEDEFENDER_H_
#define _UPDATEDEFENDER_H_

#include <stdio.h>
#include <stdlib.h>

#include "Defender.h"
#include "Dimensions.h"
#include "Direction.h"
#include "Missile.h"

///
/// \brief updateDefender
/// \param defender the player controlled object that fires at space invaders
/// \param input the input from the player
/// \param missiles the array of Missile structs (each can be of four different types)
/// \param freeze if freeze==1 a new missile cannot be fired from defender
///
void updateDefender(Defender *defender, enum DIRECTION input, Missile missiles[], int *freeze);

#endif
