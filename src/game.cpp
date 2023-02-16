#include "game.h"
#include <iostream>
#include "SDL.h"

// Add
#include <string>
#include "welcomeScreen.h"
#include <fstream>
#include <memory>
#include <unistd.h>

#define wText_xPos       (int)screen_width/2 - 286
#define wText_yPos       (int)screen_height  / 10
#define tText_xPos       (int)screen_width/2 - 290
#define tText_yPos       (int)screen_height * 10 / 15
#define player1Text_xPos (int)screen_width/2 - 250
#define player1Text_yPos (int)screen_height  - 180
#define player2Text_xPos (int)screen_width/2 - 250
#define player2Text_yPos (int)screen_height  - 150
#define eText_xPos       (int)screen_width/2
#define eText_yPos       (int)screen_height -   50
#define gText_xPos       200
#define gText_yPos       100
#define b1Text_xPos      100
#define b1Text_yPos      300
#define b2Text_xPos      100
#define b2Text_yPos      400
#define img_xPos         (int)screen_width/2
#define img_yPos         (int)screen_height/2 - 60

Game::Game(std::size_t screen_width, std::size_t screen_height, std::size_t grid_width, std::size_t grid_height,
           std::shared_ptr<std::string> welcome, std::shared_ptr<std::string> player1Username,
           std::shared_ptr<std::string> player2Username, std::shared_ptr<std::string> pressTab, 
           std::shared_ptr<std::string> pressEnter, const char* imgPath)
    : wText(std::move(welcome),    white, arial, 44, wText_xPos, wText_yPos),
      tText(std::move(pressTab),   white, arial, 22, tText_xPos, tText_yPos),
      player1Text(std::move(player1Username),   white, arial, 22, player1Text_xPos, player1Text_yPos),
      player2Text(std::move(player2Username),   white, arial, 22, player2Text_xPos, player2Text_yPos),
      eText(std::move(pressEnter), white, arial, 22, eText_xPos, eText_yPos),
      img(imgPath, img_xPos, img_yPos), 
      snake(grid_width, grid_height), // position the snake in the screen
      snake2(grid_width, grid_height),
      engine(dev()), // random number generation tool using dev as seed
      random_w(0, static_cast<int>(grid_width - 1)), // random number between 0 and the grid width
      random_h(0, static_cast<int>(grid_height - 1)) { // random number between 0 and the grid width
  snake.setPosition(random_w(engine),random_h(engine));
  snake2.setPosition(random_w(engine),random_h(engine));
  PlaceFood(); // place food on the screen
}

