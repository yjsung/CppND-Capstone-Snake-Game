# CPPND: Capstone Snake Game from Example code 

This is a Stake game based on the starter code which is provided by Udacity C++ Udacity C++ Nanodegree Program. (base repo: https://github.com/udacity/CppND-Capstone-Snake-Game)

# Rudbic Points
* The project uses Object Oriented Programming techniques.
  * Classes for controller/game/renderer/snake is used in the program.
* Class constructors utilize member initialization lists.
  * Initialization list is used in game/renderer/snake class constructor.
* Templates generalize functions in the project.
  * Applied Templates in message queue in renderer class.
* The project uses destructors appropriately.
  * Class destructor is well defined in renderer class.
* The project uses multithreading.
  * There are 2 thread : main and thread for renderer.

* A mutex or lock is used in the project. A condition variable is used in the project.
  * In renderer class, MessageQueue concept is applied. To apply MessageQueue concept, mutex and condition variable are used.

## Dependencies for Running Locally
* cmake >= 3.7
  * All OSes: [click here for installation instructions](https://cmake.org/install/)
* make >= 4.1 (Linux, Mac), 3.81 (Windows)
  * Linux: make is installed by default on most Linux distros
  * Mac: [install Xcode command line tools to get make](https://developer.apple.com/xcode/features/)
  * Windows: [Click here for installation instructions](http://gnuwin32.sourceforge.net/packages/make.htm)
* SDL2 >= 2.0
  * All installation instructions can be found [here](https://wiki.libsdl.org/Installation)
  * Note that for Linux, an `apt` or `apt-get` installation is preferred to building from source.
* SDL2_ttf >= 2.0
  * sudo apt-get install libsdl2-ttf-dev
* SDL_image >= 1.2.12
  * sudo apt-get install libsdl-image1.2-dev
* gcc/g++ >= 5.4
  * Linux: gcc / g++ is installed by default on most Linux distros
  * Mac: same deal as make - [install Xcode command line tools](https://developer.apple.com/xcode/features/)
  * Windows: recommend using [MinGW](http://www.mingw.org/)

## Basic Build Instructions

1. Clone this repo.
2. Make a build directory in the top level directory: `mkdir build && cd build`
3. Compile: `cmake .. && make`
4. Run it: `./SnakeGame`.

## Game Rule
1. If snake eat the food, snake's body will grow and you'll get 1 point. 
2. Every time when snake eat the food, snake's speed will be faster.
3. If snake hit the wall or itself then game is over.
