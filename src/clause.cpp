#include "clause.hpp"

Clause::Clause() {
}

Clause::Clause(std::vector<Clause> init, Operator opr) {

}

Clause::Clause(Clause& init, Operator opr) {

}

Clause::~Clause() {

}

Clause& Clause::operator=(const Clause& to_copy) {

}

Clause::Clause(const Clause& to_copy) {

}

void Clause::negate() {

}

void Clause::setOperator(Clause::Operator new_opr) {

}

Clause::Operator Clause::getOperator() {

}

int Clause::numClauses() {

}

void Clause::addClause(Clause& clause) {

}

void Clause::insertClause(Clause& clause, int index) {

}

Clause& Clause::getClause(int index) {

}

Clause& Clause::removeClause(int index) {

}

int Clause::evalNum() {

}

Bit Clause::evaluate() {

}