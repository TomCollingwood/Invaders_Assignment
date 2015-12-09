/// \file BlastBarrier.h
/// \brief updates a barriers to have a crater
/// \author Thomas Collingwood
/// \version 1.0
/// \date 9/12/15 Updated to NCCA Coding standard
/// Revision History :
/// Initial Version 9/12/15
/// \todo

#ifndef _BLASTBARRIER_H_
#define _BLASTBARRIER_H_

#include <stdio.h>
#include <stdlib.h>

#include "InitializeBarriers.h"

void blastBarrier(int barriers[4][BARRIERHEIGHT][BARRIERWIDTH],int barrier, int x, int y, int type);

#endif
