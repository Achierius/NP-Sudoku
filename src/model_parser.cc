#include "model_parser.hpp"
#include "cnf_equation.hpp"

#include <vector>
#include <optional>

int variableID(int i, int j, int k) {
    return j + 9*i + 81*(k-1);
}

CNFEquation parseModel(const Model& model) {
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
            if (model.value(i, j)){    //Fixed number at cell in board
                eqn.addVariable(variableID(i, j, model.value(i, j).value()), false);
            }
            //Treat all cells as Undefined cells
            for (int k1 = 1; k1 <= Model::IMAX; k1++) {
                for (int k2 = k1 + 1; k2 <= Model::IMAX; k2++) {  //Starts at k1 + 1 to avoid duplicate pairs
                    CNFEquation::clause_t clause;
                    //At most one of these two variables can be true! If both are, there are two numbers in the cell.
                    //Thus, the clause is the disjunction of the two variables.
                    clause.push_back(CNFEquation::makePair(variableID(i, j, k1), false));
                    clause.push_back(CNFEquation::makePair(variableID(i, j, k2), false));
                    eqn.addClause(clause);
                }
            }
        }
    }
    //2. Every cell must have at least 1 number
    for (int i = 0; i < Model::ROWS; i++) {
        for (int j = 0; j < Model::COLS; j++) {
            CNFEquation::clause_t clause;
            for (int k = 1; k <= Model::IMAX; k++) {
                clause.push_back(CNFEquation::makePair(variableID(i, j, k), true));
            }
            eqn.addClause(clause);
        }
    }
    //3. Each row must have at most 1 of every number
    for (int j = 0; j < Model::COLS; j++) {
        for (int k = 1; k <= Model::IMAX; k++) {
            for (int i1 = 0; i1 < Model::ROWS - 1; i1++){
                for (int i2 = i1 + 1; i2 < Model::ROWS; i2++) {
                    CNFEquation::clause_t clause;
                    clause.push_back(CNFEquation::makePair(variableID(i1, j, k), false));
                    clause.push_back(CNFEquation::makePair(variableID(i2, j, k), false));
                    eqn.addClause(clause);
                }
            }
        }
    }
    //4. Each row must have at least 1 of every number
    for (int j = 0; j < Model::COLS; j++) {
        for (int k = 1; k <= Model::IMAX; k++) {
            CNFEquation::clause_t clause;
            for (int i = 0; i < Model::ROWS; i++) {
                clause.push_back(CNFEquation::makePair(variableID(i, j, k), true));
            }
            eqn.addClause(clause);
        }
    }
    //5. Each column must have at most 1 of every number
    for (int i = 0; i < Model::ROWS; i++) {
        for (int k = 1; k <= Model::IMAX; k++) {
            for (int j1 = 0; j1 < Model::COLS - 1; j1++){
                for (int j2 = j1 + 1; j2 < Model::COLS; j2++) {
                    CNFEquation::clause_t clause;
                    clause.push_back(CNFEquation::makePair(variableID(i, j1, k), false));
                    clause.push_back(CNFEquation::makePair(variableID(i, j2, k), false));
                    eqn.addClause(clause);
                }
            }
        }
    }
    //6. Each column must have at least 1 of every number
    for (int i = 0; i < Model::ROWS; i++) {
        for (int k = 1; k <= Model::IMAX; k++) {
            CNFEquation::clause_t clause;
            for (int j = 0; j < Model::COLS; j++) {
                clause.push_back(CNFEquation::makePair(variableID(i, j, k), true));
            }
            eqn.addClause(clause);
        }
    }
    //7. Each region must have at most 1 of every number
    for (int k = 1; k <= Model::IMAX; k++) {
        for (int c1 = 0; c1 < Model::REGIONS_PER_SIDE; c1++) {
            for (int c2 = 0; c2 < Model::REGIONS_PER_SIDE; c2++) {
                for (int i = 0; i < Model::REGION_ROWS; i++) {
                    for (int j = 0; j < Model::REGION_COLS; j++) {
                        for (int c3 = j + 1; c3 < Model::REGIONS_PER_SIDE; c3++) {
                            CNFEquation::clause_t clause;
                            int var_1 = variableID(3*c1 + i, 3*c2 + j, k);
                            int var_2 = variableID(3*c1 + i, 3*c2 + c3, k);
                            clause.push_back(CNFEquation::makePair(var_1, false));
                            clause.push_back(CNFEquation::makePair(var_2, false));
                            eqn.addClause(clause);
                        }
                        for (int c3 = i + 1; c3 < Model::REGIONS_PER_SIDE; c3++) {
                            for (int c4 = 1; c4 <= Model::REGIONS_PER_SIDE; c4++) {
                                CNFEquation::clause_t clause;
                                int var_1 = variableID(3*c1 + i, 3*c2 + j, k);
                                int var_2 = variableID(3*c1 + c3, 3*c2 + c4, k);
                                clause.push_back(CNFEquation::makePair(var_1, false));
                                clause.push_back(CNFEquation::makePair(var_2, false));
                                eqn.addClause(clause);
                            }
                        }
                    }
                }
            }
        }
    }
    //8. Each region must have at least 1 of every number
    //I'm very confused about this -- it's not presented in the same AND of ORs format as the other
    //equations in the paper. I've implemented a fix, but it might cause issues with the solver -- TODO
    for (int c1 = 0; c1 < Model::REGIONS_PER_SIDE; c1++) {
        for (int c2 = 0; c2 < Model::REGIONS_PER_SIDE; c2++) {
            for (int i = 0; i < Model::REGION_ROWS; i++) {
                for (int j = 0; j < Model::REGION_COLS; j++) {
                    CNFEquation::clause_t clause;
                    for (int k = 1; k <= Model::IMAX; k++) {
                        clause.push_back(CNFEquation::makePair(variableID(3*c1 + i, 3*c2 + j, k), true));
                    }
                    eqn.addClause(clause);
                }
            }
        }
    }
    return eqn;
}

Model parseEqns(const CNFEquation& eqn) {
    Model model;

    for (int i = 0; i < Model::ROWS; i++) {
        for (int j = 0; j < Model::COLS; j++) {
            for (int k = 1; k <= Model::IMAX; k++) {
                if(eqn.getVariable(variableID(i, j, k)) && eqn.getVariable(variableID(i, j, k)).value()) {
                    model.set(i, j, k);
                }
            }
        }
    }

    return model;
}

bool verifyEqns(const CNFEquation& eqn) {
    return false;
}

bool verifyModel(Model& model) {
    return false;
}
