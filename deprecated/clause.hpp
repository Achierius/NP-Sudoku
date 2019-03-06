#ifndef __NP_SUDOKU_CLAUSE
#define __NP_SUDOKU_CLAUSE

#include <string>
#include <vector>
#include "bit.hpp"

class Clause {
public:
  enum Operator {
    kIdentity = 0, kNegate,
    kAnd, kNand,
    kOr, kNor,
    kXor, kNxor,
  };

  Clause();
  Clause(Operator opr);
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
  Clause* getClause(int index);
  void removeClause(int index);

  int evalNum(); //0 if evaluateable, else equals the number of variables which remain undetermined
  Bit evaluate(); //Undetermined if cannot be evaluate
  bool reduce(); //Logically compact this clause and its tree of children into a smaller number of clauses; return false if nop
  bool cnf(); //Morph tree into conjunctive normal form; return false if nop

  void print_tree(bool colored = true);

  int depth();

  char display();
  std::string displayFancy();

private:
  bool identityCompress();
  bool negationDecompress();
  bool operatorCompress();
  void negationSink();
  bool negationDescend();

  std::string cCd(Operator opr); //Color code of an operator
  std::string neu(); //Neutral color code

  Operator operator_;
  std::vector<Clause> clauses_;
};

#endif//__NP_SUDOKU_CLAUSE
