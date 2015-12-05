#include <SDL.h>
#include <SDL_image.h>
#include <stdio.h>
#include <stdlib.h>
#include "drawText.h"
#include "direction.h"

int selectLetter(int asciinumber, enum DIRECTION input, enum DIRECTION previousinput){
  char result=asciinumber;
  if((asciinumber>64 && asciinumber<90) || (asciinumber>47 && asciinumber<57)){
    if(input==UPS && previousinput!=UPS) result++;
    else if(input==DOWNS && previousinput!=DOWNS) result--;
  }
  else if(asciinumber==90){
    if(input==UPS && previousinput!=UPS) result=48;
    else if (input==DOWNS && previousinput!=DOWNS) result--;
  }
  else if(asciinumber==57){
    if(input==UPS && previousinput!=UPS) result=65;
    else if(input==DOWNS && previousinput!=DOWNS) result--;
  }
  else{
    result=65;
  }
  return result;
}
