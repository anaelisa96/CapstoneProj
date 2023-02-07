#include "controller.h"
#include <iostream>
#include "SDL.h"
#include "snake.h"

// Add
#include "renderer.h"

void Controller::ChangeDirection(Snake &snake, Snake::Direction input,
                                 Snake::Direction opposite) const {
  if (snake.direction != opposite || snake.size == 1) snake.direction = input;
  return;
}

void Controller::HandleInput(bool &running, bool &welcomeScreenOn, bool &renderInputText, Snake &snake,
                            Text iText, Renderer &renderer) const {
  SDL_Event e; // Union that contain structures for different event types.
  while (SDL_PollEvent(&e)) { // Poll current pending events
    if (e.type == SDL_QUIT) { // User want to quits
      running = false; // Stop running the game
    }
    else if( welcomeScreenOn){
      if (e.type == SDL_TEXTINPUT || e.type == SDL_KEYDOWN){
         iText.HandleInputText(e, renderInputText, welcomeScreenOn);
      }
      // Render input Text
      renderer.CopyToRender(iText);
    }
    else if (e.type == SDL_KEYDOWN) { // Check if event is a key press
      switch (e.key.keysym.sym) { // See which key was pressed
        case SDLK_UP:
          ChangeDirection(snake, Snake::Direction::kUp,
                          Snake::Direction::kDown);
          break;

        case SDLK_DOWN:
          ChangeDirection(snake, Snake::Direction::kDown,
                          Snake::Direction::kUp);
          break;

        case SDLK_LEFT:
          ChangeDirection(snake, Snake::Direction::kLeft,
                          Snake::Direction::kRight);
          break;

        case SDLK_RIGHT:
          ChangeDirection(snake, Snake::Direction::kRight,
                          Snake::Direction::kLeft);
          break;
      }
    }
  }
}