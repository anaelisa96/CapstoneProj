# CPPND: Capstone Snake Game Example

This is a starter repo for the Capstone project in the [Udacity C++ Nanodegree Program](https://www.udacity.com/course/c-plus-plus-nanodegree--nd213). The code for this repo was inspired by [this](https://codereview.stackexchange.com/questions/212296/snake-game-in-c-with-sdl) excellent StackOverflow post and set of responses.

<img src="snake_game.gif"/>

This is the Capstone Project project I decided to do for Udacity C++ Nanodegree Program. The project consists in an extension of the Snake Game. To the [code provided by Udacity](https://github.com/udacity/CppND-Capstone-Snake-Game), the following features were added:
* **Two Players Game:** The game can only be played with two people. To accomplish this, a 2nd snake was added and is controlled with 'w', 'a', 's' and 'd' keys.
* **Welcome Screen:** When the code is launched an introduction screen is presented. The screen cointains the game title, the game logo and some instructions to start the game. In this screen, the two players can also insert their usernames using the PC keyboard. Both players must insert at least one character to start the game and player 1 must insert their username first (the code is protected for incorrect use at this level).
* **Scores Tracking:** By writing and reading from an external file (scores.txt), the game keeps track of not only the scores of the current game for the two players but also their best scores and new records.
* **GameOver Screen:** The game overs in one of the following 3 scenarios: one of the snakes hits itself, the two snakes collide or the game windows is closed. In these scenarios, a GameOver screen is presented with a title, the players usernames, their current scores, their best scores, the info that a new record was achieved, if that is the case, and lastly the result of the game (who won or if it was a tie). The game window automatically closes 10 seconds after the GameOver screen is presented.

## How this project satisfy the rubric items
* **Loops, Functions, I/O**
  - **A variety of control structures are used in the project. The project is clearly organized into functions.**
  Along the code multiple if statements, switch statements and while loops are used to control variables and vary the code flow according to different situations: *game.cpp - lines 215 to 263; controller.cpp - lines 13 to 60 (there are other examples!).*
  - **The project reads data from an external file or writes data to a file as part of the necessary operation of the program.**
  The program keeps tracking of the players' scores obtained at each time the game is played by writing them down to an external file. In addition, the program also reads from that file to check for best score or new records of the current players: *game.cpp - lines 206 to 267.*
  - **The project accepts input from a user as part of the necessary operation of the program.**
  The program accepts input from the keyboard when presents a welcome screen for the two players insert their usernames and during the game itself to move both snakes: *welcomeScreen.cpp - lines 22 to 44; controller.cpp - lines 10 to 61, respectively.*
* **Object Oriented Programming**
  - **The project code is organized into classes with class attributes to hold the data, and class methods to perform tasks.**
  - **All class data members are explicitly specified as public, protected, or private.**
  - **All class member functions document their effects, either through function names, comments, or formal documentation. Member functions do not change program state in undocumented ways.**
  - **Appropriate data and functions are grouped into classes. Member data that is subject to an invariant is hidden from the user. State is accessed via member functions.**
  All the project code in general fulfils the four above criteria: *welcomeScreen.h and game.h are good examples.*
  - **All class members that are set to argument values are initialized through member initialization lists.**
  All classes in *welcomeScreen.h* and the Game class in *game.cpp (lines 32 to 46)* fulfill this criteria.
  - **Inheritance hierarchies are logical. Override functions are specified.**
  Class WelcomeScreen (parent) and classes Text and Image (children) follow a logical hierarchical relationship: *welcomeScreen.h - all file*. Function `void PositionElement()` is overridden in the Image Class: *welcomeScreen.cpp - lines 3 to 7 (parent class) and lines 110 to 118 (child class)*.
  - **One function is declared with a template that allows it to accept a generic parameter.**
  Function `void CopytoRender(T obj)` is declared with a template in *renderer.h - lines 18 to 21* and is used several times along the *game.cpp - lines 138 to 147, 333 to 341* and in *controller.cpp - lines 28 to 29*.
* **Memory Management**
  - **At least two functions use pass-by-reference in the project code.**
  Several functions along the code use pass-by-reference. Some examples are in *game.h - lines 45, 46 and 49; welcomeScreen.h - line 51*.
  - **The project follows the Resource Acquisition Is Initialization pattern where appropriate, by allocating objects at compile-time, initializing objects when they are declared, and utilizing scope to ensure their automatic destruction.**
  The declaration of Text class objects for the GameOver screen are a good example of this criteria application: *game.cpp - lines 303 to 308*.
  - **The project uses at least one smart pointer: shared_ptr.**
  The Text and Image classes accept one parameter each of type shared pointer (`std::shared_ptr<std::string> text` and `std::shared_ptr<const char*> imgPath`, respectively). Variables of this type are declared along the code: *main.cpp - lines 16 to 21* and *game.h - lines 27 to 28 and 32 to 37* and are used as parameters of the constructors to create objects of these classes: *game.cpp - lines 36 to 41 and lines 303 to 308*.

## Dependencies for Running Locally
* cmake >= 3.7
  * All OSes: [click here for installation instructions](https://cmake.org/install/)
* make >= 4.1 (Linux, Mac), 3.81 (Windows)
  * Linux: make is installed by default on most Linux distros
  * Mac: [install Xcode command line tools to get make](https://developer.apple.com/xcode/features/)
  * Windows: [Click here for installation instructions](http://gnuwin32.sourceforge.net/packages/make.htm)
* SDL2 >= 2.0
  * All installation instructions can be found [here](https://wiki.libsdl.org/Installation)
  >Note that for Linux, an `apt` or `apt-get` installation is preferred to building from source. 
* gcc/g++ >= 5.4
  * Linux: gcc / g++ is installed by default on most Linux distros
  * Mac: same deal as make - [install Xcode command line tools](https://developer.apple.com/xcode/features/)
  * Windows: recommend using [MinGW](http://www.mingw.org/)

## Basic Build Instructions

1. Clone this repo.
2. Make a build directory in the top level directory: `mkdir build && cd build`
3. Install SDL2-TTF library: `sudo apt install libsdl2-ttf-dev`
4. Compile: `cmake .. && make`
5. Run it: `./SnakeGame`.


## CC Attribution-ShareAlike 4.0 International


Shield: [![CC BY-SA 4.0][cc-by-sa-shield]][cc-by-sa]

This work is licensed under a
[Creative Commons Attribution-ShareAlike 4.0 International License][cc-by-sa].

[![CC BY-SA 4.0][cc-by-sa-image]][cc-by-sa]

[cc-by-sa]: http://creativecommons.org/licenses/by-sa/4.0/
[cc-by-sa-image]: https://licensebuttons.net/l/by-sa/4.0/88x31.png
[cc-by-sa-shield]: https://img.shields.io/badge/License-CC%20BY--SA%204.0-lightgrey.svg
