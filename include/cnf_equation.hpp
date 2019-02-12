#ifndef __NP_SUDOKU_CNF_EQUATION
#define __NP_SUDOKU_CNF_EQUATION

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

  CNFEquation() : equation_(), variables_(), numVariables_(0) {

  }

  CNFEquation(const CNFEquation& to_copy) : equation_(to_copy), variables_(to_copy.variables_), numVariables_(to_copy.numVariables_) {

  }

  CNFEquation& operator=(const CNFEquation& to_copy) {
    numVariables_ = to_copy.numVariables_;
    equation_ = to_copy.equation_;
    variables_ = to_copy.variables;
  }
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
  std::vector<T> getVariables() { //TODO 1
    std::vector<T> temp;
    temp.reserve(variables_.size());
    for(CNFHandler<T> i : variables_) {
      if(i.determined()) {
        if(i.numClauses() > 0) {
          temp.push_back(i.getIdentifier());
        }
      }
    }
    return temp;
  }
  /** Returns the number of clauses a given variable
   *  appears within in equation_.
   */
  int variableNum(T identifier) { //TODO 3
    return variables_[identifier].numClauses();
  }

  /** Returns true if a variable is in use and is determined. */
  bool hasVariableValue(T identifier) const { //TODO 3
    return hasVariable(identifier) && variables_[identifier].determined();
  }
  /** Returns the value of a variable if hasValue, otherwise errors */
  bool getVariableValue(T identifier) const { //TODO 3
    assert(hasVariableValue(identifier));
    return variables_[identifier].getValue();
  }
  /** Returns true if the variable is in use. */
  bool hasVariable(T varName) const { //TODO 5
    return variableNum(varName) > 0;
  }

  /** Returns true if the given CNFClause
   *  exists within clauses_.
   */
  bool hasClause(CNFClause clause) const { //TODO 3
    for(CNFClause i : equation_) {
      if(i == clause) {
        return true;
      }
    }
  }

  /** Returns the index of the given clause,
   *  assuming it is present in equation_.
   */
  int clauseIndex(CNFClause clause) const { //TODO 2
    assert(hasClause(clause));
    int i = 0;
    for(auto itr = equation_.begin(); itr != equation_.end(); itr++) {
      if(*itr == clause) {
        return i;
      }
      i++;
    }
    return i;
  }
  /** Adds a clause to the end of _equation; returns
   *  the index of the new clause in the list. If the
   *  clause already exists, returns the index of the
   *  clauses' location within the list and does not
   *  add an additional copy.
   */
  int addClause(CNFClause new_clause) const { //TODO 3
    if(hasClause(new_clause)) {
      return clauseIndex(new_clause);
    }
    equation_.push_back(new_clause);
    return equation_.size() - 1;
  }

  /** Returns the clause at the given index.
   *  Must be a valid index.
   */
  CNFClause getClause(int index) const { //TODO 3
    assert(index < numClauses());
    return equation_[index];
  }

  /** Removes a clause at the given index. index must be < numClauses()*/
  void removeClause(int index) { //TODO 2
    assert(index < numClauses());
    auto itr = equation_.begin();
    for(int i = index; i > 0; i--) {
      itr++;
    }
    dropClause(*itr);
    equation_.erase(*itr);
  }

  /** Removes a given clause from the list. */
  void removeClause(const CNFClause& clause) { //TODO 3
    dropClause(clause);
    equation_.remove(clause);
  }

  /** Returns true if:
   *  All variables referenced by the CNFClause have values
   *  and exist within variables_,
   *  or if at least one variable referenced by the CNFClause
   *  has a value of false.
   *  Otherwise returns false.
   */
  bool canEvalClause(const CNFClause& to_eval) { //TODO 3
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
  bool evalClause(const CNFClause& to_eval) { //TODO 3
    assert(canEvalClause(to_eval));
    for(T i : to_eval) {
      if(!getVariableValue(i)) {
        return false;
      }
    }
    return true;
  }

private:
  void dropClause(const CNFClause& clause) { //TODO 2
    for(T i : clause) {
      variables_[i].removeClause(clause);
    }
  }
  void putClause(const CNFClause& clause) { //TODO 2
    for(T i : clause) {
      variables_[i].addClause(clause);
    }
  }

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
   */
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