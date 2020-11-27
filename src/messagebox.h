#ifndef MESSAGEBOX_H
#define MESSAGEBOX_H

#include "SDL.h"

class MessageBox
{
  public:
    MessageBox();
    int ShowScreen();

  private:
    SDL_MessageBoxColorScheme colorScheme;
    SDL_MessageBoxData message_box_data;
};

#endif