/// \file UpdateMissiles.h
/// \brief updates all the active missiles' position
/// \author Thomas Collingwood
/// \version 1.0
/// \date 9/12/15 Updated to NCCA Coding standard

#ifndef _UPDATEMISSILES_H_
#define _UPDATEMISSILES_H_

#include <stdio.h>
#include <stdlib.h>

#include "Dimensions.h"
#include "Missile.h"

///
/// \brief updateMissiles
/// \param missiles the array of Missile structs (each can be of four different types)
///
void updateMissiles(Missile missiles[]);

#endif
