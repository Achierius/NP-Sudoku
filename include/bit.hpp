#ifndef __NP_SUDOKU_BIT_HPP
#define __NP_SUDOKU_BIT_HPP

#include "node.hpp"

class Bit : Node {
public:
  void set(unsigned int value);
  void set(bool value);

  void flip();
  void setOn();
  void setOff();

  bool state();
private:
};

#endif//__NP_SUDOKU_BIT_HPP