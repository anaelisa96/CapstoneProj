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

void Controller::HandleInput(bool &running,/* bool &welcomeScreenOn, bool &renderInputText, */Snake &snake/*,
                            Text &iText, Renderer &renderer*/) const {
  SDL_Event e; // Union that contain structures for different event types.
  while (SDL_PollEvent(&e)) { // Poll current pending events

    std::cout << "I am an event!" << std::endl;
    if (e.type == SDL_QUIT) { // User want to quit
      running = false; // Stop running the game
    }
    /*else if( welcomeScreenOn){
      if (e.type == SDL_TEXTINPUT || e.type == SDL_KEYDOWN)
         iText.HandleInputText(e, renderInputText, welcomeScreenOn);
      // Render input Text
      renderer.CopyToRender(iText);
    */
    else if (/*!welcomeScreenOn &&*/e.type == SDL_KEYDOWN) {
      if(e.key.keysym.sym == _upKey){
          ChangeDirection(snake, Snake::Direction::kUp, Snake::Direction::kDown);
          std::cout << "Snake " << &snake << "is going up! " << std::endl;
          break;
      }
      else if (e.key.keysym.sym == _downKey){
          ChangeDirection(snake, Snake::Direction::kDown, Snake::Direction::kUp);
          std::cout << "Snake " << &snake << "is going down! " << std::endl;
          break;
      }
      else if (e.key.keysym.sym == _leftKey){
          ChangeDirection(snake, Snake::Direction::kLeft, Snake::Direction::kRight);
          std::cout << "Snake " << &snake << "is going left! " << std::endl;
          break;
      }
      else if(e.key.keysym.sym == _rightKey){
          ChangeDirection(snake, Snake::Direction::kRight, Snake::Direction::kLeft);
          std::cout << "Snake " << &snake << "is going right! " << std::endl;
          break;
      }
    }
  }
}