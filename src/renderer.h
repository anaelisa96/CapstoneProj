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

  void Render(Snake const snake, Snake const snake2, SDL_Point const &food, bool &welcomeScreenOn);
  void UpdateWindowTitle(int player1Score, int player2Score, int fps);
  
  // Template function to copy objects of different classes to render
  template <typename T>
  void CopyToRender(T obj){
    obj.CopyToRender(sdl_renderer);
  }

  SDL_Renderer* GetRenderer();
  void ClearScreen();
  void PresentRenderer();

 private:
  SDL_Window *sdl_window;
  SDL_Renderer *sdl_renderer;

  const std::size_t screen_width;
  const std::size_t screen_height;
  const std::size_t grid_width;
  const std::size_t grid_height;

};

#endif