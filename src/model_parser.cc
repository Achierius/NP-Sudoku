#include "model_parser.hpp"

#include <vector>
#include <optional>

int variableID(int i, int j, int k) {
    return j + 9*i + 81*(k-1);
}

CNFEquation& parseModel(const Model& model) {
    //There are ROWS*ROWS*ROWS variables. We will enumerate them as follows:
    //i, j -- rows, cols respectively. k: 'number' variable, from 1-9.
    //Variable index = j + 9i + 81*(k-1)
    //Each model can be turned into a series of boolean equations by representing
    //it as a series of restrictions:
    //1. Each vertical (i, j fixed, k free) must have exactly 1 true value
    //2. Each horizontal column (j, k fixed, i free) must sum to 1
    //3. Each horizontal row (i, k fixed, j free) must sum to 1
    //4. Each group (3x3 regions in i,j, k fixed) must sum to 1
    CNFEquation eqn;

    //1.  Every cell must have at most 1 number
    //1a. Every vertical in the varspace must have at most 1 true variable
    //1b. Every cell with a defined variable in the model must have that variable true in the equation
    for (int i = 0; i < Model::ROWS; i++) {
        for (int j = 0; j < Model::COLS; j++) {
            if (model.value(i, j)) {    //Fixed number at cell in board
                eqn.addVariable(variableID(i, j, model.value(i, j).value()), false);
            } else {                    //Undefined cell
                for (int k1 = 1; k1 <= 9; k1++) {
                    for (int k2 = k1 + 1; k2 <= 9; k2++) {  //Starts at k1 + 1 to avoid duplicate pairs
                        CNFEquation::clause_t clause;
                        //At most one of these two variables can be true! If both are, there are two numbers in the cell.
                        //Thus, the clause is the disjunction of the two variables.
                        clause.push_back(CNFEquation::makePair(variableID(i, j, k1), true));
                        clause.push_back(CNFEquation::makePair(variableID(i, j, k2), true));
                        eqn.addClause(clause);
                    }
                }
            }
        }
    }
    for (int i = 0; i < Model::ROWS; i++) {
        for (int j = 0; j < Model::COLS; j++) {
            CNFEquation::clause_t clause;
            for (int k = 1; k < Model::COLS; k++) {
                clause.push_back(CNFEquation::makePair(variableID(i, j, k), true));
            }
            eqn.addClause(clause);
        }
    }
}
bool verifyEqns(const CNFEquation& eqn) {
    return false;
}

bool verifyModel(Model& model) {
    return false;
}
