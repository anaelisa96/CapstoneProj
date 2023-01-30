#ifndef SNAKE_H
#define SNAKE_H

#include <vector>
#include "SDL.h"

class Snake {
 public:
  // Directions that snake can be travelling
  enum class Direction { kUp, kDown, kLeft, kRight };

  // Snake Constructor: accepts the grid height and width and sets a position for the head (middle of the screen)
  Snake(int grid_width, int grid_height)
      : grid_width(grid_width),
        grid_height(grid_height),
        head_x(grid_width / 2),
        head_y(grid_height / 2) {}

  // Update the snake at each game loop iteration
  void Update();

  // Once the snake eat some food this function is called
  void GrowBody();
  // Tells us if x and y are part of the snake
  bool SnakeCell(int x, int y);

  // Direction which snake is travelling - initially set to up
  Direction direction = Direction::kUp;

  float speed{0.1f}; // Speed of the snake
  int size{1}; // Size of the snake
  bool alive{true}; // Says if the snake is alive - initially set to true
  // Float coordinates of the snake head
  float head_x;
  float head_y;
  // Vector of SDL_Points with the snake body 
  // SDL_Point is a struct with integer x and y coordinates
  std::vector<SDL_Point> body;

 private:
  // When Update() is called, it calls UpdateHead()
  void UpdateHead();
  // Update the vector body with the coordintes with the of the snake body
  void UpdateBody(SDL_Point &current_cell, SDL_Point &prev_cell);

  // When the snake eats some food, we set this variable to true and in the next loop iteration the snake body grows
  bool growing{false};
  int grid_width;
  int grid_height;
};

#endif