#ifndef CONTROLLER_H
#define CONTROLLER_H

#include "direction.hpp"
#include <string>

class Controller {
public:
  Controller();
  ~Controller();
  Direction getDirection() const;
private:
  Direction _getDirection(const std::string & input) const;
  const std::string getInput() const;
};

#endif /* CONTROLLER_H */
