#include "view.hpp"
#include "grid.hpp"
#include <iostream>
#include <iomanip>
#include <string>
#include <sstream>
#include <cstddef> // std::size_t

View::View(const Grid & _grid) : grid(_grid) { }

View::~View() { }

void View::show(showType type) {
  switch(type) {
    case showType::win:
      showWin();
      break;
    case showType::lose:
      showLose();
      break;
    case showType::invalid_argument:
      showInvalidArgument();
      break;
    case showType::grid:
      showGrid();
      break;
  }
}

void View::showWin() {
  std::cout << "You won, congratulations!" << std::endl;
}

void View::showLose() {
  std::cout << "Game over." << std::endl;
}

void View::showInvalidArgument() {
  std::cout << "You entered invalid character(s), try again." << std::endl;
}

void View::showGrid() {
  const auto grid2d = grid.get2d();
  const int nodeWidth = 8;
  const int nodeHeight = 3; // should be an odd number

  const int gridSize = grid.getGridSize();
  /*
  const int gridWidth = nodeWidth * gridSize +
                        (gridSize + 1);
  const int gridHeight = nodeHeight * gridSize +
                         (gridSize + 1);
  */
  const std::string hNodeLine(nodeWidth, '-');

  auto repeat = [](const std::string & str, std::size_t times) {
    std::stringstream stream;
    for (std::size_t i = 0; i < times; ++i)
      stream << str;
    return stream.str();
  };

  const std::string hSeperator = " " + repeat(hNodeLine + " ", gridSize) + "\n";
  const std::string vPadding   = "|" + repeat(std::string(nodeWidth, ' ') + "|",
                                              gridSize) + "\n";
  std::stringstream grid_str;

  grid_str << hSeperator;
  for (std::size_t i = 0; i < gridSize; ++i) {
    for (int j = 0; j < (nodeHeight - 1) / 2; ++j)
      grid_str << vPadding;
    grid_str << "|";
    for (std::size_t j = 0; j < gridSize; ++j) {
      std::stringstream num_ss;
      unsigned num = grid2d[i][j].getVal();
      num_ss << num;
      int num_len = num_ss.str().length();
      const int rPadLen = (nodeWidth - num_len)/2;
      const int lPadLen = (nodeWidth - num_len) - rPadLen;
      const std::string rPad(rPadLen, ' ');
      const std::string lPad(lPadLen, ' ');
      const std::string num_str = num ? num_ss.str() : " ";
      grid_str << lPad << num_str << rPad << "|";
    }
    grid_str << "\n";
    for (int j = 0; j < (nodeHeight - 1) / 2; ++j)
      grid_str << vPadding;
    grid_str << hSeperator;
  }

  std::cout << grid_str.str() << std::endl;


/*   -------- ---
    |        |
    |  2048  |
    |        |
     --------
    |
*/

}
