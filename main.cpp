#include "game.hpp"

const unsigned game_size = 4;
const unsigned win_condition = 2048;

int main() {
  Game game;
  game.run();
  return 0;
}
