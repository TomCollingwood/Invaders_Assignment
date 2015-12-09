#include <stdio.h>
#include <stdlib.h>
#include "Missile.h"
#include "Defender.h"
#include "direction.h"

void updateDefender(Defender *defender, enum DIRECTION input, Missile missiles[], int *freeze);
