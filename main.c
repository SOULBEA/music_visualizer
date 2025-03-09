#include<stdio.h>
#include"raylib.h"

int main(void){
  InitAudioDevice();
  Sound sound = LoadSound("last of us.mp3");
  PlaySound(sound);
 // printf("hello world");
  return 0;
}
