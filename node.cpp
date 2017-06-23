
#include "node.hpp"
#include "direction.hpp"

Node::Node(unsigned _val) : val(_val) { };

Node::~Node() { };

void Node::reset() {
  val = 0;
}

void Node::addIfEqual(Node & rhs) {
  if (*this == rhs) {
    this->val *= 2; // since they are equal, sum is essentially *=2
    rhs.reset();
  }
}

bool Node::isEmpty() const {
  return val == 0;
}

bool Node::operator==(const Node & rhs) const {
  return this->val == rhs.val;
}

void Node::bindNode(Direction direction, Node * node) {
  switch(direction) {
    case Direction::right:
      this->right = node;
      node->left = this;
      break;
    case Direction::left:
      this->left = node;
      node->right = this;
      break;
    case Direction::down:
      this->down = node;
      node->up = this;
      break;
    case Direction::up:
      this->up = node;
      node->down = this;
      break;
  }
}
