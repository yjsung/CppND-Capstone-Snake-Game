#ifndef RENDERER_H
#define RENDERER_H

#include <vector>
#include <string>
#include "SDL.h"
#include "SDL_ttf.h"
#include "SDL_image.h"
#include "snake.h"

#include <mutex>
#include <deque>
#include <condition_variable>


using namespace std;

template <class T>
class MessageQueue
{
public:
	T receive();    
    void send(T &&msg);
    
private:
    std::deque<T> _queue;
    std::condition_variable _cond;
    std::mutex _mutex;
};

class Renderer {
 public:
  Renderer(const std::size_t screen_width, const std::size_t screen_height,
           const std::size_t grid_width, const std::size_t grid_height);
  ~Renderer();

  void Render(Snake const snake);
  void ScreenForStart();
  void ScreenForDie(int score);
  void UpdateWindowTitle(int score);
  void RenderThread(); 
  
  void InvokeRenderThread(Snake msg);

 private:
  SDL_Window *sdl_window;
  SDL_Renderer *sdl_renderer;
  TTF_Font * font;
  
  SDL_Surface *imgSurfaceForStartScreen = NULL;
  SDL_Texture *imgTextureForStartScreen = NULL;
  SDL_Rect imgPosition;
  
  const std::size_t screen_width;
  const std::size_t screen_height;
  const std::size_t grid_width;
  const std::size_t grid_height;
  
  void RenderText(int x, int y, const char* text);
  
  MessageQueue<Snake> queue;
  
};

#endif