#include "cnf_equation.hpp"

CNFEquation::CNFEquation() {

}

CNFEquation::CNFEquation(const CNFEquation& to_copy) {

}
CNFEquation& CNFEquation::operator=(const CNFEquation& to_copy) {

}
CNFEquation::~CNFEquation() = default;

CNFEquation::CNFEquation(const std::initializer_list<cnf_clause_t>& clauses) {

}

CNFEquation::CNFEquation(const std::initializer_list<cnf_clause_t>& clauses,
            std::initializer_list<value_t>) {

}

void CNFEquation::setVariable(variable_t variable, value_t new_value) {

}
void CNFEquation::setRange(variable_t min, variable_t max, value_t new_value) {

}
void CNFEquation::setAll(value_t new_value) {

}

CNFEquation::value_t CNFEquation::getVariable(variable_t variable) const {

}