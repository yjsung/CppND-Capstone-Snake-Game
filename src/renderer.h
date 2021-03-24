#ifndef RENDERER_H
#define RENDERER_H

#include <vector>
#include <string>
#include "SDL.h"
#include "SDL_ttf.h"
#include "snake.h"

using namespace std;

class Renderer {
 public:
  Renderer(const std::size_t screen_width, const std::size_t screen_height,
           const std::size_t grid_width, const std::size_t grid_height, const std::size_t wall_width);
  ~Renderer();

  void Render(Snake const snake, SDL_Point const &food);
  void StartScrren();
  void UpdateWindowTitle(int score, int fps);

 private:
  SDL_Window *sdl_window;
  SDL_Renderer *sdl_renderer;
  //SDL_Surface* surfaceMessage;
  //SDL_Texture* texture;
  TTF_Font * font;
  
  const std::size_t screen_width;
  const std::size_t screen_height;
  const std::size_t grid_width;
  const std::size_t grid_height;
  const std::size_t wall_width;   
  
  void RenderText(int x, int y, const char* text);
  
};

#endif