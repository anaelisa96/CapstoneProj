#ifndef GAME_H
#define GAME_H

#include <random>
#include <thread>
#include "SDL.h"
#include "controller.h"
#include "renderer.h"
#include "snake.h"

// Add
#include "welcomeScreen.h"

class Game {
 public:
  Game(std::size_t screen_width, std::size_t screen_height, std::size_t grid_width, std::size_t grid_height,
           std::shared_ptr<std::string> welcome, std::shared_ptr<std::string> username,
           std::shared_ptr<std::string> pressEnter, const char* imgPath);
  void Run(Controller const &controller/*Player1, Controller const &controllerPlayer2*/, Renderer &renderer,
           std::size_t target_frame_duration);
  int GetScore() const;
  int GetSize() const;

 private:
  Snake snake;
  Snake snake2;
  SDL_Point food;

  Text wText, iText, eText;
  Image img;

  // Random numbers used to place the food
  std::random_device dev;
  std::mt19937 engine;
  std::uniform_int_distribution<int> random_w;
  std::uniform_int_distribution<int> random_h;

  int score{0};

  void PlaceFood();
  void Update(Renderer &renderer, bool &renderInputText, bool &welcomeScreenOn);
  void PrepareWelcomeScreen(Renderer &renderer);
};

#endif