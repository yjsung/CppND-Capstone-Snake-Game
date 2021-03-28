#include <iostream>
#include "controller.h"
#include "game.h"
#include "renderer.h"
#include <thread>

int main() {
  constexpr std::size_t kFramesPerSecond{50};
  constexpr std::size_t kMsPerFrame{1000 / kFramesPerSecond};
  constexpr std::size_t kScreenWidth{680}; // 340
  constexpr std::size_t kScreenHeight{680}; // 340
  constexpr std::size_t kGridWidth{34};
  constexpr std::size_t kGridHeight{34};
  constexpr std::size_t kWallWidth{20};

  Renderer renderer(kScreenWidth, kScreenHeight, kGridWidth, kGridHeight, kWallWidth);
  Controller controller;  
  Game game(kGridWidth, kGridHeight, kWallWidth); 
  std::thread t1{ &Renderer::RenderThread, &renderer};
  game.Run(controller, renderer, kMsPerFrame); 
  
  t1.join();
  
  std::cout << "Game has terminated successfully!\n";
  std::cout << "Score: " << game.GetScore() << "\n";
  std::cout << "Size: " << game.GetSize() << "\n";
  return 0;
}