#include <iostream>
#include "controller.h"
#include "game.h"
#include "renderer.h"
#include "bgm.h"

#define BGM_PATH "../music/bgm_maoudamashii_8bit07.wav"

int main() {
  constexpr std::size_t kFramesPerSecond{60};
  constexpr std::size_t kMsPerFrame{1000 / kFramesPerSecond};
  constexpr std::size_t kScreenWidth{640};
  constexpr std::size_t kScreenHeight{640};
  constexpr std::size_t kGridWidth{32};
  constexpr std::size_t kGridHeight{32};

  Renderer renderer(kScreenWidth, kScreenHeight, kGridWidth, kGridHeight);
  Controller controller;
  Bgm bgm(BGM_PATH);
  Game game(kGridWidth, kGridHeight);
  game.Run(controller, renderer, bgm, kMsPerFrame);
  std::cout << "Game has terminated successfully!\n";
  std::cout << "Score: " << game.GetScore() << "\n";
  std::cout << "Size: " << game.GetSize() << "\n";
  return 0;
}