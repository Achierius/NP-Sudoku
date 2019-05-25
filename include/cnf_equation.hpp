#ifndef __NP_SUDOKU_CNF_EQUATION_H
#define __NP_SUDOKU_CNF_EQUATION_H

#include <array>
#include <vector>
#include <memory>
#include <tuple>
#include <list>
#include <utility>
#include <optional>
#include <initializer_list>

class CNFEquation {
public:
  using value_t                   = std::optional<bool>;
  using variable_t                = uint64_t;
  using clause_t                  = std::vector<std::pair<variable_t, bool> >;
  const static variable_t CNF_MAX = UINT64_MAX;
  const static variable_t CNF_MIN = 0;

  CNFEquation();
  CNFEquation(const CNFEquation& to_copy);
  CNFEquation& operator=(const CNFEquation& to_copy);
  ~CNFEquation();

  void setVariable(variable_t variable, value_t new_value);
  void setRange(variable_t min, variable_t max, value_t new_value); //Min and max inclusive
  void setAll(value_t new_value);

  value_t getVariable(variable_t variable) const;

  variable_t maxVariable() const; //Returns the index of the maximum variable currently included in a clause in clauses_

  static std::pair<variable_t, bool> makePair(variable_t variable, bool negated);
  void addVariable(variable_t, bool);
  void addClause(const clause_t& new_clause);
  void removeClause(const clause_t& clause_to_delete);

  int numClauses();
  const std::list<std::shared_ptr<clause_t> > allClauses();
  const std::vector<std::shared_ptr<clause_t> > varClauses(variable_t variable);

private:
  void reparseCReferences(); //Recalculates all vectors of shared_ptr<snf_clause_t> in variables_
  void reparseMaxVariable(); //Recalculates the correct value of max_variable

  std::list<std::shared_ptr<clause_t> > clauses_;
  std::array<value_t, CNF_MAX+1> variables_;
  std::array<std::vector<std::shared_ptr<clause_t> >, CNF_MAX+1> references_;
  variable_t max_variable_;
};

#endif//__NP_SUDOKU_CNF_EQUATION_H
