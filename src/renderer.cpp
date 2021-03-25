#include "renderer.h"
#include <iostream>
#include <string>

Renderer::Renderer(const std::size_t screen_width,
                   const std::size_t screen_height,
                   const std::size_t grid_width, const std::size_t grid_height, 
                   const std::size_t wall_width)
    : screen_width(screen_width),
      screen_height(screen_height),
      grid_width(grid_width),
      grid_height(grid_height),
      wall_width(wall_width){
  // Initialize SDL
  if (SDL_Init(SDL_INIT_VIDEO) < 0) {
    std::cerr << "SDL could not initialize.\n";
    std::cerr << "SDL_Error: " << SDL_GetError() << "\n";
  }

  TTF_Init();

  // Create Window
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
        
  font = TTF_OpenFont("/usr/share/fonts/truetype/freefont/FreeSans.ttf", 24);
  if (nullptr == font) {
    std::cout << "error while opening font\n";
  }
}

Renderer::~Renderer() {
  TTF_CloseFont(font);
  SDL_DestroyWindow(sdl_window);
  TTF_Quit();
  SDL_Quit();
}

void Renderer::Render(Snake const snake, SDL_Point const &food) {
  SDL_Rect block;
  block.w = (screen_width- 2*wall_width) / grid_width;
  block.h = (screen_height- 2*wall_width) / grid_height;
 
  // Draw Wall
  SDL_SetRenderDrawColor(sdl_renderer, 0x7F, 0x1E, 0x1E, 0xFF);
  SDL_Rect wall;
  wall.x = 0;
  wall.y = 0;
  wall.w = screen_width;
  wall.h = screen_height;
  SDL_RenderFillRect(sdl_renderer, &wall);
   
  SDL_SetRenderDrawColor(sdl_renderer, 0x1E, 0x1E, 0x1E, 0xFF);
  SDL_Rect playGround;
  playGround.x = wall_width;
  playGround.y = wall_width;
  playGround.w = screen_width - 2*wall_width;
  playGround.h = screen_height - 2*wall_width;
  SDL_RenderFillRect(sdl_renderer, &playGround);

  // Render food
  SDL_SetRenderDrawColor(sdl_renderer, 0xFF, 0xCC, 0x00, 0xFF);
  block.x = food.x * block.w;
  block.y = food.y * block.h;
  SDL_RenderFillRect(sdl_renderer, &block);

  // Render snake's body
  SDL_SetRenderDrawColor(sdl_renderer, 0xFF, 0xFF, 0xFF, 0xFF);
  for (SDL_Point const &point : snake.body) {
    block.x = point.x * block.w;
    block.y = point.y * block.h;
    SDL_RenderFillRect(sdl_renderer, &block);
  }

  // Render snake's head
  block.x = static_cast<int>(snake.head_x) * block.w;
  block.y = static_cast<int>(snake.head_y) * block.h;
  if (snake.alive) {
    SDL_SetRenderDrawColor(sdl_renderer, 0x00, 0x7A, 0xCC, 0xFF);
  } else {
    SDL_SetRenderDrawColor(sdl_renderer, 0xFF, 0x00, 0x00, 0xFF);
  }
  SDL_RenderFillRect(sdl_renderer, &block);  

  // Update Screen
  SDL_RenderPresent(sdl_renderer);
}

void Renderer::RenderText(int x, int y, const char* text) {
  SDL_Color White = {255, 255, 255};
  SDL_Surface* surfaceMessage = TTF_RenderText_Blended(font, text, White);
  SDL_Texture* texture = SDL_CreateTextureFromSurface(sdl_renderer, surfaceMessage);
  
  int msgWidth = 0, msgHeight = 0;
  SDL_QueryTexture(texture, NULL, NULL, &msgWidth, &msgHeight);
  SDL_Rect msgRect = {x, y, msgWidth, msgHeight};
  SDL_RenderCopy(sdl_renderer, texture, NULL, &msgRect);
  
  SDL_DestroyTexture(texture);
  SDL_FreeSurface(surfaceMessage);  
}


void Renderer::ScreenForStart() {
  SDL_SetRenderDrawColor(sdl_renderer, 0x1E, 0x1E, 0x1E, 0xFF);
  SDL_RenderClear(sdl_renderer); 
  RenderText(0, 0, "Snake Game");
  RenderText(0, 50, "Press space bar to start");  
  
  // Update Screen
  SDL_RenderPresent(sdl_renderer);
}

void Renderer::ScreenForDie(int score) {
  
  char charBuffer[256];
  SDL_SetRenderDrawColor(sdl_renderer, 0x7F, 0x1E, 0x1E, 0xFF);
  SDL_SetRenderDrawBlendMode(sdl_renderer, SDL_BLENDMODE_BLEND);
  SDL_Rect screen;
  screen.x = 0;
  screen.y = 0;
  screen.w = screen_width;
  screen.h = screen_height;
  SDL_RenderFillRect(sdl_renderer, &screen);
  
  sprintf(charBuffer, "Your Score : %d", score);
  RenderText(0, 0, charBuffer); 
  RenderText(0, 50, "Press Up Key to RESTART");
  RenderText(0, 100, "Press Down Key to closing");
  // Update Screen
  SDL_RenderPresent(sdl_renderer);
}

void Renderer::UpdateWindowTitle(int score, int fps) {
  std::string title{"Snake Score: " + std::to_string(score) + " FPS: " + std::to_string(fps)};
  SDL_SetWindowTitle(sdl_window, title.c_str());
}
