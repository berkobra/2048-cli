#ifndef GRID_H
#define GRID_H

#include "node.hpp"
#include <vector>
#include <cstddef> // std::size_t, std::ptrdiff_t

#ifdef DEBUG
class GridTester;
#endif /* DEBUG */

class Grid {
public:
  class iterator;
  //typedef Grid::iterator iterator;
  typedef std::ptrdiff_t difference_type;
  typedef std::size_t size_type;
  typedef Node value_type;
  typedef Node * pointer;
  typedef Node & reference;

  iterator begin();
  iterator end();

  Grid(unsigned n);
  ~Grid();
  //void initializeGrid(unsigned n); // create nxn 2d vector
  void bindNodes(); // bind the nodes in the 2d vector
  //void moveLeft();
  //void moveRight();
  //void moveUp();
  //void moveDown();
  std::vector<Node *> getEmptyNodes(); // return all node A where A.val == 0
                                     // game will pick some of these randomly
                                     // to place new numbers.
  bool isFull(); // if there are nodes that are empty (val == 0)
  void populate();
  bool canMove() const;
  void move(Direction direction);
  std::size_t getGridSize() const;
  const std::vector<std::vector<Node> > & get2d() const;

private:
  std::vector<std::vector<Node> > grid2d; // wanna remove ASAP but may make
                                             // things easier in the meanwhile

  void justify(Direction direction);
  void add(Direction direction);

  void ljust();
  void rjust();
  void ujust();
  void djust();

  void lAdd();
  void rAdd();
  void uAdd();
  void dAdd();

  int getRandomVal() const;

  #ifdef DEBUG
  friend class GridTester;
  #endif /* DEBUG */
};

#endif /* GRID_H */
