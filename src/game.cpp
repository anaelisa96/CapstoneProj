#include "game.h"
#include <iostream>
#include "SDL.h"

Game::Game(std::size_t grid_width, std::size_t grid_height)
    : snake(grid_width, grid_height), // position the snake in the screen
      engine(dev()), // random number generation tool using dev as seed
      random_w(0, static_cast<int>(grid_width - 1)), // random number between 0 and the grid width
      random_h(0, static_cast<int>(grid_height - 1)) { // random number between 0 and the grid width
  PlaceFood(); // place food on the screen
}

// Game loop
void Game::Run(Controller const &controller, Renderer &renderer,
               std::size_t target_frame_duration) {
  Uint32 title_timestamp = SDL_GetTicks(); // time stamp
  Uint32 frame_start;
  Uint32 frame_end;
  Uint32 frame_duration;
  int frame_count = 0;
  bool running = true; // tell if the game is running, it is initally set to true

  while (running) {
    frame_start = SDL_GetTicks(); // timestamp for the frame start

    // Input, Update, Render - the main game loop.
    controller.HandleInput(running, snake);
    Update();
    renderer.Render(snake, food);

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

void Game::Update() {
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
    PlaceFood(); // Place foo at other random position
    // Grow snake and increase speed.
    snake.GrowBody(); // The snake grow
    snake.speed += 0.02; // Snake speed increases
  }
}

int Game::GetScore() const { return score; }
int Game::GetSize() const { return snake.size; }