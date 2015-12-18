/// \file SelectLetter.h
/// \brief deals with character switching when inputting your name for new highscore
/// \author Thomas Collingwood
/// \version 1.0
/// \date 9/12/15 Updated to NCCA Coding standard

#ifndef _SELECTLETTER_H_
#define _SELECTLETTER_H_

#include <SDL.h>
#include <SDL_image.h>
#include <stdio.h>
#include <stdlib.h>

#include "Direction.h"
#include "DrawText.h"

///
/// \brief selectLetter
/// \param asciinumber the current asciinumber to be incremented/decremented/left alone
/// \param input this is the
/// \param previousinput This is the input prior to the current input.
/// having this means that the asciinumber is only incremented once for one keydown
/// for example: when input==UPS and previousinput==NONE : increment asciinumber and return it
/// \return the incremented/decremented/same asciinumber
///
void selectLetter(int *asciinumber, enum DIRECTION input, enum DIRECTION previousinput);

#endif
