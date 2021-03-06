#include "messagebox.h"
#include <iostream>
#include <string>

MessageBox::MessageBox()
{
  colorScheme = {
    {
      {100, 100, 255},  /* [SDL_MESSAGEBOX_COLOR_BACKGROUND] */
      {0, 0, 0},      /* [SDL_MESSAGEBOX_COLOR_TEXT] */
      {255, 255, 0},    /* [SDL_MESSAGEBOX_COLOR_BUTTON_BORDER] */
      {255, 255, 255}     /* [SDL_MESSAGEBOX_COLOR_BUTTON_SELECTED] */
    }
  };
}

int MessageBox::ShowStartScreen()
{
  SDL_MessageBoxButtonData buttons[] = {
    { SDL_MESSAGEBOX_BUTTON_RETURNKEY_DEFAULT, 0, "Start" },
    { SDL_MESSAGEBOX_BUTTON_ESCAPEKEY_DEFAULT, 1, "Quit" },
  };

  std::string msg = "This game is for Udacity C++ Capstone project:). \nYou can play this game for 60 seconds.";

  message_box_data = {
    SDL_MESSAGEBOX_INFORMATION,
    NULL,
    "Start Snake Game",
    msg.c_str(),
    SDL_arraysize(buttons),
    buttons,
    &colorScheme
  };

  int buttonid;
  if (SDL_ShowMessageBox(&message_box_data, &buttonid) < 0) {
    SDL_Log("error displaying message box");
    return -1;
  }
  if (buttonid == -1) {
    SDL_Log("no selection");
  } else {
    SDL_Log("selection was %s", buttons[buttonid].text);
    std::cout << "selectied buttonid was " << buttonid << "\n";
    std::cout << "selection was " << buttons[buttonid].text << "\n";
  }

  return buttonid;
}

int MessageBox::ShowContinueScreen()
{
  SDL_MessageBoxButtonData buttons[] = {
    { SDL_MESSAGEBOX_BUTTON_RETURNKEY_DEFAULT, 0, "Continue" },
    { SDL_MESSAGEBOX_BUTTON_ESCAPEKEY_DEFAULT, 1, "Quit" },
  };

  std::string msg = "Your snake died! Continue?";

  message_box_data = {
    SDL_MESSAGEBOX_INFORMATION,
    NULL,
    "Gemeover",
    msg.c_str(),
    SDL_arraysize(buttons),
    buttons,
    &colorScheme
  };

  int buttonid;
  if (SDL_ShowMessageBox(&message_box_data, &buttonid) < 0) {
    SDL_Log("error displaying message box");
    return -1;
  }
  if (buttonid == -1) {
    SDL_Log("no selection");
  } else {
    SDL_Log("selection was %s", buttons[buttonid].text);
    std::cout << "selectied buttonid was " << buttonid << "\n";
    std::cout << "selection was " << buttons[buttonid].text << "\n";
  }

  return buttonid;
}