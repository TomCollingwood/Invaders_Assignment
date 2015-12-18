///
///  @file SelectLetter.c
///  @brief deals with character switching when inputting your name for new highscore

#include "include/SelectLetter.h"

void selectLetter(int *asciinumber, enum DIRECTION input, enum DIRECTION previousinput)
{
  if(input==UPS && previousinput!=UPS) {(*asciinumber)++;}
  else if(input==DOWNS && previousinput!=DOWNS) {(*asciinumber)--;}

  // the below else ifs below skip lots of letters that are unused by drawText
  // also creates a loop ...->A->...->Z->0->...->9->A->...
  if((*asciinumber)==91) { (*asciinumber)=48; }
  else if((*asciinumber)==58) { (*asciinumber)=65; }
  else if((*asciinumber)==64) { (*asciinumber)=57; }
  else if((*asciinumber)==47) { (*asciinumber)=90; }
}
