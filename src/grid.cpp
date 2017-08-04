#include <iostream>
#include "grid.hpp"
#include "grid_iterator.hpp"
#include "node.hpp"
#include "direction.hpp"
#include <vector>
#include <cstddef> // std::size_t
#include <random>

using std::size_t;

Grid::iterator Grid::begin() {
  return iterator(&grid2d[0][0]);
}

Grid::iterator Grid::end() const {
  return iterator(nullptr);
}

Grid::Grid(unsigned n)
  : grid2d(std::vector<std::vector<Node> >(n))
{
  for (unsigned i = 0; i < n; ++i) {
    std::vector<Node> row(n);
    for (unsigned j = 0; j < n; ++j) {
      row[j] = Node();
    }
    grid2d[i] = row;
  }
  bindNodes();
}

Grid::~Grid() { }

void Grid::bindNodes() {
  // assume n >= 2
  // using std::size_t;
  size_t gridSize = grid2d.size();

  // bind left-right
  // treat first and last nodes independently
  // first nodes in their respective rows
  for (size_t row_i = 0; row_i < gridSize; ++row_i) {
    grid2d[row_i][0].bindNode(Direction::right, &grid2d[row_i][1]);
  }
  // nodes in cols = [1, gridSize-1)
  for (size_t row_i = 0; row_i < gridSize; ++row_i) {
    for (size_t col_i = 1; col_i < gridSize - 1; ++col_i) {
      grid2d[row_i][col_i].bindNode(Direction::left, &grid2d[row_i][col_i-1]);
      grid2d[row_i][col_i].bindNode(Direction::right, &grid2d[row_i][col_i+1]);
    }
  }
  // last nodes in their respective rows
  for (size_t row_i = 0; row_i < gridSize; ++row_i) {
    grid2d[row_i][gridSize-1].bindNode(Direction::left, &grid2d[row_i][gridSize-2]);
  }

  //bind up-down
  // treat first and last nodes independently
  // first nodes in their respective columns
  for (size_t col_i = 0; col_i < gridSize; ++col_i) {
    grid2d[0][col_i].bindNode(Direction::down, &grid2d[1][col_i]);
  }
  // nodes in rows = [1, gridSize-1)
  // TODO: might swap two for-loops for better caching
  for (size_t col_i = 0; col_i < gridSize; ++col_i) {
    for (size_t row_i = 1; row_i < gridSize - 1; ++row_i) {
      grid2d[row_i][col_i].bindNode(Direction::up, &grid2d[row_i-1][col_i]);
      grid2d[row_i][col_i].bindNode(Direction::down, &grid2d[row_i+1][col_i]);
    }
  }
  // last nodes in their respective columns
  for (size_t col_i = 0; col_i < gridSize; ++col_i) {
    grid2d[gridSize-1][col_i].bindNode(Direction::up, &grid2d[gridSize-2][col_i]);
  }
}

std::vector<Node *> Grid::getEmptyNodes() {
  std::vector<Node *> emptyNodes;
  for (auto it = begin(); it != end(); ++it) {
    if ((*it).isEmpty())
      emptyNodes.push_back(&(*it));
  }
  return emptyNodes;
}

bool Grid::isFull() {
  for (auto it = begin(); it != end(); ++it) {
    if ((*it).isEmpty())
      return false;
  }
  return true;
}

int Grid::getRandomVal() const {
  static std::random_device rd;
  static std::mt19937 rng(rd());
  //static std::mt19937 rng;
  static std::uniform_int_distribution<int> dist(1,2);
  return dist(rng) * 2; // 2 or 4
}

void Grid::populate() {
  static std::random_device rd;
  static std::mt19937 rng(rd());
  std::vector<Node *> emptyNodes = getEmptyNodes();
  if (emptyNodes.empty())
    return;
  std::uniform_int_distribution<int> dist(0, emptyNodes.size()-1);
  int randIndex = dist(rng);
  //int randIndex = 6;
  //std::cout << randIndex << std::endl;
  //std::cout << "prev val: " << emptyNodes[randIndex]->val << std::endl;
  emptyNodes[randIndex]->val = getRandomVal();
  //std::cout << "end val: " << emptyNodes[randIndex]->val << std::endl;
}

void Grid::ljust() {
  Grid & grid = *this;
  for (auto & node : grid)
    //for (auto & node : row)
      if (node.left && node.left->isEmpty()) {
        *node.left = node;
        node.reset();
      }
}

void Grid::rjust() {
  Grid & grid = *this;
  for (auto & node : grid)
    //for (auto & node : row)
      if (node.right && node.right->isEmpty()) {
        *node.right = node;
        node.reset();
      }
}

void Grid::ujust() {
  Grid & grid = *this;
  for (auto & node : grid)
    //for (auto & node : row)
      if (node.up && node.up->isEmpty()) {
        *node.up = node;
        node.reset();
      }
}

void Grid::djust() {
  Grid & grid = *this;
  for (auto & node : grid)
    //for (auto & node : row)
      if (node.down && node.down->isEmpty()) {
        *node.down = node;
        node.reset();
      }
}

// TODO make justifying work with a single-pass algorithm
void Grid::justify(Direction direction) {
  extern const unsigned game_size;
  switch (direction) {
    case Direction::left:
      for (unsigned i = 0; i < game_size - 1; ++i)
	ljust();
      break;
    case Direction::right:
      for (unsigned i = 0; i < game_size - 1; ++i)
        rjust();
      break;
    case Direction::up:
      for (unsigned i = 0; i < game_size - 1; ++i)
        ujust();
      break;
    case Direction::down:
      for (unsigned i = 0; i < game_size - 1; ++i)
        djust();
      break;
  }
}

void Grid::lAdd() {
  for (auto & row : grid2d)
    for (auto it = row.begin(); it != row.end() - 1; ++it)
      (*it).addIfEqual(*(*it).right);
}

void Grid::rAdd() {
  for (auto & row : grid2d)
    for (auto it = row.rbegin(); it != row.rend() - 1; ++it)
      (*it).addIfEqual(*(*it).left);
}

void Grid::uAdd() {
  for (auto it = grid2d.begin(); it != grid2d.end() - 1; ++it)
    for (auto & node : *it)
      node.addIfEqual(*node.down);
}

void Grid::dAdd() {
  for (auto it = grid2d.rbegin(); it != grid2d.rend() - 1; ++it)
    for (auto & node : *it)
      node.addIfEqual(*node.up);
}

void Grid::add(Direction direction) {
  switch (direction) {
    case Direction::left:
      lAdd();
      break;
    case Direction::right:
      rAdd();
      break;
    case Direction::up:
      uAdd();
      break;
    case Direction::down:
      dAdd();
      break;
  }
}

void Grid::move(Direction direction) {
  justify(direction);
  add(direction);
  justify(direction);
}

std::size_t Grid::getGridSize() const {
  return grid2d.size();
}

const std::vector<std::vector<Node> > & Grid::get2d() const {
  return grid2d;
}

bool Grid::canMove() const {
  auto grid = *this;
  for (auto node : grid)
    if (node.hasEqualNeighbor() || node.isEmpty())
      return true;
  return false;
}
