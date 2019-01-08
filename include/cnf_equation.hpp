#ifndef __NP_SUDOKU_CNF_EQUATION
#define __NP_SUDOKU_CNF_EQUATION

#include "cnf_variable.hpp"
#include "cnf_handler.hpp"

#include <array>
#include <vector>
#include <memory>
#include <tuple>
#include <list>

template <class T>
class CNFEquation {
public:
  using CNFClause = std::vector<T>;

  friend CNFHandler;

  CNFEquation();

  CNFEquation(const CNFEquation& to_copy);
  CNFEquation& operator=(const CNFEquation& to_copy);
  ~CNFEquation() = default;

  /** Returns the number of clauses in equation_.
   */
  int numClauses() const { //TODO 5
    return equation_.size();
  }
  /** Returns the number of variables in variables_
   *  that are active in equation_.
   */
  int numVariables() const { //TODO 5
    return numVariables_;
  }
  /** Returns a list of variables currently in use. */
  std::vector<T> getVariables() { //TODO 3
    std::vector<T> temp;
    temp.reserve(variables_.size());
    temp.insert(temp.end(), variables_.begin(), variables_.end());
    return temp;
  }
  /** Returns the number of clauses a given variable
   *  appears within in equation_.
   */
  int variableNum(T identifier) {
    return variables_[identifier].numClauses();
  }

  /** Returns true if a variable is in use and is determined. */
  bool hasVariableValue(T identifier) {
    return hasVariable(identifier) && std::get<0>(variables_[identifier]).determined();
  }
  /** Returns the value of a variable if hasValue, otherwise errors */
  bool getVariableValue(T identifier) {
    assert(hasVariableValue(identifier));
    return std::get<0>(variables_[identifier]).getValue();
  }
  /** Returns true if the variable is in use. */
  bool hasVariable(T varName) {
    return variableNum(varName) > 0;
  }

  /** Adds a clause to the end of _equation; returns
   *  the index of the new clause in the list.
   */
  addClause(CNFClause new_clause) {
    equation_.push_back(new_clause);
    return equation_.size() - 1;
  }

  /** Returns the clause at the given index.
   *  Must be a valid index.
   */
  CNFClause getClause(int index) {
    assert(index < numClauses());
    return equation_[index];
  }

  /** Removes a clause at the given index. index must be < numClauses()*/
  void removeClause(int index) {
    assert(index < numClauses());
    auto itr = equation_.begin();
    for(int i = index; i > 0; i--) {
      itr++;
    }
    equation.erase(itr);
  }
  /**

  /** Returns true if:
   *  All variables referenced by the CNFClause have values
   *  and exist within variables_,
   *  or if at least one variable referenced by the CNFClause
   *  has a value of false.
   *  Otherwise returns false.
   */
  bool canEvalClause(const CNFClause& to_eval) {
    bool ret = true;
    for(T i : to_eval) {
      if(hasVariableValue(i)) {
        if(getVariableValue(i)) {
          return true;
        }
      } else {
        ret = false;
      }
    }
    return ret;
  }
  /** Evaluates the value of the given CNFClause by performing
   *  lookups on the CNFVariables within variables_ and
   *  logical or'ing them by eachother. If any has a value of false,
   *  evalClause will return false. If canEvalClause is false,
   *  evalClause will return false.
   */
  bool evalClause(const CNFClause& to_eval) {
    assert(canEvalClause(to_eval));
    for(T i : to_eval) {
      if(!getVariableValue(i)) {
        return false;
      }
    }
    return true;
  }

private:

  /** This is a list because we want pointers to members
   *  of this container to remain valid after a resize.
   *  Access should not actually be done through the list's
   *  access operators, but through the handlers --
   *  our SAT solver implementation will be making decisions
   *  based off of individual variables and the number of clauses
   *  they affect, so we can simply use the stored pointers
   *  each handler will contain to modify or look at the relevant
   *  clauses.
   */
  std::list<CNFClause> equation_;

  /** Stores reference data for every possible CNFVariable for
   *  this equation. If std::get<1> of an entry is 0, that
   *  variable is not present in this equation and the data inside
   *  the CNFHandler is just a placeholder. Otherwise, it is equal to
   *  the number of clauses in equation_ that reference it. All CNFHandlers
   *  and contained CNFVariables should be initialized at the construction
   *  of the CNFEquation. Each CNFHandler contains pointers to every
   *  CNFClause that contains their handled variable; it is the
   *  responsibility of the CNFEquation to keep the CNFHandler's back-
   *  reference list updated as the CNFEquation updates with new clauses.
   *  The index of a given CNFVariable in the array is equal to their
   *  identifier_ value.
   *
  std::array<CNFHandler<T>, CNFVariable<T>::NUM_IDENTIFIERS> variables_;

  /** Calculates the number of unique-identifier variables present
   *  in equation_ and assigns that value to numVariables_.
   *  Assumes variables_ is correctly updated to match the current
   *  state of equation_.
   */
  void recalcNumVariables();

  /** Number of unique-identifier variables present in equation_.
   *  Updated periodically by recalcNumVariables().
  */
  int numVariables_;
};

#endif//__NP_SUDOKU_CNF_EQUATION