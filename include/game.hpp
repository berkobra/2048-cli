#ifndef GAME_H
#define GAME_H

#include "grid.hpp"
#include "view.hpp"
#include "controller.hpp"

//const unsigned game_size = 4;
//const unsigned win_condition = 2048;
extern const unsigned game_size;
extern const unsigned win_condition;

class Game {
public:
  Game();
  ~Game();
  void run();
private:
  Grid grid;
  Controller controller;
  View view;
  bool isWon();
  bool isLost();
};

#endif /* GAME_H */
