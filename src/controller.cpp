#include "controller.h"
#include "SDL.h"
#include <iostream>

void Controller::ChangeDirection(Snake &snake, Snake::Direction input, Snake::Direction opposite) const {
  if (snake.direction != opposite || snake.size == 1) snake.direction = input;
  return;
}

void Controller::HandleInput(bool &running, bool &welcomeScreenOn, bool &renderInputText, bool &insertPlayer1Username,
                            Snake &snake, Snake &snake2, Text &player1Text, Text &player2Text, Renderer &renderer) const {
  SDL_Event e; 
  while (SDL_PollEvent(&e)) {
    // If game window is closed
    if (e.type == SDL_QUIT) {
      // Stop running the game
      running = false;
    }
    // User Input goes to render welcome screen
    else if( welcomeScreenOn){
      if (e.type == SDL_TEXTINPUT || e.type == SDL_KEYDOWN)
        if (insertPlayer1Username) // Insert player 1 username
          player1Text.HandleInputText(e, renderInputText, welcomeScreenOn, insertPlayer1Username);
        else // Insert player 2 username and start the game
          player2Text.HandleInputText(e, renderInputText, welcomeScreenOn, insertPlayer1Username);

      // Render input Text
      renderer.CopyToRender(player1Text);
      renderer.CopyToRender(player2Text);
    }
    // User input control both snakes
    else if (!welcomeScreenOn && e.type == SDL_KEYDOWN) {
      switch(e.key.keysym.sym){
        case SDLK_UP: // Up arrow key - snake 1 up
            ChangeDirection(snake, Snake::Direction::kUp, Snake::Direction::kDown);
            break;
        case SDLK_DOWN: // Down arrow key - snake 1 down
            ChangeDirection(snake, Snake::Direction::kDown, Snake::Direction::kUp);
            break;
        case SDLK_LEFT: // Left arrow key - snake 1 left
            ChangeDirection(snake, Snake::Direction::kLeft, Snake::Direction::kRight);
            break;
        case SDLK_RIGHT: // Right arrow key - snake 1 right
            ChangeDirection(snake, Snake::Direction::kRight, Snake::Direction::kLeft);
            break;
        case SDLK_w: // w key - snake 2 up
            ChangeDirection(snake2, Snake::Direction::kUp, Snake::Direction::kDown);
            break;
        case SDLK_s: // s key - snake 2 down
            ChangeDirection(snake2, Snake::Direction::kDown, Snake::Direction::kUp);
            break;
        case SDLK_a: // a key - snake 2 left
            ChangeDirection(snake2, Snake::Direction::kLeft, Snake::Direction::kRight);
            break;
        case SDLK_d: // d key - snake 2 right
            ChangeDirection(snake2, Snake::Direction::kRight, Snake::Direction::kLeft);
            break;
      }
    }
  }
}