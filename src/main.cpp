#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include "controller.h"
#include "game.h"
#include "renderer.h"
#include "bgm.h"
#include "messagebox.h"

#define BGM_PATH "../music/bgm_maoudamashii_8bit07.wav"
#define HISTORY_FILE_PATH "../history.txt"

std::string GetCurrentTime()
{
  time_t t = time(nullptr);
  const tm* lt = localtime(&t);

  std::stringstream ss;
  ss << "20" << lt->tm_year-100;
  ss << "/";
  ss << lt->tm_mon+1;
  ss << "/";
  ss << lt->tm_mday;
  ss << " ";
  ss << lt->tm_hour;
  ss << ":";
  ss << lt->tm_min;
  ss << ":";
  ss << lt->tm_sec;

  return ss.str();
}

void WriteHistory(int score, int size, const char *file_path)
{
  std::ofstream writing_file(file_path);
  if (!writing_file.is_open()) {
    std::cout << "Cloud not open file..." << "\n";
  }
  writing_file << "Time: " << GetCurrentTime() << "\n";
  writing_file << "Score: " << score << "\n";
  writing_file << "Size: " << size << "\n";
  writing_file.close();
}

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
  MessageBox messagebox;
  Game game(kGridWidth, kGridHeight);
  game.Run(controller, renderer, bgm, messagebox, kMsPerFrame);

  WriteHistory(game.GetScore(), game.GetSize(), HISTORY_FILE_PATH);

  std::cout << "Game has terminated successfully!\n";
  std::cout << "Score: " << game.GetScore() << "\n";
  std::cout << "Size: " << game.GetSize() << "\n";
  return 0;
}