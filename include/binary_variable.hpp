#ifndef __NP_SUDOKU_BINARY_VARIABLE
#define __NP_SUDOKU_BINARY_VARIABLE

#include "clause.hpp"

class BinaryVariable : public Clause {
public:
  void negate();
  void setOperator(Operator new_opr);

  int numClauses();
  void setClause(Clause& clause);
  Clause& getClause();

  int evalNum();
  Bit evaluate();

  void set(bool val);
  void setOn();
  void setOff();

  bool state();
  bool determined();
  void flip();

private:
  Bit value_;
};

#endif//__NP_SUDOKU_BINARY_VARIABLE