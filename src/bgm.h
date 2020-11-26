#ifndef BGM_H
#define BGM_H

#include <string>
#include "SDL.h"
#include "SDL_mixer.h"

class Bgm
{
  public:
    Bgm(const char *file_path);
    void PlayBgm();
    void StopBgm();

  private:
    Mix_Music *backgroundSound;
};

#endif