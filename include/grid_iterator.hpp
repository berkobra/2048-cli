#ifndef GRID_ITERATOR_H
#define GRID_ITERATOR_H

class Node;

class GridIterator {
public:

  explicit GridIterator(Node * _node_p);
  // why not const refs?
  bool operator==(GridIterator other) const;
  bool operator!=(GridIterator other) const;
  Node & operator*() const;
  GridIterator & operator++();
  GridIterator operator++(int);

private:
  Node * node_p;
};

#endif /* GRID_ITERATOR_H */
