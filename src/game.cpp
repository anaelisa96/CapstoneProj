#include "game.h"
#include <iostream>
#include "SDL.h"

// Add
#include <string>
#include "welcomeScreen.h"

#define wText_xPos (int)screen_width/2 - 286
#define wText_yPos (int)screen_height  / 10
#define iText_xPos (int)screen_width/2 - 250
#define iText_yPos (int)screen_height  - 100
#define eText_xPos (int)screen_width/2 - 250
#define eText_yPos (int)screen_height * 10 / 13
#define img_xPos   (int)screen_width/2
#define img_yPos   (int)screen_height/2

Game::Game(std::size_t screen_width, std::size_t screen_height, std::size_t grid_width, std::size_t grid_height,
           std::shared_ptr<std::string> welcome, std::shared_ptr<std::string> username,
           std::shared_ptr<std::string> pressEnter, const char* imgPath)
    : wText(std::move(welcome),    white, arial, 44, wText_xPos, wText_yPos),
      iText(std::move(username),   white, arial, 22, iText_xPos, iText_yPos),
      eText(std::move(pressEnter), white, arial, 22, eText_xPos, eText_yPos),
      img(imgPath, img_xPos, img_yPos), 
      snake(grid_width, grid_height), // position the snake in the screen
      engine(dev()), // random number generation tool using dev as seed
      random_w(0, static_cast<int>(grid_width - 1)), // random number between 0 and the grid width
      random_h(0, static_cast<int>(grid_height - 1)) { // random number between 0 and the grid width
  PlaceFood(); // place food on the screen
}

// Edit
// Game loop
void Game::Run(Controller const &controller, Renderer &renderer,
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

  while (running) {
    frame_start = SDL_GetTicks(); // timestamp for the frame start

    //Add
    bool renderInputText = false;

    // Input, Update, Render - the main game loop.
    controller.HandleInput(running, welcomeScreenOn, renderInputText, snake, iText,
                           renderer);
    Update(renderer, renderInputText, welcomeScreenOn);
    renderer.Render(snake, food, welcomeScreenOn);

    frame_end = SDL_GetTicks(); // timestamp for the frame end

    // Keep track of how long each loop through the input/update/render cycle
    // takes.
    frame_count++;
    frame_duration = frame_end - frame_start;

    // After every second, update the window title.
    if (frame_end - title_timestamp >= 1000) {
      renderer.UpdateWindowTitle(score, frame_count);
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
}

void Game::PlaceFood() {
  int x, y;
  while (true) {
    // Get random coordinates on the screen
    x = random_w(engine);
    y = random_h(engine);
    // Check that the location is not occupied by a snake item before placing
    // food.
    if (!snake.SnakeCell(x, y)) {
      // Place food at he random coordinates in the screen and get out of the loop.
      food.x = x;
      food.y = y;
      return;
    }
  }
}

// Edit
void Game::Update(Renderer &renderer, bool &renderInputText, bool &welcomeScreenOn) {
  if (welcomeScreenOn){
    if( renderInputText && iText.GetInputText().get()->c_str() != "Username: " ){
      
      renderer.ClearScreen();

      iText.SetTxtSurface();
      iText.SetTexture(renderer.GetRenderer());
      iText.PositionElement(false);
      renderer.CopyToRender(iText);
    }
    renderer.CopyToRender(wText);
    renderer.CopyToRender(img);
    renderer.CopyToRender(eText);
    return;
  }
  if (!snake.alive) return;

  // Update the snake position
  snake.Update();

  // Get head position
  int new_x = static_cast<int>(snake.head_x);
  int new_y = static_cast<int>(snake.head_y);

  // Check if there's food over here
  // Check if head position is equal to the food position
  if (food.x == new_x && food.y == new_y) {
    score++; // Increase the score
    PlaceFood(); // Placed foo at other random position
    // Grow snake and increase speed.
    snake.GrowBody(); // The snake grow
    snake.speed += 0.02; // Snake speed increases
  }
}

int Game::GetScore() const { return score; }
int Game::GetSize() const { return snake.size; }

// Add
void Game::PrepareWelcomeScreen(Renderer &renderer){
  wText.SetTexture(renderer.GetRenderer());
  wText.PositionElement(false);
  iText.SetTexture(renderer.GetRenderer());
  iText.PositionElement(false);
  img.SetTexture(renderer.GetRenderer());
  img.PositionElement(true);
  eText.SetTexture(renderer.GetRenderer());
  eText.PositionElement(false);
}