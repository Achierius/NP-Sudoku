#include "cnf_handler.hpp"
#include "cnf_variable.hpp"
#include "cnf_equation.hpp"

#include <assert.h>
#include <iostream>

void testVariableNumIdentifiers() {
  assert(CNFVariable<int8_t>::NUM_IDENTIFIERS == 128);
  assert(CNFVariable<int32_t>::NUM_IDENTIFIERS == 2147483648);
  assert(CNFVariable<uint8_t>::NUM_IDENTIFIERS == 128);
  assert(CNFVariable<uint32_t>::NUM_IDENTIFIERS == 2147483648);
  assert(CNFVariable<uint64_t>::NUM_IDENTIFIERS == 9223372036854775808ull);
  assert(CNFVariable<char>::NUM_IDENTIFIERS == 128);
  assert(CNFVariable<unsigned char>::NUM_IDENTIFIERS == 128);
}

void testVariableConstruct() {
  CNFVariable<int> v1;
  CNFVariable<int> v2(3);
  CNFVariable<int> v3(5, true);

  assert(v1.determined() == false);
  assert(v2.determined() == false);
  assert(v3.determined() == true);

  assert(v2.negated() == false);
  assert(v3.negated() == false);
  assert(v1.negated() == false);


  assert(v1.getIdentifier() == 1);
  assert(v3.getIdentifier() == 5);
  assert(v2.getIdentifier() == 3);

  assert(v3.value() == true);
}

void testVariableNegations() {
  CNFVariable<int> v1(3);
  CNFVariable<int> v2(-3);
  assert(v1.negated() == false);
  assert(v2.negated() == true);
  assert(v1.getIdentifier() == 3);
  assert(v2.getIdentifier() == -3);
  v1.setNegate(true);
  v2.setNegate(false);
  assert(v1.getIdentifier() == -3);
  assert(v2.getIdentifier() == 3);
  v1.setIdentifier(-5);
  assert(v1.getIdentifier() == -5);
  assert(v1.negated() == true);
  v1.negate();
  assert(v1.getIdentifier() == 5);
  assert(v1.negated() == false);
  v1.negate();
  assert(v1.getIdentifier() == -5);
  assert(v1.negated() == true);
}

void testVariableValues() {
  CNFVariable<int> mem;
  assert(mem.determined() == false);
  mem.setValue(true);
  assert(mem.value() == true);
  mem.negate();
  assert(mem.value() == false);
  mem.unset();
  assert(mem.determined() == false);
}

int main() {
  testVariableNumIdentifiers();
  testVariableConstruct();
  testVariableNegations();
  testVariableValues();
}