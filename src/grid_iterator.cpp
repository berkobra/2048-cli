#include "grid_iterator.hpp"
#include "node.hpp"

GridIterator::GridIterator(Node * _node_p) :
  node_p(_node_p) { }

bool GridIterator::operator==(GridIterator other) const {
  return node_p == other.node_p;
}

bool GridIterator::operator!=(GridIterator other) const {
  return !(*this == other);
}

Node & GridIterator::operator*() const {
  return *node_p;
}

GridIterator & GridIterator::operator++() {
  if (node_p -> right == nullptr) {
    if (node_p == nullptr)  return *this;

    Node *tmp = node_p;
    while (tmp -> left != nullptr) {
      tmp = tmp -> left;
    }
    tmp = tmp -> down;
    node_p = tmp;
  }
  else {
    node_p = node_p -> right;
  }
  return *this;
}

GridIterator GridIterator::operator++(int) {
  GridIterator retval = *this;
  ++(*this);
  return retval;
}
