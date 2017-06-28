#ifndef NODE_H
#define NODE_H

#include "direction.hpp"

class Grid;

#ifdef DEBUG
class NodeTester;
class GridTester;
#endif /* DEBUG */

class Node {
public:
  explicit Node(unsigned _val = 0);
  ~Node();
  bool operator==(const Node & rhs) const;
  Node & operator=(const Node & rhs);
  //void operator =(const Node & rhs); // probably will not need
                                    // everything will be handled via
                                    // addition.
  //void operator +(const Node & rhs);
  //void operator ++(); // A.val == 4 ==> (++A).val == 8
                     // is this operator needed really?
  void reset(); // A.val = 0;
  void addIfEqual(Node & rhs); // this or operator+, not sure
  bool isEmpty() const; // return val == 0
  unsigned getVal() const;
private:
  Node *right = nullptr;
  Node *left  = nullptr;
  Node *up    = nullptr;
  Node *down  = nullptr;
  unsigned val;
  // methods
  //void bindNeighbors(); // e.g. A.right = B ==> make B.left = A
                        // used when new node is instantiated
  void bindNode(Direction direction, Node * node); // direction is position of
                                                   // new node relative to *this
  bool hasEqualNeighbor() const;
  friend class Grid;
  friend class GridIterator;

  #ifdef DEBUG
  friend class NodeTester;
  friend class GridTester;
  #endif /* DEBUG */
};

bool operator== (const Node & lhs, const unsigned rhs) {
  return lhs.getVal() == rhs;
}

bool operator== (const unsigned lhs, const Node & rhs) {
  return rhs == lhs;
}

#endif /* NODE_H */
