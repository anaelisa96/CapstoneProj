#include "renderer.h"
#include <iostream>
#include <string>
#include "SDL_ttf.h"

// Renderer Constructor
Renderer::Renderer(const std::size_t screen_width,
                   const std::size_t screen_height,
                   const std::size_t grid_width, const std::size_t grid_height)
    : screen_width(screen_width),
      screen_height(screen_height),
      grid_width(grid_width),
      grid_height(grid_height) {
  // Initialize SDL
  if (SDL_Init(SDL_INIT_VIDEO) < 0) { // SDL is being initialized with video only for now
    std::cerr << "SDL could not initialize.\n";
    std::cerr << "SDL_Error: " << SDL_GetError() << "\n";
  }

  if (TTF_Init() < 0)
    std::cerr << "TTF could not initialize.\n";

  // Create Window - centered in the screen
  sdl_window = SDL_CreateWindow("Snake Game", SDL_WINDOWPOS_CENTERED,
                                SDL_WINDOWPOS_CENTERED, screen_width,
                                screen_height, SDL_WINDOW_SHOWN);

  if (nullptr == sdl_window) {
    std::cerr << "Window could not be created.\n";
    std::cerr << " SDL_Error: " << SDL_GetError() << "\n";
  }

  // Create renderer
  sdl_renderer = SDL_CreateRenderer(sdl_window, -1, SDL_RENDERER_ACCELERATED);
  if (nullptr == sdl_renderer) {
    std::cerr << "Renderer could not be created.\n";
    std::cerr << "SDL_Error: " << SDL_GetError() << "\n";
  }
}

Renderer::~Renderer() {
  SDL_DestroyWindow(sdl_window);
  SDL_Quit();
}

void Renderer::Render(Snake const snake, Snake const snake2, SDL_Point const &food, bool &welcomeScreenOn) {

  // Render Welcome Screen at the begining of the game
  if(welcomeScreenOn){
    SDL_RenderPresent(sdl_renderer);
    return;
  }
  // Define a rectangle
  SDL_Rect block;
  block.w = screen_width / grid_width; // Width of one cell in the grid
  block.h = screen_height / grid_height; // Height of one cell in the grid

  // Clear screen
  ClearScreen();

  // Render food
  SDL_SetRenderDrawColor(sdl_renderer, 0xFF, 0xCC, 0x00, 0xFF); // Yellow color
  block.x = food.x * block.w; 
  block.y = food.y * block.h;
  SDL_RenderFillRect(sdl_renderer, &block); // Fill block of one cell

  // Render snake1's body
  SDL_SetRenderDrawColor(sdl_renderer, 0xFF, 0xFF, 0xFF, 0xFF); // snake 1 - white body
  for (SDL_Point const &point : snake.body) {
    block.x = point.x * block.w;
    block.y = point.y * block.h;
    SDL_RenderFillRect(sdl_renderer, &block);
  }

  // Render snake1's head
  block.x = static_cast<int>(snake.head_x) * block.w;
  block.y = static_cast<int>(snake.head_y) * block.h;
  if (snake.alive) {
    SDL_SetRenderDrawColor(sdl_renderer, 0x00, 0x7A, 0xCC, 0xFF); // snake 1 - yellow head
  } else {
    SDL_SetRenderDrawColor(sdl_renderer, 0xFF, 0x00, 0x00, 0xFF); // snake 1 - red head when die
  }
  SDL_RenderFillRect(sdl_renderer, &block);

  // Render snake2's body
  SDL_SetRenderDrawColor(sdl_renderer, 0xFF, 0xFF, 0xFF, 0xFF); // snake 2 - white body
  for (SDL_Point const &point : snake2.body) {
    block.x = point.x * block.w;
    block.y = point.y * block.h;
    SDL_RenderFillRect(sdl_renderer, &block);
  }

  // Render snake2's head
  block.x = static_cast<int>(snake2.head_x) * block.w;
  block.y = static_cast<int>(snake2.head_y) * block.h;
  if (snake2.alive) {
    SDL_SetRenderDrawColor(sdl_renderer, 0x80, 0x00, 0x80, 0xFF); // snake 2 - purple head 
  } else {
    SDL_SetRenderDrawColor(sdl_renderer, 0xFF, 0x00, 0x00, 0xFF); // snake 2 - read head when die
  }
  SDL_RenderFillRect(sdl_renderer, &block);

  // Update Screen
  SDL_RenderPresent(sdl_renderer);
}

void Renderer::UpdateWindowTitle(int player1Score, int player2Score, int fps) {
  std::string title{"Snake 1 Score: " + std::to_string(player1Score) + " && Snake 2 Score: " + 
                    std::to_string(player2Score) + " && FPS: " + std::to_string(fps)};
  SDL_SetWindowTitle(sdl_window, title.c_str());
}

SDL_Renderer* Renderer::GetRenderer(){
  return sdl_renderer;
}

void Renderer::ClearScreen(){
  // Clear screen
  SDL_SetRenderDrawColor(sdl_renderer, 0, 0, 0, 255); // Set screen color to black
  SDL_RenderClear(sdl_renderer); // Draw color in the screen
}

void Renderer::PresentRenderer(){
  SDL_RenderPresent(sdl_renderer);
}