///
///  @file UpdateDefender.h
///  @brief Header file for UpdateDefender.c

#ifndef _UPDATEDEFENDER_H_
#define _UPDATEDEFENDER_H_

#include <stdio.h>
#include <stdlib.h>

#include "Defender.h"
#include "Direction.h"
#include "Missile.h"

void updateDefender(Defender *defender, enum DIRECTION input, Missile missiles[], int *freeze);

#endif
