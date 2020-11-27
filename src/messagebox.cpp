#include "messagebox.h"
#include <iostream>

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

int MessageBox::ShowScreen()
{
  SDL_MessageBoxButtonData buttons[] = {
    { SDL_MESSAGEBOX_BUTTON_RETURNKEY_DEFAULT, 0, "Start" },
    { SDL_MESSAGEBOX_BUTTON_ESCAPEKEY_DEFAULT, 1, "Quit" },
  };

  message_box_data = {
    SDL_MESSAGEBOX_INFORMATION,
    NULL,
    "Start",
    "Press button",
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