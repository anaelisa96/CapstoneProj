#ifndef GAME_H
#define GAME_H

#include <random>
#include "SDL.h"
#include "controller.h"
#include "renderer.h"
#include "snake.h"
#include "welcomeScreen.h"

class Game {
 public:
  Game(std::size_t screen_width, std::size_t screen_height, std::size_t grid_width, std::size_t grid_height,
     std::shared_ptr<std::string> welcome, std::shared_ptr<std::string> player1Username,
     std::shared_ptr<std::string> player2Username, std::shared_ptr<std::string> pressEnter, 
     std::shared_ptr<std::string> pressTab, std::shared_ptr<const char*> imgPath);

  void Run(Controller const &controller, Renderer &renderer,
           std::size_t target_frame_duration);
 private:
  Snake snake;
  Snake snake2;
  SDL_Point food;

  Text wText, player1User, player2User, eText, tText;
  Image img;
  std::string _player1Username;
  std::string _player2Username;
  int _player1Score{0},_player2Score{0};
  int _player1MaxScore{0}, _player2MaxScore{0};
  bool _player1NewRecord{false}, _player2NewRecord{false};
  std::shared_ptr<std::string> _gameOver;
  std::shared_ptr<std::string> _player1BestScore;
  std::shared_ptr<std::string> _player2BestScore;
  std::shared_ptr<std::string> _player1CurrentScore;
  std::shared_ptr<std::string> _player2CurrentScore;
  std::shared_ptr<std::string> _result;

  std::random_device dev;
  std::mt19937 engine;
  std::uniform_int_distribution<int> random_w;
  std::uniform_int_distribution<int> random_h;

  void PlaceFood();
  void Update(Renderer &renderer, bool &running, bool &renderInputText, bool &welcomeScreenOn);
  void PrepareWelcomeScreen(Renderer &renderer);
  void SaveUsername();
  void BestScoreComputation();
  void PresentGameOverScreen(Renderer &renderer);
};

#endif