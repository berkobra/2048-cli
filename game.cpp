#include "grid.hpp"
#include "node.hpp"
#include "direction.hpp"
#include "controller.hpp"
#include "view.hpp"
#include "game.hpp"
#include <stdexcept>

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
      return true;
  }
  return false;
}

bool Game::isLost() {
  return !grid.canMove();
}

void Game::run() {
  Direction currentDirection;
  while (!isWon() && !isLost()) {
    // generate one random value
    grid.populate();
    view.show(view.showType::grid);
    try {
      currentDirection = controller.getDirection();
    }
    catch(const std::invalid_argument & e) {
      view.show(view.showType::invalid_argument);
      currentDirection = controller.getDirection();
    }
    grid.move(currentDirection);
  }

  if (isWon()) {
    view.show(view.showType::win);
  }
  else { // isLost()
    view.show(view.showType::lose);
  }
}
