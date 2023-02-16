#include "snake.h"
#include <cmath>
#include <iostream>

void Snake::Update(Snake otherSnake) {
  SDL_Point prev_cell{
      static_cast<int>(head_x),
      static_cast<int>(
          head_y)};  // We first capture the head's cell before updating.
  UpdateHead();
  SDL_Point current_cell{
      static_cast<int>(head_x),
      static_cast<int>(head_y)};  // Capture the head's cell after updating.

  // Update all of the body vector items if the snake head has moved to a new
  // cell.
  // The body of the snake is updated only if the snake head has moved to a new cell.
  if (current_cell.x != prev_cell.x || current_cell.y != prev_cell.y) {
    UpdateBody(current_cell, prev_cell, otherSnake);
  }
}

// In SDL the origin is in the left upper corner
void Snake::UpdateHead() {
  switch (direction) {
    case Direction::kUp:
      head_y -= speed; // Head moves up 
      break;

    case Direction::kDown:
      head_y += speed; // Head moves down
      break;

    case Direction::kLeft:
      head_x -= speed; // Head moves left
      break;

    case Direction::kRight:
      head_x += speed; // Head moved right
      break;
  }

  // Wrap the Snake around to the beginning if going off of the screen.
  head_x = fmod(head_x + grid_width, grid_width);
  head_y = fmod(head_y + grid_height, grid_height);
}

// The snake body updates by making the previous head cell as part of the body
void Snake::UpdateBody(SDL_Point &current_head_cell, SDL_Point &prev_head_cell, Snake otherSnake) {
  // Add previous head location to vector
  body.push_back(prev_head_cell);

  // If the snake is not growing, the tail must be removed
  if (!growing) {
    // Remove the tail from the vector.
    body.erase(body.begin());
  } else {
    // If snake must grow, the tail is not removed and the snake size increases
    growing = false;
    size++;
  }

  // Check if the snake has died, by checking if the head coordinates match with any of the body coordinates
  for (auto const &item : body) {
    if (current_head_cell.x == item.x && current_head_cell.y == item.y) {
      std::cout << "Snake hit itself." << std::endl;
      alive = false;
    }
  }

  for (auto const &item : otherSnake.body) {
   if (current_head_cell.x == item.x && current_head_cell.y == item.y) {
      std::cout << "Snakes collided." << std::endl;
      alive = false;
    }
  }
  
  if (current_head_cell.x == static_cast<int>(otherSnake.head_x) && current_head_cell.y == static_cast<int>(otherSnake.head_y)) {
      std::cout << "Snakes collided." << std::endl;
      alive = false;
  }
}

void Snake::GrowBody() { growing = true; }

// Inefficient method to check if cell is occupied by snake.
// Check if a cell is occupied by the snake
// It is used to place food in the game because we do not want to place food on top of the snake
bool Snake::SnakeCell(int x, int y) {
  if (x == static_cast<int>(head_x) && y == static_cast<int>(head_y)) {
    return true;
  }
  for (auto const &item : body) {
    if (x == item.x && y == item.y) {
      return true;
    }
  }
  return false;
}