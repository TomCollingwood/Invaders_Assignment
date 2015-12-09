#include "drawText.h"

void drawText(SDL_Renderer *ren, SDL_Texture *tex, char text[], int x, int y, float multiplier){
  int xoffset=0;
  SDL_Rect SrcR;
  int nochar=0;
  for(int i=0; i<(int)strlen(text); i++){
    switch(text[i])
    {
    case 'A':
      SrcR.x=0;
      SrcR.y=132;
      SrcR.w=15;
      SrcR.h=21;
      break;
    case 'B':
      SrcR.x=21;
      SrcR.y=132;
      SrcR.w=15;
      SrcR.h=21;
      break;
    case 'C':
      SrcR.x=42;
      SrcR.y=132;
      SrcR.w=15;
      SrcR.h=21;
      break;
    case 'D':
      SrcR.x=63;
      SrcR.y=132;
      SrcR.w=15;
      SrcR.h=21;
      break;
    case 'E':
      SrcR.x=84;
      SrcR.y=132;
      SrcR.w=15;
      SrcR.h=21;
      break;
    case 'F':
      SrcR.x=105;
      SrcR.y=132;
      SrcR.w=15;
      SrcR.h=21;
      break;
    case 'G':
      SrcR.x=126;
      SrcR.y=132;
      SrcR.w=15;
      SrcR.h=21;
      break;
    case 'H':
      SrcR.x=147;
      SrcR.y=132;
      SrcR.w=15;
      SrcR.h=21;
      break;
    case 'I':
      SrcR.x=168;
      SrcR.y=132;
      SrcR.w=9;
      SrcR.h=21;
      break;
    case 'J':
      SrcR.x=0;
      SrcR.y=156;
      SrcR.w=15;
      SrcR.h=21;
      break;
    case 'K':
      SrcR.x=21;
      SrcR.y=156;
      SrcR.w=15;
      SrcR.h=21;
      break;
    case 'L':
      SrcR.x=42;
      SrcR.y=156;
      SrcR.w=15;
      SrcR.h=21;
      break;
    case 'M':
      SrcR.x=63;
      SrcR.y=156;
      SrcR.w=15;
      SrcR.h=21;
      break;
    case 'N':
      SrcR.x=84;
      SrcR.y=156;
      SrcR.w=15;
      SrcR.h=21;
      break;
    case 'O':
      SrcR.x=105;
      SrcR.y=156;
      SrcR.w=15;
      SrcR.h=21;
      break;
    case 'P':
      SrcR.x=126;
      SrcR.y=156;
      SrcR.w=15;
      SrcR.h=21;
      break;
    case 'Q':
      SrcR.x=147;
      SrcR.y=156;
      SrcR.w=15;
      SrcR.h=21;
      break;
    case 'R':
      SrcR.x=0;
      SrcR.y=180;
      SrcR.w=15;
      SrcR.h=21;
      break;
    case 'S':
      SrcR.x=21;
      SrcR.y=180;
      SrcR.w=15;
      SrcR.h=21;
      break;
    case 'T':
      SrcR.x=42;
      SrcR.y=180;
      SrcR.w=15;
      SrcR.h=21;
      break;
    case 'U':
      SrcR.x=63;
      SrcR.y=180;
      SrcR.w=15;
      SrcR.h=21;
      break;
    case 'V':
      SrcR.x=84;
      SrcR.y=180;
      SrcR.w=15;
      SrcR.h=21;
      break;
    case 'W':
      SrcR.x=105;
      SrcR.y=180;
      SrcR.w=15;
      SrcR.h=21;
      break;
    case 'X':
      SrcR.x=126;
      SrcR.y=180;
      SrcR.w=15;
      SrcR.h=21;
      break;
    case 'Y':
      SrcR.x=147;
      SrcR.y=180;
      SrcR.w=15;
      SrcR.h=21;
      break;
    case 'Z':
      SrcR.x=168;
      SrcR.y=180;
      SrcR.w=15;
      SrcR.h=21;
      break;
    case ' ':
      SrcR.x=144;
      SrcR.y=54;
      SrcR.w=6;
      SrcR.h=21;
      break;
    case '-':
      SrcR.x=0;
      SrcR.y=204;
      SrcR.w=15;
      SrcR.h=21;
      break;
    case '<':
      SrcR.x=21;
      SrcR.y=204;
      SrcR.w=15;
      SrcR.h=21;
      break;
    case '>':
      SrcR.x=42;
      SrcR.y=204;
      SrcR.w=15;
      SrcR.h=21;
      break;
    case '*':
      SrcR.x=63;
      SrcR.y=204;
      SrcR.w=15;
      SrcR.h=21;
      break;
    case '?':
      SrcR.x=84;
      SrcR.y=204;
      SrcR.w=15;
      SrcR.h=21;
      break;
    case '=':
      SrcR.x=105;
      SrcR.y=204;
      SrcR.w=15;
      SrcR.h=21;
      break;
    case '0':
      SrcR.x=126;
      SrcR.y=204;
      SrcR.w=15;
      SrcR.h=21;
      break;
    case '1':
      SrcR.x=147;
      SrcR.y=204;
      SrcR.w=15;
      SrcR.h=21;
      break;
    case '2':
      SrcR.x=168;
      SrcR.y=204;
      SrcR.w=15;
      SrcR.h=21;
      break;
    case '3':
      SrcR.x=0;
      SrcR.y=228;
      SrcR.w=15;
      SrcR.h=21;
      break;
    case '4':
      SrcR.x=21;
      SrcR.y=228;
      SrcR.w=15;
      SrcR.h=21;
      break;
    case '5':
      SrcR.x=42;
      SrcR.y=228;
      SrcR.w=15;
      SrcR.h=21;
      break;
    case '6':
      SrcR.x=63;
      SrcR.y=228;
      SrcR.w=15;
      SrcR.h=21;
      break;
    case '7':
      SrcR.x=84;
      SrcR.y=228;
      SrcR.w=15;
      SrcR.h=21;
      break;
    case '8':
      SrcR.x=105;
      SrcR.y=228;
      SrcR.w=15;
      SrcR.h=21;
      break;
    case '9':
      SrcR.x=126;
      SrcR.y=228;
      SrcR.w=15;
      SrcR.h=21;
      break;
    case 'd':
      SrcR.x=141;
      SrcR.y=228;
      SrcR.w=21;
      SrcR.h=12;
      break;
    case 'u':
      SrcR.x=162;
      SrcR.y=228;
      SrcR.w=21;
      SrcR.h=12;
      break;
    case '!':
      SrcR.x=168;
      SrcR.y=156;
      SrcR.w=9;
      SrcR.h=21;
      break;
    default:
      nochar = 1;
      break;
    }

    if(nochar==0)
    {
      SDL_Rect letter;
      letter.x = x + xoffset;
      letter.y = y;
      letter.w = SrcR.w*multiplier;
      letter.h = SrcR.h*multiplier;
      xoffset += SrcR.w*multiplier + 6;
      SDL_RenderCopy(ren,tex,&SrcR,&letter);
    }
    else
    {
      nochar=0;
    }
  }

}
