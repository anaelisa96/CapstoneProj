#include <iostream>
#include "controller.h"
#include "game.h"
#include "renderer.h"

// Add
#include <memory>

int main() {
  // Constants useful for the project
  constexpr std::size_t kFramesPerSecond{60};
  constexpr std::size_t kMsPerFrame{1000 / kFramesPerSecond};
  constexpr std::size_t kScreenWidth{640};
  constexpr std::size_t kScreenHeight{640};
  constexpr std::size_t kGridWidth{32};
  constexpr std::size_t kGridHeight{32};
  // Add
  std::shared_ptr<std::string> welcome (new std::string("Welcome to the Snake Game"));
  std::shared_ptr<std::string> username (new std::string("Username: "));
  std::shared_ptr<std::string> pressEnter (new std::string("Type you username and press enter to start the game!"));
  const char *imgPath = "build/mySnake2.bmp";

  // Create a Renderer, a Controller and a Game object
  Renderer renderer(kScreenWidth, kScreenHeight, kGridWidth, kGridHeight);
  Controller controllerPlayer1(SDLK_UP, SDLK_DOWN, SDLK_LEFT, SDLK_RIGHT);
  Controller controllerPlayer2(SDLK_w, SDLK_s, SDLK_a, SDLK_d);
  Game game(kScreenWidth, kScreenHeight, kGridWidth, kGridHeight, std::move(welcome), std::move(username), std::move(pressEnter), imgPath);
  // Start the game loop
  game.Run(controllerPlayer1, controllerPlayer2, renderer, kMsPerFrame);
  std::cout << "Game has terminated successfully!\n";
  std::cout << "Score: " << game.GetScore() << "\n";
  std::cout << "Size: " << game.GetSize() << "\n";
 
  return 0;
}
