#ifndef CONTROLLER_H
#define CONTROLLER_H

#include "snake.h"
// Add
#include "welcomeScreen.h"
#include <string>
#include "renderer.h"
class Controller {
 public:
  /*Controller(SDL_Keycode upKey, SDL_Keycode downKey, SDL_Keycode leftKey, SDL_Keycode rightKey) :
             _upKey(upKey), _downKey(downKey), _leftKey(leftKey), _rightKey(rightKey){}*/
             
  void HandleInput(bool &running,/* bool &welcomeScreenOn, bool &renderInputText, */Snake &snake/*,
                            Text &iText, Renderer &renderer*/, Snake &snake2) const;

 private:
  void ChangeDirection(Snake &snake, Snake::Direction input,
                       Snake::Direction opposite) const;
  /*const SDL_Keycode _upKey;
  const SDL_Keycode _downKey;
  const SDL_Keycode _leftKey;
  const SDL_Keycode _rightKey;*/
};

#endif