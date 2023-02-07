#include <iostream>
#include "controller.h"
#include "game.h"
#include "renderer.h"

// Add
#include "SDL_ttf.h"
#include "welcomeScreen.h"
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
  std::shared_ptr<std::string> pressEnter (new std::string("Type you username and press Enter to start the game!"));
  const char *imgPath = "/home/workspace/CppND-Capstone-Snake-Game/build/mySnake2.bmp";

  
  // Create a Renderer, a Controller and a Game object
  Renderer renderer(kScreenWidth, kScreenHeight, kGridWidth, kGridHeight);
  Controller controller;
  Game game(kGridWidth, kGridHeight, std::move(welcome), std::move(username), std::move(pressEnter), imgPath);
  // Start the game loop
  game.Run(controller, renderer, kMsPerFrame);
  std::cout << "Game has terminated successfully!\n";
  std::cout << "Score: " << game.GetScore() << "\n";
  std::cout << "Size: " << game.GetSize() << "\n";
 
  return 0;
}