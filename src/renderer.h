#ifndef RENDERER_H
#define RENDERER_H

#include <vector>
#include "SDL.h"
#include "snake.h"

class Renderer {
 public:
  Renderer(const std::size_t screen_width, const std::size_t screen_height,
           const std::size_t grid_width, const std::size_t grid_height);
  ~Renderer();

  // Render the snake object and the food
  void Render(Snake const snake, SDL_Point const &food, bool &welcomeScreenOn);
  // Updates the top bar of the screen with the score and the frames per second
  void UpdateWindowTitle(int score, int fps);
  // Add
  template <typename T>
  void CopyToRender(T obj){
    obj.CopyToRender(sdl_renderer);
  }
  SDL_Renderer* GetRenderer(){
    return sdl_renderer;
  }
  void ClearScreen();

 private:
  SDL_Window *sdl_window;
  SDL_Renderer *sdl_renderer;

  const std::size_t screen_width;
  const std::size_t screen_height;
  const std::size_t grid_width;
  const std::size_t grid_height;

};

#endif