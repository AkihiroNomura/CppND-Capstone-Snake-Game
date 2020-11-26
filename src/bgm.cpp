#include <iostream>
#include <string>
#include "bgm.h"

Bgm::Bgm(const char *file_path)
{
  if (SDL_Init(SDL_INIT_AUDIO) < 0)
  {
    std::cerr << "SDL Audio could not initialize.\n";
    std::cerr << "SDL_Error: " << SDL_GetError() << "\n";
  }

  if (Mix_OpenAudio(44100, MIX_DEFAULT_FORMAT, 2, 2048) < 0)
  {
    std::cout << "failed to open audio: " << Mix_GetError() << "\n";
  }

  backgroundSound = Mix_LoadMUS(file_path);
  if (!backgroundSound)
  {
    std::cout << "failed to load music: " << Mix_GetError() << "\n";
  }
}

void Bgm::PlayBgm()
{
  Mix_PlayMusic(backgroundSound, -1);
}

void Bgm::StopBgm()
{
  Mix_FreeMusic(backgroundSound);
  Mix_CloseAudio();
}