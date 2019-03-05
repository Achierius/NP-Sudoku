#include "cnf_equation.hpp"

CNFEquation::CNFEquation() {

}

CNFEquation::CNFEquation(const CNFEquation& to_copy) {

}
CNFEquation& CNFEquation::operator=(const CNFEquation& to_copy) {

}
CNFEquation::~CNFEquation() = default;

CNFEquation::CNFEquation(const std::initializer_list<clause_t>& clauses) {

}

CNFEquation::CNFEquation(const std::initializer_list<clause_t>& clauses,
            std::initializer_list<value_t>) {

}

void CNFEquation::setVariable(variable_t variable, value_t new_val) {
  variables_[variable] = new_val;
}
void CNFEquation::setRange(variable_t min, variable_t max, value_t new_val) {
  for(variable_t i : {min, max}) {
    setVariable(i, new_val);
  }
}
void CNFEquation::setAll(value_t new_val) {
  setRange(CNF_MIN, CNF_MAX, new_val);
}

CNFEquation::value_t CNFEquation::getVariable(variable_t variable) const {
  return variables_[variable];
}

void CNFEquation::addClause(const clause_t& new_clause) {

}
void CNFEquation::removeClause(const clause_t& clause_to_delete) {

}

std::vector<std::shared_ptr<const CNFEquation::clause_t> > CNFEquation::varClauses(variable_t variable) {

}