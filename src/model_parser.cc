#include "model_parser.hpp"

#include <vector>

#include "linear_equation.hpp"

Model parseEqns(const std::vector<LinearEquation>& eqns) {
    //i, j, k -- rows, cols, number
    //We look through the vertical equations -- the first ROWS*ROWS equations!

    int rows = Model.ROWS;
    LinearEquation lneq;
    Model model;

    for(int i = 0; i < rows; i++) {
        for(int j = 0; j < rows; j++) {
            lneq = eqns[j + 9*i];
            for(int k = 1; k <= rows; k++) {
                if(lneq.coefficient(j + 9*i + 81*(k - 1)) > 0.5) {
                    model.set(i, j, k);
                }
            }
        }
    }

    return model;
}

std::vector<LinearEquation> parseModel(const Model& model) {
    //There are ROWS*ROWS*ROWS variables. We will enumerate them as follows:
    //i, j -- rows, cols respectively. k: 'number' variable, from 1-9.
    //Variable index = j + 9i + 81*(k-1)
    //Each model can be turned into a series of boolean equations by representing
    //it as a series of restrictions: 
    //1. Each vertical (i, j fixed, k free) must sum to 1
    //2. Each horizontal column (j, k fixed, i free) must sum to 1
    //3. Each horizontal row (i, k fixed, j free) must sum to 1
    //4. Each group (3x3 regions in i,j, k fixed) must sum to 1

    int rows = Model.ROWS;

    std::vector<LinearEquation> equations;
    std::vector<double> zeroes;

    for(int n = 0; n < rows*rows*rows; n++) {
        zeroes.push_back(0);
    }

    for(int i = 0; i < rows; i++) { //Verticals
        for(int j = 0; j < rows; j++) {
            equations.emplace_back(zeroes, 1);
            for(int k = 1; k <= rows; k++) {
                equations.back().setCoefficient(j + 9*i + 81*(k-1), 1);
            }
        }
    }
    for(int j = 0; j < rows; j++) { //Horizontal Columns
        for(int k = 1; k <= rows; k++) {
            equations.emplace_back(zeroes, 1);
            for(int i = 0; i < rows; i++) {
                if(model.value(i, j) == k) {
                    equations.back().setCoefficient(j + 9*i + 81*(k-1), 1);
                }
            }
        }
    }
    for(int i = 0; i < rows; i++) { //Horizontal Rows
        for(int k = 1; k <= rows; k++) {
            equations.emplace_back(zeroes, 1);
            for(int j = 0; j < rows; j++) {
                if(model.value(i, j) == k) {
                    equations.back().setCoefficient(j + 9*i + 81*(k-1), 1);
                }
            }
        }
    }
    for(int n = 0; n < Model.REGIONS; n++) { //Groups/Regions
        for(int k = 1; k <= rows; k++) {
            equations.emplace_back(zeroes, 1);
            for(int i = 0; i < Model.REGION_ROWS; i++) {
                for(int j = 0; j < Mode.REGION_COLS; j++) {
                    if(mode.value(i, j) == k) {
                        equations.back().setCoefficient(
                                i + 81*(k - 1) + ((rows / Model.REGIONS_PER_SIDE)
                                * ((n / Model.REGIONS_PER_SIDE)),
                                j + 81*(k - 1) + ((cols / Model.REGIONS_PER_SIDE)
                                * (n % Model.REGIONS_PER_SIDE)));
                    }
                }
            }
        }
    }
    
    return equations;
}

bool verifyEqns(const std::vector<LinearEquation>& eqns) {
    std::vector<double> ones;
    int rows = Model.ROWS;

    for(int n = 0; n < rows*rows*rows; n++) {
        zeroes.push_back(0);
    }

    for(auto itr = eqns.begin(); itr != eqns.end(); itr++) {
        if(!itr.validate(ones)) {
            return false;
        }
    }
    
}

bool verifyModel(Model& model) {
    std::vector<LinearEquation> eqns = parseModel(model);

    return verifyEqns(eqns);
}
