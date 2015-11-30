#include <SDL.h>
#include <SDL_image.h>
#include <stdio.h>
#include <stdlib.h>

void drawText(SDL_Renderer *ren, SDL_Texture *tex, char text[], int x, int y, float multiplier){
  int xoffset=0;
  SDL_Rect SrcR;
  int nochar=0;
  for(int i=0; i<(int)strlen(text); i++){
    switch(text[i])
    {
    case 'a':
    case 'A':
      SrcR.x=0;
      SrcR.y=132;
      SrcR.w=15;
      SrcR.h=21;
      break;
    case 'b':
    case 'B':
      SrcR.x=21;
      SrcR.y=132;
      SrcR.w=15;
      SrcR.h=21;
      break;
    case 'c':
    case 'C':
      SrcR.x=42;
      SrcR.y=132;
      SrcR.w=15;
      SrcR.h=21;
      break;
    case 'd':
    case 'D':
      SrcR.x=63;
      SrcR.y=132;
      SrcR.w=15;
      SrcR.h=21;
      break;
    case 'e':
    case 'E':
      SrcR.x=84;
      SrcR.y=132;
      SrcR.w=15;
      SrcR.h=21;
      break;
    case 'f':
    case 'F':
      SrcR.x=105;
      SrcR.y=132;
      SrcR.w=15;
      SrcR.h=21;
      break;
    case 'g':
    case 'G':
      SrcR.x=126;
      SrcR.y=132;
      SrcR.w=15;
      SrcR.h=21;
      break;
    case 'h':
    case 'H':
      SrcR.x=147;
      SrcR.y=132;
      SrcR.w=15;
      SrcR.h=21;
      break;
    case 'i':
    case 'I':
      SrcR.x=168;
      SrcR.y=132;
      SrcR.w=9;
      SrcR.h=21;
      break;
    case 'j':
    case 'J':
      SrcR.x=0;
      SrcR.y=156;
      SrcR.w=15;
      SrcR.h=21;
      break;
    case 'k':
    case 'K':
      SrcR.x=21;
      SrcR.y=156;
      SrcR.w=15;
      SrcR.h=21;
      break;
    case 'l':
    case 'L':
      SrcR.x=42;
      SrcR.y=156;
      SrcR.w=15;
      SrcR.h=21;
      break;
    case 'm':
    case 'M':
      SrcR.x=63;
      SrcR.y=156;
      SrcR.w=15;
      SrcR.h=21;
      break;
    case 'n':
    case 'N':
      SrcR.x=84;
      SrcR.y=156;
      SrcR.w=15;
      SrcR.h=21;
      break;
    case 'o':
    case 'O':
      SrcR.x=105;
      SrcR.y=156;
      SrcR.w=15;
      SrcR.h=21;
      break;
    case 'p':
    case 'P':
      SrcR.x=126;
      SrcR.y=156;
      SrcR.w=15;
      SrcR.h=21;
      break;
    case 'q':
    case 'Q':
      SrcR.x=147;
      SrcR.y=156;
      SrcR.w=15;
      SrcR.h=21;
      break;
    case 'r':
    case 'R':
      SrcR.x=0;
      SrcR.y=180;
      SrcR.w=15;
      SrcR.h=21;
      break;
    case 's':
    case 'S':
      SrcR.x=21;
      SrcR.y=180;
      SrcR.w=15;
      SrcR.h=21;
      break;
    case 't':
    case 'T':
      SrcR.x=42;
      SrcR.y=180;
      SrcR.w=15;
      SrcR.h=21;
      break;
    case 'u':
    case 'U':
      SrcR.x=63;
      SrcR.y=180;
      SrcR.w=15;
      SrcR.h=21;
      break;
    case 'v':
    case 'V':
      SrcR.x=84;
      SrcR.y=180;
      SrcR.w=15;
      SrcR.h=21;
      break;
    case 'w':
    case 'W':
      SrcR.x=105;
      SrcR.y=180;
      SrcR.w=15;
      SrcR.h=21;
      break;
    case 'x':
    case 'X':
      SrcR.x=126;
      SrcR.y=180;
      SrcR.w=15;
      SrcR.h=21;
      break;
    case 'y':
    case 'Y':
      SrcR.x=147;
      SrcR.y=180;
      SrcR.w=15;
      SrcR.h=21;
      break;
    case 'z':
    case 'Z':
      SrcR.x=168;
      SrcR.y=180;
      SrcR.w=15;
      SrcR.h=21;
      break;
    case ' ':
      SrcR.x=168;
      SrcR.y=156;
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
    default:
      nochar = 1;
      break;
    }

    if(nochar==0){
      SDL_Rect letter;
      letter.x = x + xoffset;
      letter.y = y;
      letter.w = SrcR.w*multiplier;
      letter.h = SrcR.h*multiplier;
      xoffset += SrcR.w*multiplier + 6;
      SDL_RenderCopy(ren,tex,&SrcR,&letter);
    }
    else{
      nochar=0;
    }
  }

}
