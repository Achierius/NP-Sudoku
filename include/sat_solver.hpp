#ifndef __NP_SUDOKU_SAT_SOLVER
#define __NP_SUDOKU_SAT_SOLVER

#include <vector>

#include "cnf_equation.hpp"
#include "cnf_variable.hpp"

class SatSolver {
public:
  SatSolver();
  SatSolver(CNFEquation eqn);
  SatSolver(std::vector<CNFEquation::CNFClause> clauses);

  ~SatSolver();
  SatSolver(const SatSolver& to_copy);
  SatSolver& operator=(const SatSolver& to_copy);

  void setEquation(CNFEquation eqn);
  void setEquation(std::vector<CNFEquation::CNFClause> clauses);

  virtual bool satisfiable() = 0;
  virtual std::vector<CNFVariable> solve() = 0;

private:
  CNFEquation equation_;
};

#endif//__NP_SUDOKU_SAT_SOLVER