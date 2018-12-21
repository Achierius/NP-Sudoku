#include "bit.hpp"

void Bit::set(unsigned int value) {
  if(value) {
    this->Node::set(1);
  }
  else {
    this->Node::set(0);
  }
}

void Bit::set(bool value)  {
  if(value) {
    this->set(1U);
  }
  else {
    this->set(0U);
  }
}

void Bit::flip() {
  bool val = state();
  this->set(!val);
}

void Bit::setOff() {
  this->set(false);
}

void Bit::setOn() {
  this->set(true);
}

bool Bit::state() {
  unsigned int val = Node::value();
  if(!val) {
    return false;
  }
  return true;
}
