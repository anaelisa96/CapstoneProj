#ifndef CONTROLLER_H
#define CONTROLLER_H

#include "snake.h"
#include "welcomeScreen.h"
#include "renderer.h"
class Controller {
 public:

  void HandleInput(bool &running, bool &welcomeScreenOn, bool &renderInputText, bool &insertPlayer1Username,
                            Snake &snake, Snake &snake2, Text &player1Text, Text &player2Text, Renderer &renderer) const;

 private:
  void ChangeDirection(Snake &snake, Snake::Direction input, Snake::Direction opposite) const;
};

#endif