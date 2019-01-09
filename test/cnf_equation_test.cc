#include "cnf_handler.hpp"
#include "cnf_variable.hpp"
#include "cnf_equation.hpp"

#include <assert.h>

void testVariableNumIdentifiers() {
  assert(CNFVariable<int8_t>::NUM_IDENTIFIERS == 128);
  assert(CNFVariable<int32_t>::NUM_IDENTIFIERS == 2147483648);
  assert(CNFVariable<uint8_t>::NUM_IDENTIFIERS == 128);
  assert(CNFVariable<uint32_t>::NUM_IDENTIFIERS == 2147483648);
  assert(CNFVariable<char>::NUM_IDENTIFIERS == 128);
  assert(CNFVariable<unsigned char>::NUM_IDENTIFIERS == 128);
}

int main() {
  testVariableNumIdentifiers();
}