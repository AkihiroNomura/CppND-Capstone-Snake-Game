#include "game.h"
#include <iostream>
#include <thread>
#include <atomic>
#include "SDL.h"

struct thread_aborted{};
std::atomic<bool> exit_flag(false);
int count{60};

void CheckExitFlag() {
  if (exit_flag) throw thread_aborted{};
}

void StopCountdownTimerThread() {
  exit_flag = true;
}

void CountdownTimer60Seconds(bool &running)
{
  try {
    std::cout << "-------- Start Timer --------\n";
    while (count > 0)
    {
      std::this_thread::sleep_for(std::chrono::milliseconds(1000));
      // std::cout << count << "\n";
      count--;
      CheckExitFlag();
    }
    std::cout << "-------- End Timer --------\n";
    running = false;
  } catch (thread_aborted &e) {
    std::cout << "You have forced the game to quit by pressing Ctrl+C." << "\n";
  }
}

Game::Game(std::size_t grid_width, std::size_t grid_height)
    : snake(grid_width, grid_height),
      engine(dev()),
      random_w(0, static_cast<int>(grid_width)),
      random_h(0, static_cast<int>(grid_height)) {
  PlaceFood();
  PlaceObstacle();
}

void Game::Run(Controller &controller, Renderer &renderer,
               Bgm &bgm, MessageBox &messagebox,
               std::size_t target_frame_duration) {
  Uint32 title_timestamp = SDL_GetTicks();
  Uint32 frame_start;
  Uint32 frame_end;
  Uint32 frame_duration;
  int frame_count = 0;
  bool running = true;

  int pressed_button_number = messagebox.ShowStartScreen();
  if (pressed_button_number != 0) return;

  bgm.PlayBgm();
  std::thread t1(CountdownTimer60Seconds, std::ref(running));

  while (running) {
    frame_start = SDL_GetTicks();

    // Input, Update, Render - the main game loop.
    controller.HandleInput(running, snake);
    Update(controller, renderer);
    renderer.Render(snake, food, obstacle, count);

    if (!snake.alive)
    {
      int pressed_button_number = messagebox.ShowContinueScreen();
      if (pressed_button_number == 1) break;
      if (pressed_button_number == 0) {
        PlaceFood();
        PlaceObstacle();
        snake.alive = true;
      }
    }

    frame_end = SDL_GetTicks();

    // Keep track of how long each loop through the input/update/render cycle
    // takes.
    frame_count++;
    frame_duration = frame_end - frame_start;

    // After every second, update the window title.
    if (frame_end - title_timestamp >= 1000) {
      renderer.UpdateWindowTitle(score, frame_count);
      frame_count = 0;
      title_timestamp = frame_end;
    }

    // If the time for this frame is too small (i.e. frame_duration is
    // smaller than the target ms_per_frame), delay the loop to
    // achieve the correct frame rate.
    if (frame_duration < target_frame_duration) {
      SDL_Delay(target_frame_duration - frame_duration);
    }
  }

  StopCountdownTimerThread();
  t1.join();
  bgm.StopBgm();
}

void Game::PlaceFood() {
  int x, y;
  while (true) {
    x = random_w(engine);
    y = random_h(engine);
    // Check that the location is not occupied by a snake item before placing
    // food.
    if (!snake.SnakeCell(x, y)) {
      food.x = x;
      food.y = y;
      return;
    }
  }
}

void Game::PlaceObstacle() {
  int x, y;
  while (true) {
    x = random_w(engine);
    y = random_h(engine);
    if (!snake.SnakeCell(x, y) && food.x != x && food.y != y) {
      obstacle.x = x;
      obstacle.y = y;
      return;
    }
  }
}

void Game::Update(Controller &controller, Renderer &renderer) {
  if (!snake.alive) return;

  if (controller.IsPaused())
  {
    std::this_thread::sleep_for(std::chrono::milliseconds(100));
    renderer.UpdateWindowTitleForPausing();
    return;
  }

  snake.Update();

  int new_x = static_cast<int>(snake.head_x);
  int new_y = static_cast<int>(snake.head_y);

  // Check if there's obstacle over here
  if (obstacle.x == new_x && obstacle.y == new_y) {
    snake.alive = false;
  }

  // Check if there's food over here
  if (food.x == new_x && food.y == new_y) {
    score++;
    PlaceFood();
    PlaceObstacle();
    // Grow snake and increase speed.
    snake.GrowBody();
    snake.speed += 0.02;
  }
}

int Game::GetScore() const { return score; }
int Game::GetSize() const { return snake.size; }
int Game::GetCount() { return count; }