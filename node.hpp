#ifndef NODE_H
#define NODE_H

#include "grid.hpp"

class node {
public:
  node();
  ~node();
  void operator=(const node & rhs);
  void operator+(const node & rhs);
  void operator++(); // A.val == 4 ==> (++A).val == 8
  void reset(); // A.val = 0;
private:
  node *right = nullptr;
  node *left  = nullptr;
  node *up    = nullptr;
  node *down  = nullptr;
  unsigned val = 0;
  // methods
  void bindNeighbors(); // e.g. A.right = B ==> make B.left = A
                        // used when new node is instantiated
  friend class grid;
}

#endif /* NODE_H */
