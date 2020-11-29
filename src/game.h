#ifndef GAME_H
#define GAME_H

#include <random>
#include "SDL.h"
#include "controller.h"
#include "renderer.h"
#include "snake.h"
#include "bgm.h"
#include "messagebox.h"

class Game {
 public:
  Game(std::size_t grid_width, std::size_t grid_height);
  void Run(Controller &controller, Renderer &renderer,
           Bgm &bgm, MessageBox &messagebox,
           std::size_t target_frame_duration);
  int GetScore() const;
  int GetSize() const;
  int GetCount();

 private:
  Snake snake;
  SDL_Point food;
  SDL_Point obstacle;

  std::random_device dev;
  std::mt19937 engine;
  std::uniform_int_distribution<int> random_w;
  std::uniform_int_distribution<int> random_h;

  int score{0};

  void PlaceFood();
  void PlaceObstacle();
  void Update(Controller &controller, Renderer &renderer);
};

#endif