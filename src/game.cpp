#include "game.h"
#include <iostream>
#include <fstream>
#include <memory>
#include <unistd.h>

#define wText_xPos       40
#define wText_yPos       64
#define tText_xPos       30
#define tText_yPos       427
#define player1User_xPos 70
#define player1User_yPos 480
#define player2User_xPos 70
#define player2User_yPos 520
#define eText_xPos       400
#define eText_yPos       590
#define gText_xPos       130
#define gText_yPos       50
#define c1Text_xPos      100
#define c1Text_yPos      280
#define c2Text_xPos      100
#define c2Text_yPos      430
#define b1Text_xPos      100
#define b1Text_yPos      310
#define b2Text_xPos      100
#define b2Text_yPos      460
#define rsText_xPos      100
#define rsText_yPos      560
#define img_xPos         305
#define img_yPos         280

Game::Game(std::size_t screen_width, std::size_t screen_height, std::size_t grid_width, std::size_t grid_height,
           std::shared_ptr<std::string> welcome, std::shared_ptr<std::string> player1Username,
           std::shared_ptr<std::string> player2Username, std::shared_ptr<std::string> pressTab, 
           std::shared_ptr<std::string> pressEnter, std::shared_ptr<const char*> imgPath)
    : wText(std::move(welcome),    green, welcomeF, 66, wText_xPos, wText_yPos),
      tText(std::move(pressTab),   green, textF, 20, tText_xPos, tText_yPos),
      player1User(std::move(player1Username),   green, textF, 19, player1User_xPos, player1User_yPos),
      player2User(std::move(player2Username),   green, textF, 19, player2User_xPos, player2User_yPos),
      eText(std::move(pressEnter), green, enterF, 22, eText_xPos, eText_yPos),
      img(std::move(imgPath), img_xPos, img_yPos), 
      snake(grid_width, grid_height),
      snake2(grid_width, grid_height),
      engine(dev()), // random number generation tool using dev as seed
      random_w(0, static_cast<int>(grid_width - 1)), // random number between 0 and the grid width
      random_h(0, static_cast<int>(grid_height - 1)) { // random number between 0 and the grid width
  snake.setPosition(random_w(engine),random_h(engine));
  snake2.setPosition(random_w(engine),random_h(engine));
  PlaceFood(); // place food on the screen
}

