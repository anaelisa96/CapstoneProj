#include <iostream>
#include "controller.h"
#include "game.h"
#include "renderer.h"

// Add
#include <memory>
#include <fstream>

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
  std::shared_ptr<std::string> player1Username (new std::string("Player 1 Username: "));
  std::shared_ptr<std::string> player2Username (new std::string("Player 2 Username: "));
  std::shared_ptr<std::string> pressTab (new std::string("Type you usernames (press TAB to insert player 2 username)"));
  std::shared_ptr<std::string> pressEnter (new std::string("Press Enter to start the game!"));
  const char *imgPath = "mySnake2.bmp";

  // Create a Renderer, a Controller and a Game object
  Renderer renderer(kScreenWidth, kScreenHeight, kGridWidth, kGridHeight);
  //Controller controllerPlayer1(SDLK_UP, SDLK_DOWN, SDLK_LEFT, SDLK_RIGHT);
  //Controller controllerPlayer2(SDLK_w, SDLK_s, SDLK_a, SDLK_d);
  Controller controller;
  Game game(kScreenWidth, kScreenHeight, kGridWidth, kGridHeight, std::move(welcome), std::move(player1Username),
            std::move(player2Username), std::move(pressTab), std::move(pressEnter), imgPath);
  // Start the game loop
  game.Run(controller/*Player1, controllerPlayer2*/, renderer, kMsPerFrame);
  std::cout << "Game has terminated successfully!\n";
  std::cout << "Score: " << game.GetScore() << "\n";
  std::cout << "Size: " << game.GetSize() << "\n";
  std::cout << "Score 2: " << game.GetScore2() << "\n";
  std::cout << "Size 2: " << game.GetSize2() << "\n";
  std::ofstream myfile;
  myfile.open ("example.txt");
  myfile << game.GetPlayer1Username().substr(19) << " -->  " << "Score: " << game.GetScore()  << "\n" 
         << game.GetPlayer2Username().substr(19) << " -->  " << "Score: " << game.GetScore2() << "\n";
  myfile.close();
 
  return 0;
}