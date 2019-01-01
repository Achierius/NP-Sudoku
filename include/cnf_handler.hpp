#ifndef __NP_SUDOKU_CNF_HANDLER
#define __NP_SUDOKU_CNF_HANDLER

#include <vector>
#include <memory>

#include "cnf_equation.hpp"
#include "cnf_variable.hpp"

class CNFHandler {
public:
  friend CNFEquation;

  /** Creates a handler with a default-constructed
   *  CNFVariable.
   */
  CNFHandler();

  /** Each handler is supposed to keep a list of clauses
   *  pointing at this specific CNFVariable, and there's
   *  only supposed to be one CNFHandler per CNFEquation --
   *  copying them makes no sense!
   */
  CNFHandler(const CNFHandler& to_copy) = delete;
  CNFHandler& operator=(const CNFHandler& to_copy) = delete;
  ~CNFHandler();

  //TODO: Move semantics

  /** Adds clause to clauses_ by creating a
   *  shared_ptr to point to it. Returns false
   *  if clause is already in clauses_, otherwise
   *  returns true. Does not add duplicate clauses.
   */
  bool addClause(CNFClause& new_clause);
  /** Removes given clause by checking equality
   *  with every clause in the list and removing the first
   *  clause to match.
   */
  bool removeClause(CNFClause& old_clause);

  /** Returns the size of clauses_. */
  int numClauses();

  /** Sets variable_ to new_variable. */
  void setVariable(CNFVariable new_variable);
  /** Returns a copy of variable_. */
  CNFVariable getVariable();

  /** Does this make sense? Is it valid at all? */
  const std::vector<std::shared_ptr<CNFEquation::CNFClause> >::iterator clauses();

private:
  /** Variable wrapped by the handler object. */
  CNFVariable variable_;
  /** A (not necessarily complete) list of CNFClauses
   *  containing a pointer to this variable. CNFHandler
   *  is responsible for all clauses in this object.
   *  Should contain a complete list of CNFClauses
   *  containing a pointer to this variable belonging to
   *  a specific CNFEquation for at least one CNFEquation.
   *  The pointer-references will remain valid during the
   *  lifespan of the given CNFEquation. */
  std::vector<std::shared_ptr<CNFEquation::CNFClause> > clauses_;
};

#endif//__NP_SUDOKU_CNF_HANDLER