// Edit
// Game loop
void Game::Run(Controller const &controller/*Player1, Controller const &controllerPlayer2*/, Renderer &renderer,
               std::size_t target_frame_duration) {
  Uint32 title_timestamp = SDL_GetTicks(); // time stamp
  Uint32 frame_start;
  Uint32 frame_end;
  Uint32 frame_duration;
  int frame_count = 0;

  // Add
  PrepareWelcomeScreen(renderer);
  renderer.ClearScreen();  
  SDL_StartTextInput();

  bool running = true; // tell if the game is running, it is initally set to true
  bool welcomeScreenOn = true;
  bool insertPlayer1Username = true;

  while (running) {
        //Add
    bool renderInputText = false;
    frame_start = SDL_GetTicks(); // timestamp for the frame start

    /*std::thread player1Input(&Controller::HandleInput, controllerPlayer1, std::ref(running), std::ref(welcomeScreenOn),
      std::ref(renderInputText), std::ref(snake), std::ref(iText), std::ref(renderer));
    std::thread player2Input(&Controller::HandleInput, controllerPlayer2, std::ref(running), std::ref(welcomeScreenOn),
      std::ref(renderInputText), std::ref(snake2), std::ref(iText), std::ref(renderer));*/
    /*std::thread player1Input(&Controller::HandleInput, controllerPlayer1, std::ref(running), std::ref(snake));
    std::thread player2Input(&Controller::HandleInput, controllerPlayer2, std::ref(running), std::ref(snake2));
    player1Input.join();
    player2Input.join();*/

    // Input, Update, Render - the main game loop.
    //controllerPlayer1.HandleInput(running, welcomeScreenOn, renderInputText, snake, iText,
    //                       renderer);
    //controller.HandleInput(running, snake, snake2);
    controller.HandleInput(running, welcomeScreenOn, renderInputText, insertPlayer1Username, snake, snake2, player1Text, player2Text, renderer);
    Update(renderer, running, renderInputText, welcomeScreenOn);
    renderer.Render(snake, snake2, food, welcomeScreenOn);

    frame_end = SDL_GetTicks(); // timestamp for the frame end

    // Keep track of how long each loop through the input/update/render cycle
    // takes.
    frame_count++;
    frame_duration = frame_end - frame_start;

    // After every second, update the window title.
    if (frame_end - title_timestamp >= 1000) {
      renderer.UpdateWindowTitle(score, score2, frame_count);
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
  SaveUsername();
  BestScoreComputation(maxScore, maxScore2, newRecord1, newRecord2);
  PresentGameOverScreen(renderer, maxScore, maxScore2, newRecord1, newRecord2);
}

void Game::PlaceFood() {
  int x, y;
  while (true) {
    // Get random coordinates on the screen
    x = random_w(engine);
    y = random_h(engine);
    // Check that the location is not occupied by a snake item before placing
    // food.
    if (!snake.SnakeCell(x, y) && !snake2.SnakeCell(x,y)) {
      // Place food at he random coordinates in the screen and get out of the loop.
      food.x = x;
      food.y = y;
      return;
    }
  }
}

// Edit
void Game::Update(Renderer &renderer, bool &running, bool &renderInputText, bool &welcomeScreenOn) {
  if (welcomeScreenOn){
    if( renderInputText && player1Text.GetInputText().get()->c_str() != "Player 1 Username: " ){
      
      renderer.ClearScreen();

      player1Text.SetTxtSurface();
      player1Text.SetTexture(renderer.GetRenderer());
      player1Text.PositionElement(false);
      renderer.CopyToRender(player1Text);
    }
    if( renderInputText && player2Text.GetInputText().get()->c_str() != "Player 2 Username: " ){
      
      renderer.ClearScreen();

      player2Text.SetTxtSurface();
      player2Text.SetTexture(renderer.GetRenderer());
      player2Text.PositionElement(false);
      renderer.CopyToRender(player2Text);
    }
    renderer.CopyToRender(wText);
    renderer.CopyToRender(tText);
    renderer.CopyToRender(player1Text);
    renderer.CopyToRender(player2Text);
    renderer.CopyToRender(img);
    renderer.CopyToRender(eText);
    return;
  }
  //if (!snake.alive) return;
  if (!snake.alive || !snake2.alive){
    running = false;
    return;
  }

  // Update the snake position
  snake.Update(snake2);
  snake2.Update(snake);

  // Get head position
  int new_x = static_cast<int>(snake.head_x);
  int new_y = static_cast<int>(snake.head_y);
  int new_x2 = static_cast<int>(snake2.head_x);
  int new_y2 = static_cast<int>(snake2.head_y);

  // Check if there's food over here
  // Check if head position is equal to the food position
  if (food.x == new_x && food.y == new_y) {
    score++; // Increase the score
    PlaceFood(); // Placed foo at other random position
    // Grow snake and increase speed.
    snake.GrowBody(); // The snake grow
    snake.speed += 0.02; // Snake speed increases
  }

  if (food.x == new_x2 && food.y == new_y2) {
    score2++; // Increase the score2
    PlaceFood(); // Placed foo at other random position
    // Grow snake and increase speed.
    snake2.GrowBody(); // The snake grow
    snake2.speed += 0.02; // Snake speed increases
  }

}

int Game::GetScore()  const { return score; }
int Game::GetScore2() const { return score2; }
int Game::GetSize() const { return snake.size; }
int Game::GetSize2() const { return snake2.size; }
void Game::SaveUsername() {
  _player1Username = player1Text.GetUsername();
  _player2Username = player2Text.GetUsername();
  }
std::string Game::GetPlayer1Username(){return _player1Username;}
std::string Game::GetPlayer2Username(){return _player2Username;}

// Add
void Game::PrepareWelcomeScreen(Renderer &renderer){
  wText.SetTexture(renderer.GetRenderer());
  wText.PositionElement(false);
  tText.SetTexture(renderer.GetRenderer());
  tText.PositionElement(false);
  player1Text.SetTexture(renderer.GetRenderer());
  player1Text.PositionElement(false);
  player2Text.SetTexture(renderer.GetRenderer());
  player2Text.PositionElement(false);
  img.SetTexture(renderer.GetRenderer());
  img.PositionElement(true);
  eText.SetTexture(renderer.GetRenderer());
  eText.PositionElement(false);
}

void Game::BestScoreComputation(int &maxScore, int &maxScore2, bool &newRecord1, bool &newRecord2){

  std::fstream outputFile("outBestScores.txt", std::ios::app | std::ios::in | std::ios::out);
  std::string myline;
  maxScore  = 0;
  maxScore2 = 0;
  newRecord1 = false;
  newRecord2 = false;

  if ( outputFile.is_open() ){
    while ( outputFile ) {
      std::getline (outputFile, myline);
      std::string score;
      if (myline.find(GetPlayer1Username().substr(19) + " ") != std::string::npos){
        score = myline.substr(myline.find(":") + 1) ;
        if (maxScore < std::atoi(score.c_str()))
          maxScore = std::atoi(score.c_str());
      }
      else if (myline.find(GetPlayer2Username().substr(19) + " ") != std::string::npos){
        score = myline.substr(myline.find(":") + 1) ;
        if (maxScore2 < std::atoi(score.c_str()))
          maxScore2 = std::atoi(score.c_str());
      }
    }
    if (maxScore < GetScore()){
      newRecord1 = true;
      maxScore = GetScore();
    }
    if (maxScore2 < GetScore2()){
      newRecord2 = true;
      maxScore2 = GetScore2();
    }
  }
  else
  {
    std::cout << "Could not open the file" << std::endl;
  }

  outputFile.close();

  outputFile.open("outBestScores.txt", std::ios::app | std::ios::in | std::ios::out); 

  if ( outputFile.is_open() ){
    outputFile << GetPlayer1Username().substr(19) << " -->  " << "Score: " << GetScore()  << "\n" 
               << GetPlayer2Username().substr(19) << " -->  " << "Score: " << GetScore2() << "\n";
  }
  else
  {
    std::cout << "Couldn't open output file!" << std::endl;
  }
  
  outputFile.close();

  std::cout << "Player 1 max score is " << maxScore << std::endl;
  std::cout << "Player 2 max score is " << maxScore2 << std::endl; 

}

void Game::PresentGameOverScreen(Renderer &renderer, int &maxScore, int &maxScore2, bool &newRecord1, bool &newRecord2){

  renderer.ClearScreen();

  gameOver = std::make_shared<std::string> ("Game Over");
  
  if(newRecord1)
    player1BestScore = std::make_shared<std::string> ("Player 1: New Record: your best score is " + std::to_string(maxScore));
  else
    player1BestScore = std::make_shared<std::string> ("Player 1: Your best score is " + std::to_string(maxScore));
  
  if(newRecord2)
    player2BestScore = std::make_shared<std::string> ("Player 2: New Record: your best score is " + std::to_string(maxScore2));
  else
    player2BestScore = std::make_shared<std::string> ("Player 2: Your best score is " + std::to_string(maxScore2));
  
  Text gText(std::move(gameOver), white, arial, 44, gText_xPos, gText_yPos);
  Text b1Text(std::move(player1BestScore), white, arial, 22, b1Text_xPos, b1Text_yPos);
  Text b2Text(std::move(player2BestScore), white, arial, 22, b2Text_xPos, b2Text_yPos);
  
  gText.SetTexture(renderer.GetRenderer());
  gText.PositionElement(false);
  b1Text.SetTexture(renderer.GetRenderer());
  b1Text.PositionElement(false);
  b2Text.SetTexture(renderer.GetRenderer());
  b2Text.PositionElement(false);

  renderer.CopyToRender(gText);
  renderer.CopyToRender(b1Text);
  renderer.CopyToRender(b2Text);

  renderer.PresentRenderer();
  sleep(5);
}