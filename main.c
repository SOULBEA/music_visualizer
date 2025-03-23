#include<stdio.h>
#include<unistd.h>
#include<raylib.h>
#include<assert.h>
#include<string.h>
#include<stdint.h>
#include<stdlib.h>

#define ARRAY_LEN(xs) sizeof(xs)/sizeof(xs[0])

uint32_t global_frames[1024] = {0};
size_t global_frames_count = 0;

void callback(void *bufferData, unsigned int frames){
  if (frames > ARRAY_LEN(global_frames)){
    frames = ARRAY_LEN(global_frames);
  }
  memcpy(global_frames, bufferData, sizeof(int32_t)*frames*2);
  global_frames_count = frames;
}
int main(void){
  // create window and initialize audio device
  InitWindow(800, 600, "music");
  InitAudioDevice();
  Music music= LoadMusicStream("C:\\Users\\Arpit Singh\\music_visualizer\\last of us.ogg"); // loading music
  assert(music.stream.sampleSize == 16);
  assert(music.stream.channels == 2);
  printf("muisc.frameCount = %u\n", music.frameCount);
  printf("music.stream.sampleRate = %u\n", music.stream.sampleRate);
  printf("music.stream.channels = %u\n", music.stream.channels);
  PlayMusicStream(music);
  AttachAudioStreamProcessor(music.stream, callback);
  while(!WindowShouldClose()){
    if(IsKeyPressed(KEY_SPACE)){
      if(IsMusicStreamPlaying(music)){
        PauseMusicStream(music);
      }
      else{
        ResumeMusicStream(music);
      }
    }
    int w = GetRenderWidth();
    int h = GetRenderHeight();
    UpdateMusicStream(music);
    BeginDrawing();
    ClearBackground(CLITERAL(Color) {0x18, 0x18, 0x18, 0xFF});
      float cell_widht = (float)w/global_frames_count;
      for(size_t i = 0; i<global_frames_count; ++i){
        int16_t sample = *(int16_t*)&global_frames[i];
        if(sample>0){
          float t = (float)sample/INT16_MAX;
          DrawRectangle(i*cell_widht, h/2 - h/2*t, cell_widht, h/2*t, RED);
        }else{
          float t = (float)sample/INT16_MIN;
          DrawRectangle(i*cell_widht, h/2, cell_widht, h/2*t, RED);
        }
      }
      //if(global_frames_count>0) exit(1);
    EndDrawing();
  }
  return 0;
}