// Game loop
void Game::Run(Controller const &controller, Renderer &renderer, std::size_t target_frame_duration) {
  Uint32 title_timestamp = SDL_GetTicks(); // time stamp
  Uint32 frame_start;
  Uint32 frame_end;
  Uint32 frame_duration;
  int frame_count = 0;

  // Set elements surface and texture to be presented in the welcome screen
  PrepareWelcomeScreen(renderer);
  // Clear Screen
  renderer.ClearScreen();

  // Flags to keep track of the game flow
  bool running = true;
  bool welcomeScreenOn = true;
  bool insertPlayer1Username = true;

  SDL_StartTextInput();

  while (running) {

    bool renderInputText = false;
    frame_start = SDL_GetTicks();

    // Game input: keybord keys for usernames typing or snakes control
    controller.HandleInput(running, welcomeScreenOn, renderInputText, insertPlayer1Username, snake, snake2, player1User, player2User, renderer);
    Update(renderer, running, renderInputText, welcomeScreenOn); 
    renderer.Render(snake, snake2, food, welcomeScreenOn);

    frame_end = SDL_GetTicks();

    // Keep track of how long each loop through the input/update/render cycle takes.
    frame_count++;
    frame_duration = frame_end - frame_start;

    // After every second, update the window title.
    if (frame_end - title_timestamp >= 1000) {
      renderer.UpdateWindowTitle(_player1Score, _player2Score, frame_count);
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
  // At the end of the game: Save players usernames, compute best score and present gameover screen
  SaveUsername();
  BestScoreComputation();
  PresentGameOverScreen(renderer);
}

void Game::PlaceFood() {
  int x, y;
  while (true) {
    // Get random coordinates on the screen
    x = random_w(engine);
    y = random_h(engine);
    // Check that the location is not occupied by a snake item before placing food.
    if (!snake.SnakeCell(x, y) && !snake2.SnakeCell(x,y)) {
      // Place food at he random coordinates in the screen and get out of the loop.
      food.x = x;
      food.y = y;
      return;
    }
  }
}

void Game::Update(Renderer &renderer, bool &running, bool &renderInputText, bool &welcomeScreenOn) {
  // Occurs before the game actually starts
  if (welcomeScreenOn){
    if( renderInputText){
      // Clear screen
      renderer.ClearScreen();
      // Set surface, texture and position for players 1 and 2 username objects
      player1User.SetTxtSurface();
      player1User.SetTexture(renderer.GetRenderer());
      player1User.PositionElement();
      player2User.SetTxtSurface();
      player2User.SetTexture(renderer.GetRenderer());
      player2User.PositionElement();
      // Copý players 1 and 2 username elements to render
      renderer.CopyToRender(player2User);
      renderer.CopyToRender(player1User);
    }
    // Copy remainder welcome screen elements to render
    renderer.CopyToRender(wText);
    renderer.CopyToRender(tText);
    renderer.CopyToRender(player1User);
    renderer.CopyToRender(player2User);
    renderer.CopyToRender(img);
    renderer.CopyToRender(eText);
    return;
  }
  
  // If one of the snakes die the game is over - GameOver screen is presented
  if (!snake.alive || !snake2.alive){
    running = false;
    return;
  }

  // Update the snakes position
  snake.Update(snake2);
  snake2.Update(snake);

  // Get head position for snake 1 and snake 2
  int new_x = static_cast<int>(snake.head_x);
  int new_y = static_cast<int>(snake.head_y);
  int new_x2 = static_cast<int>(snake2.head_x);
  int new_y2 = static_cast<int>(snake2.head_y);

  // Check if head of snake 1 position is equal to the food position
  if (food.x == new_x && food.y == new_y) {
    _player1Score++;
    PlaceFood();
    snake.GrowBody();
    snake.speed += 0.02;
  }

  // Check if head of snake 2 position is equal to the food position
  if (food.x == new_x2 && food.y == new_y2) {
    _player2Score++;
    PlaceFood();
    snake2.GrowBody();
    snake2.speed += 0.02;
  }
}

void Game::SaveUsername() {
  _player1Username = player1User.GetUsername().substr(10);
  _player2Username = player2User.GetUsername().substr(10);
}

void Game::PrepareWelcomeScreen(Renderer &renderer){

  // Set surface ans texture for welcome screen elements
  wText.SetTexture(renderer.GetRenderer());
  wText.PositionElement();
  tText.SetTexture(renderer.GetRenderer());
  tText.PositionElement();
  player1User.SetTexture(renderer.GetRenderer());
  player1User.PositionElement();
  player2User.SetTexture(renderer.GetRenderer());
  player2User.PositionElement();
  img.SetTexture(renderer.GetRenderer());
  img.PositionElement();
  eText.SetTexture(renderer.GetRenderer());
  eText.PositionElement();
}

void Game::BestScoreComputation(){

  // Open the file
  std::fstream outputFile("scores.txt", std::ios::app | std::ios::in | std::ios::out);

  std::string myline;

  // Check if file was successfully opened
  // Reading the file...
  if ( outputFile.is_open() ){
    while ( outputFile ) {
      std::getline (outputFile, myline);
      std::string score;
      // Find previous scores of player 1 and player 2 in scores.txt (through their usernames).
      // Save their maximum scores in the respective variables
      if (myline.find(_player1Username + " ") != std::string::npos){
        score = myline.substr(myline.find(":") + 1) ;
        if (_player1MaxScore < std::atoi(score.c_str()))
          _player1MaxScore = std::atoi(score.c_str());
      }
      else if (myline.find(_player2Username + " ") != std::string::npos){
        score = myline.substr(myline.find(":") + 1) ;
        if (_player2MaxScore < std::atoi(score.c_str()))
          _player2MaxScore = std::atoi(score.c_str());
      }
    }
    // Check if current score is higer than the maximum score previouly obtained
    // Perform the replacement in the positive scenario
    if (_player1MaxScore < _player1Score){
      _player1NewRecord = true;
      _player1MaxScore = _player1Score;
    }
    if (_player2MaxScore < _player2Score){
      _player2NewRecord = true;
      _player2MaxScore = _player2Score;
    }
  }
  else
  {
    std::cout << "Could not open the file" << std::endl;
  }

  // Close the file
  outputFile.close();

  // Reopen the file for writing
  outputFile.open("scores.txt", std::ios::app | std::ios::in | std::ios::out); 

  // Check if the file was successfully opened
  if ( outputFile.is_open() ){
    // Write players usernames and scores
    outputFile << _player1Username << " -->  " << "Score: " << _player1Score  << "\n" 
               << _player2Username << " -->  " << "Score: " << _player2Score << "\n";
  }
  else
  {
    std::cout << "Couldn't open output file!" << std::endl;
  }
  
  // Close the file
  outputFile.close();
}

void Game::PresentGameOverScreen(Renderer &renderer){

  // Clear the screen
  renderer.ClearScreen();

  // Game over screen title text
  _gameOver = std::make_shared<std::string> ("Game Over");

  // Change username objects text and position to reuse
  player1User.EditText(std::make_shared<std::string> (_player1Username));
  player2User.EditText(std::make_shared<std::string> (_player2Username));
  player1User.EditPosition(100, 250);
  player2User.EditPosition(100, 400);

  // Current Scores
  _player1CurrentScore = std::make_shared<std::string> ("Current score = " + std::to_string(_player1Score));
  _player2CurrentScore = std::make_shared<std::string> ("Current score = " + std::to_string(_player2Score));
  
  // Check if one of the players achieved a new record
  _player1NewRecord? _player1BestScore = std::make_shared<std::string> ("New Record! Best score = " + std::to_string(_player1MaxScore)) : 
                     _player1BestScore = std::make_shared<std::string> ("Best score = " + std::to_string(_player1MaxScore));
  
  _player2NewRecord? _player2BestScore = std::make_shared<std::string> ("New Record! Best score = " + std::to_string(_player2MaxScore)) :
                     _player2BestScore = std::make_shared<std::string> ("Best score = " + std::to_string(_player2MaxScore));

  // Check the game result
  if (_player1Score > _player2Score)
    _result = std::make_shared<std::string> (_player1Username + " won!");
  else if (_player1Score < _player2Score)
    _result = std::make_shared<std::string> (_player2Username + " won!");
  else
    _result = std::make_shared<std::string> ("It is a tie!");

  // Create Text objects for GameOver screen
  Text gText(std::move(_gameOver),                red, gameOverF, 200, gText_xPos, gText_yPos);
  Text c1Text(std::move(_player1CurrentScore), yellow, textF,  20, c1Text_xPos, c1Text_yPos);
  Text b1Text(std::move(_player1BestScore),    yellow, textF,  20, b1Text_xPos, b1Text_yPos);
  Text c2Text(std::move(_player2CurrentScore), yellow, textF,  20, c2Text_xPos, c2Text_yPos);
  Text b2Text(std::move(_player2BestScore),    yellow, textF,  20, b2Text_xPos, b2Text_yPos);
  Text rsText(std::move(_result),                blue, textF,  24, rsText_xPos, rsText_yPos);

  // Set elements texture and surface, color and position (if needed)
  gText.SetTexture(renderer.GetRenderer());
  gText.PositionElement();
  player1User.SetTxtColor(yellow);
  player1User.SetTxtSurface();
  player1User.SetTexture(renderer.GetRenderer());
  player1User.PositionElement();
  player2User.SetTxtColor(yellow);
  player2User.SetTxtSurface();
  player2User.SetTexture(renderer.GetRenderer());
  player2User.PositionElement();
  c1Text.SetTxtSurface();
  c1Text.SetTexture(renderer.GetRenderer());
  c1Text.PositionElement();
  c2Text.SetTexture(renderer.GetRenderer());
  c2Text.PositionElement();
  b1Text.SetTexture(renderer.GetRenderer());
  b1Text.PositionElement();
  b2Text.SetTexture(renderer.GetRenderer());
  b2Text.PositionElement();
  rsText.SetTexture(renderer.GetRenderer());
  rsText.PositionElement();

  // Copy elements to render
  renderer.CopyToRender(gText);
  renderer.CopyToRender(player1User);
  renderer.CopyToRender(player2User);
  renderer.CopyToRender(c1Text);
  renderer.CopyToRender(c2Text);
  renderer.CopyToRender(b1Text);
  renderer.CopyToRender(b2Text);
  renderer.CopyToRender(rsText);

  // Present the screen
  renderer.PresentRenderer();

  // Screen is displayed for 10 seconds
  sleep(10);
}