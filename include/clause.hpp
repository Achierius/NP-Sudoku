#ifndef __NP_SUDOKU_CLAUSE
#define __NP_SUDOKU_CLAUSE

#include <iostream>
#include <string>
#include <vector>
#include "bit.hpp"

class Clause {
public:
  enum class Operator {
    kIdentity = 0, kNegate,
    kAnd, kNand,
    kOr, kNor,
    kXor, kNxor,
  };

  Clause();
  Clause(std::vector<Clause> init, Operator opr);
  Clause(Clause& init, Operator opr);

  ~Clause();
  Clause(const Clause& to_copy);
  Clause& operator=(const Clause& to_copy);

  void negate();
  void setOperator(Operator new_opr);
  Operator getOperator();

  int numClauses();
  void addClause(Clause& clause);
  void insertClause(Clause& clause, int index);
  Clause& getClause(int index);
  Clause& removeClause(int index);

  int evalNum(); //0 if evaluateable, else equals the number of variables which remain undetermined
  Bit evaluate(); //Undetermined if cannot be evaluate

private:
  Operator operator_gt;
  std::vector<Clause> clauses_;
};

#endif//__NP_SUDOKU_CLAUSE
