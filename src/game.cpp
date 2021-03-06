#include "game.h"
#include <iostream>
#include "SDL.h"

Game::Game(std::size_t grid_width, std::size_t grid_height)
    : snake(grid_width, grid_height),
      engine(dev()),
      random_w(0, static_cast<int>(grid_width)),
      random_h(0, static_cast<int>(grid_height)),
	  grid_width(grid_width), grid_height(grid_height){
  PlaceFood();
}

void Game::Run(Controller const &controller, Renderer &renderer,
           std::size_t target_frame_duration) {
  Uint32 title_timestamp = SDL_GetTicks();
  Uint32 frame_start;
  Uint32 frame_end;
  Uint32 frame_duration;
  int frame_count = 0;

  while (snake.running) {
    frame_start = SDL_GetTicks();
    
    switch (snake.gPhase) {
      case START :
        controller.HandleInput(snake);
        break;
      case RUNNING:
        // Input, Update, Render - the main game loop.
        controller.HandleInput(snake);
        Update();
        break;
        
      case DIE:
        controller.HandleInput(snake);
        if (snake.gPhase == RUNNING) {
          snake.Reset();
          score = 0;
        }
        break;
        
      case CLOSING:        
        snake.running = false;
        break;
        
      default:
        break;    
    }
    snake.score = score;    
    frame_end = SDL_GetTicks();
    // Keep track of how long each loop through the input/update/render cycle
    // takes.
    frame_duration = frame_end - frame_start;

    // If the time for this frame is too small (i.e. frame_duration is
    // smaller than the target ms_per_frame), delay the loop to
    // achieve the correct frame rate.
    if (frame_duration < target_frame_duration) {
      SDL_Delay(target_frame_duration - frame_duration);
    }    
    // send mst to renderer thread    
    renderer.InvokeRenderThread(snake);    
  }
}

void Game::PlaceFood() {
  int x, y;
  while (true) {
    x = random_w(engine);
    y = random_h(engine);
    // Check that the location is not occupied by a snake item before placing
    // food.
    if (!snake.SnakeCell(x, y) && 
        (x > 1 && y > 1) &&
        (x < (grid_width - 1) && y < (grid_height - 1)) ) {
      snake.food.x = x;
      snake.food.y = y;
      return;
    }
  }
}

void Game::Update() {
  if (!snake.alive) {
    snake.gPhase = DIE;
    return;    
  }

  snake.Update();

  int new_x = static_cast<int>(snake.head_x);
  int new_y = static_cast<int>(snake.head_y);

  // Check if there's food over here
  if (snake.food.x == new_x && snake.food.y == new_y) {
    score++;
    PlaceFood();
    // Grow snake and increase speed.
    snake.GrowBody();
    snake.speed += 0.02;
  }
}

int Game::GetScore() const { return score; }
int Game::GetSize() const { return snake.size; }