#include "grid.hpp"
#include "node.hpp"
#include "direction.hpp"
#include "controller.hpp"
#include "view.hpp"
#include "game.hpp"
#include <stdexcept>
#include <iostream>

Game::Game() : grid(game_size),
               view(grid) { }

Game::~Game() { }

bool Game::isWon() {
  /*for (auto const node : grid) {
    if (node == win_condition)
      return true;
  }
  return false;*/
  for (auto it = grid.begin(); it != grid.end(); ++it) {
    if (*it == win_condition)
      //std::cout << "won" << std::endl;
      return true;
  }
  //std::cout << "not won" << std::endl;
  return false;
}

bool Game::isLost() {
  //bool lost = !grid.canMove();
  //if (lost)
    //std::cout << "lost" << std::endl;
  //else
    //std::cout << "not lost" << std::endl;
  //return lost;
  return !grid.canMove();
}

void Game::run() {
  Direction currentDirection;
  grid.populate();
  while (!isWon() && !isLost()) {
    // generate one random value
    grid.populate();
    view.show(view.showType::grid);
    bool gotDirection = false;
    while(!gotDirection) {
      try {
        currentDirection = controller.getDirection();
        gotDirection = true;
      }
      catch(const std::invalid_argument & e) {
        view.show(view.showType::invalid_argument);
        //currentDirection = controller.getDirection();
      }
    }
    grid.move(currentDirection);
  }

  // show for the last time before win or lose
  view.show(view.showType::grid);

  if (isWon()) {
    view.show(view.showType::win);
  }
  else { // isLost()
    view.show(view.showType::lose);
  }
}
