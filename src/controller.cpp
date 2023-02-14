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

void Controller::HandleInput(bool &running, bool &welcomeScreenOn, bool &renderInputText, bool &insertPlayer1Username,
                            Snake &snake, Snake &snake2, Text &player1Text, Text &player2Text, Renderer &renderer) const {
  SDL_Event e; // Union that contain structures for different event types.
  while (SDL_PollEvent(&e)) { // Poll current pending events
    if (e.type == SDL_QUIT) { // User want to quit
      running = false; // Stop running the game
    }
    else if( welcomeScreenOn){
      if (e.type == SDL_TEXTINPUT || e.type == SDL_KEYDOWN)
        if (insertPlayer1Username)
          player1Text.HandleInputText(e, renderInputText, welcomeScreenOn, insertPlayer1Username);
        else
          player2Text.HandleInputText(e, renderInputText, welcomeScreenOn, insertPlayer1Username);

      // Render input Text
      renderer.CopyToRender(player1Text);
      renderer.CopyToRender(player2Text);
    }
    else if (!welcomeScreenOn && e.type == SDL_KEYDOWN) {
      switch(e.key.keysym.sym){
        case SDLK_UP:
            ChangeDirection(snake, Snake::Direction::kUp, Snake::Direction::kDown);
            std::cout << "Snake 1 is going up! " << std::endl;
            break;
        case SDLK_DOWN:
            ChangeDirection(snake, Snake::Direction::kDown, Snake::Direction::kUp);
            std::cout << "Snake 1 is going down! " << std::endl;
            break;
        case SDLK_LEFT:
            ChangeDirection(snake, Snake::Direction::kLeft, Snake::Direction::kRight);
            std::cout << "Snake 1 is going left! " << std::endl;
            break;
        case SDLK_RIGHT:
            ChangeDirection(snake, Snake::Direction::kRight, Snake::Direction::kLeft);
            std::cout << "Snake 1 is going right! " << std::endl;
            break;
        case SDLK_w:
            ChangeDirection(snake2, Snake::Direction::kUp, Snake::Direction::kDown);
            std::cout << "Snake 2 is going up! " << std::endl;
            break;
        case SDLK_s:
            ChangeDirection(snake2, Snake::Direction::kDown, Snake::Direction::kUp);
            std::cout << "Snake 2 is going down! " << std::endl;
            break;
        case SDLK_a:
            ChangeDirection(snake2, Snake::Direction::kLeft, Snake::Direction::kRight);
            std::cout << "Snake 2 is going left! " << std::endl;
            break;
        case SDLK_d:
            ChangeDirection(snake2, Snake::Direction::kRight, Snake::Direction::kLeft);
            std::cout << "Snake 2 is going right! " << std::endl;
            break;
      }
    }
  }
}