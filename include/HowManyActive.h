/// \file HowManyActive.h
/// \brief returns int of how many invaders active
/// \author Thomas Collingwood
/// \version 1.0
/// \date 9/12/15 Updated to NCCA Coding standard

#include <stdio.h>
#include <stdlib.h>

#include "Invader.h"

///
/// \param invaders the 2d array of Invader struct objects
/// \return the number of active invaders
///
int howManyActive(Invader invaders[ROWS][COLS]);
