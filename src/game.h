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
     std::shared_ptr<std::string> welcome, std::shared_ptr<std::string> player1Username,
     std::shared_ptr<std::string> player2Username, std::shared_ptr<std::string> pressEnter, 
     std::shared_ptr<std::string> pressTab, const char* imgPath);
  void Run(Controller const &controller/*Player1, Controller const &controllerPlayer2*/, Renderer &renderer,
           std::size_t target_frame_duration);
  int GetScore() const;
  int GetScore2() const;
  int GetSize() const;
  int GetSize2() const;
  void SaveUsername();
  std::string GetPlayer1Username();
  std::string GetPlayer2Username();

 private:
  Snake snake;
  Snake snake2;
  SDL_Point food;

  Text wText, player1Text, player2Text, eText, tText;
  Image img;
  std::string _player1Username;
  std::string _player2Username;
  std::shared_ptr<std::string> gameOver;
  std::shared_ptr<std::string> player1BestScore;
  std::shared_ptr<std::string> player2BestScore;

  int maxScore, maxScore2;
  bool newRecord1, newRecord2;

  // Random numbers used to place the food
  std::random_device dev;
  std::mt19937 engine;
  std::uniform_int_distribution<int> random_w;
  std::uniform_int_distribution<int> random_h;

  int score{0};
  int score2{0};

  void PlaceFood();
  void Update(Renderer &renderer, bool &running, bool &renderInputText, bool &welcomeScreenOn);
  void PrepareWelcomeScreen(Renderer &renderer);
  void BestScoreComputation(int &maxScore, int &maxScore2, bool &newRecord1, bool &newRecord2);
  void PresentGameOverScreen(Renderer &renderer, int &maxScore, int &maxScore2, bool &newRecord1, bool &newRecord2);
};

#endif