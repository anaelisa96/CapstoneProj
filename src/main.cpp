#include <iostream>
#include "controller.h"
#include "game.h"
#include "renderer.h"

// Add
#include <memory>
#include <fstream>
#include <map>

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
  std::cout << "Username 1: " << game.GetPlayer1Username().substr(19) << "\n";
  std::cout << "Username 2: " << game.GetPlayer2Username().substr(19) << "\n";

  std::fstream outputFile("outBestScores.txt", std::ios::app | std::ios::in);
  std::string myline;
  int maxScore = game.GetScore();
  int maxScore2 = game.GetScore2();

  if ( outputFile.is_open() ){
    outputFile << game.GetPlayer1Username().substr(19) << " -->  " << "Score: " << game.GetScore()  << "\n" 
               << game.GetPlayer2Username().substr(19) << " -->  " << "Score: " << game.GetScore2() << "\n";
  }
  else
  {
    std::cout << "Couldn't open output file!" << std::endl;
  }
  
  outputFile.close();

  outputFile.open("outBestScores.txt");
  while ( outputFile ) {
      std::getline (outputFile, myline);
      std::string score;
      if (myline.find(game.GetPlayer1Username().substr(19) + " ") != std::string::npos){
        score = myline.substr(myline.find(":") + 1) ;
        if (maxScore < std::atoi(score.c_str()))
          maxScore = std::atoi(score.c_str());
      }
      else if (myline.find(game.GetPlayer2Username().substr(19) + " ") != std::string::npos){
        score = myline.substr(myline.find(":") + 1) ;
        if (maxScore2 < std::atoi(score.c_str()))
          maxScore2 = std::atoi(score.c_str());
      }
    }
  std::cout << "Player 1 max score is " << maxScore << std::endl;
  std::cout << "Player 2 max score is " << maxScore2 << std::endl;  

  return 0;
}