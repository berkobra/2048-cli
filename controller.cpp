#include "direction.hpp"
#include "controller.hpp"
#include <iostream>
#include <string>
#include <stdexcept>

Controller::Controller() { }

Controller::~Controller() { }

Direction Controller::_getDirection(const std::string & input) const {
  if (input == "a")
      return Direction::left;
  if (input == "d")
      return Direction::right;
  if (input == "s")
      return Direction::down;
  if (input == "w")
      return Direction::up;
  throw std::invalid_argument("Received input is not in {w,a,s,d}.");
}

const std::string Controller::getInput() const {
  std::string input;
  std::cin >> input;
  return input;
}

Direction Controller::getDirection() const {
  return _getDirection(getInput());
}
