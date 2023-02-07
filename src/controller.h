#ifndef CONTROLLER_H
#define CONTROLLER_H

#include "snake.h"
// Add
#include "welcomeScreen.h"
#include <string>
#include "renderer.h"
class Controller {
 public:
  // Add
  void HandleInput(bool &running, bool &welcomeScreenOn, bool &renderInputText, Snake &snake,
                   Text iText, Renderer &renderer) const;

 private:
  void ChangeDirection(Snake &snake, Snake::Direction input,
                       Snake::Direction opposite) const;
};

#endif