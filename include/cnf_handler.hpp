#ifndef __NP_SUDOKU_CNF_HANDLER
#define __NP_SUDOKU_CNF_HANDLER

#include <vector>
#include <memory>

#include "cnf_equation.hpp"
#include "cnf_variable.hpp"

template <class T>
class CNFHandler {
public:
  using CNFClause = std::vector<T>;

  friend CNFEquation;

  /** Creates a handler with a default-constructed
   *  CNFVariable.
   */
  CNFHandler() { }

  CNFHandler(CNFVariable variable) {
    variable_ = variable;
  }

  /** Each handler is supposed to keep a list of clauses
   *  pointing at this specific CNFVariable, and there's
   *  only supposed to be one CNFHandler per CNFEquation --
   *  copying them makes no sense!
   */
  CNFHandler(const CNFHandler& to_copy) = delete;
  CNFHandler& operator=(const CNFHandler& to_copy) = delete;
  ~CNFHandler() = default;

  //TODO: Move semantics

  /** Adds clause to clauses_ by creating a
   *  shared_ptr to point to it. Returns false
   *  if clause is already in clauses_, otherwise
   *  returns true. Does not add duplicate clauses.
   */
  bool addClause(CNFClause& new_clause) {
    for(auto itr = clauses_.begin(); itr != clauses_.end(); itr++) {
      if((**itr) == (*old_clause)) {
        return false;
      }
    }
    clauses_.push_back(make_shared<CNFClause>(new_clause));
    return true;
  }
  /** Removes given clause by checking equality
   *  with every clause in the list and removing the first
   *  clause to match.
   */
  bool removeClause(CNFClause& old_clause) {
    for(auto itr = clauses_.begin(); itr != clauses_.end(); itr++) {
      if((**itr) == (*old_clause)) {
        clauses_.erase(itr);
        return;
      }
    }
  }

  /** Returns the size of clauses_. */
  int numClauses() {
    return clauses_.size();
  }

  /** Sets variable_ to new_variable. */
  void setVariable(CNFVariable new_variable) {
    variable_ = new_variable;
  }
  /** Returns a copy of variable_. */
  CNFVariable<T> getVariable() {
    return variable_;
  }

  bool value() {
    return variable_.value();
  }
  void setValue(bool newValue) {
    variable_.setValue(newValue);
  }
  bool determined() {
    return variable_.determined();
  }
  void unset() {
    variable_.unset();
  }
  bool negated() {
    return variable_.negated();
  }
  void setNegate(bool newState) {
    variable_.setNegate(newState);
  }
  void setIdentifier(T newIdentifier) {
    variable_.setIdentifier(newIdentifier);
  }
  T getIdentifier() {
    return variable_.getIdentifier();
  }
  bool printable() {
    return variable_.printable();
  }


private:
  /** Variable wrapped by the handler object. */
  CNFVariable<T> variable_;
  /** A (not necessarily complete) list of CNFClauses
   *  containing a pointer to this variable. CNFHandler
   *  is responsible for all clauses in this object.
   *  Should contain a complete list of CNFClauses
   *  containing a pointer to this variable belonging to
   *  a specific CNFEquation for at least one CNFEquation.
   *  The pointer-references will remain valid during the
   *  lifespan of the given CNFEquation. */
  std::vector<std::shared_ptr<CNFClause> > clauses_;
};

#endif//__NP_SUDOKU_CNF_HANDLER