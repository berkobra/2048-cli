#ifndef VIEW_H
#define VIEW_H

#include "grid.hpp"

// TODO make generic show method to work with
// different sized win_condition's, not just 2048 (len != 4)
class View {
public:
  enum class showType {win, lose, invalid_argument, grid};
  View(const Grid & _grid);
  ~View();
  void show(showType type);
private:
  Grid grid;
  void showWin();
  void showLose();
  void showGrid();
  void showInvalidArgument();
};

#endif /* VIEW_H */
