/// \file InitializeDefender.h
/// \brief initializes the input defender to active state and original position
/// \author Thomas Collingwood
/// \version 1.0
/// \date 9/12/15 Updated to NCCA Coding standard

#ifndef _INITIALIZEDEFENDER_H_
#define _INITIALIZEDEFENDER_H_

#include <stdio.h>
#include <stdlib.h>

#include "Defender.h"
#include "Dimensions.h"

///
/// \brief initializeDefender
/// \param defender the player controlled object that fires at space invaders
///
void initializeDefender(Defender *defender);

#endif
