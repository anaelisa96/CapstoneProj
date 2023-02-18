#ifndef SNAKE_H
#define SNAKE_H

#include <vector>
#include "SDL.h"

class Snake {
 public:
  // Directions that snake can be travelling
  enum class Direction { kUp, kDown, kLeft, kRight };

  Snake(int grid_width, int grid_height)
      : grid_width(grid_width),
        grid_height(grid_height){}

  void setPosition(float x, float y){
  	head_x = x;
    head_y = y;
  }

  // Update the snake at each game loop iteration
  void Update(Snake otherSnake);

  // Once the snake eat some food this function is called
  void GrowBody();
  
  // Tells us if x and y are part of the snake
  bool SnakeCell(int x, int y);

  // Direction which snake is travelling - initially set to up
  Direction direction = Direction::kUp;

  float speed{0.1f};
  int size{1};
  bool alive{true};
  float head_x;
  float head_y;
  // Vector of SDL_Points with the snake body 
  std::vector<SDL_Point> body;

 private:
  void UpdateHead();
  void UpdateBody(SDL_Point &current_cell, SDL_Point &prev_cell, Snake otherSnake);

  bool growing{false};
  int grid_width;
  int grid_height;
};

#endif