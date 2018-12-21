#include "linear_equation.hpp"

LinearEquation::LinearEquation() {
    _constant = 0;
    _coefficients = std::vector<double>();
}

LinearEquation::LinearEquation(std::vector<double> coefficients) {
    _constant = 0;
    _coefficients = coefficients;
}

LinearEquation::LinearEquation(std::vector<double> coefficients, double constant) {
    _constant = constant;
    _coefficients = coefficients;
}

LinearEquation::~LinearEquation() { }

LinearEquation::LinearEquation(const LinearEquation& to_copy) {
    _constant = to_copy._constant;
    _coefficients = to_copy._coefficients;
}

LinearEquation& LinearEquation::operator=(const LinearEquation& to_copy) {
    _constant = to_copy._constant;
    _coefficients = to_copy._coefficients;
}

double LinearEquation::constant() const {
    return _constant;
}

double LinearEquation::coefficient(int variable) const {
    this->testIndex(variable, "coefficient");
    return _coefficients[variable];
}

std::vector<double> LinearEquation::coefficients() const {
    return _coefficients;
}

void LinearEquation::setConstant(double new_constant) {
    _constant = new_constant;
}

void LinearEquation::setCoefficient(int variable, double new_coefficient) {
    this->testIndex(variable, "setCoefficient");
    _coefficients[variable] = new_coefficient;
}

void LinearEquation::setCoefficients(const std::vector<double>& new_coefficients) {
    _coefficients = new_coefficients;
}

bool LinearEquation::validate(const std::vector<double>& values) const {
    this->testCoefficients(values, "validate");
    return test(values) == this->constant();
}

double LinearEquation::test(const std::vector<double>& values) const {
    this->testCoefficients(values, "test");

    double sum = 0;
    for(int i = 0; i < values.size(); i++) {
        sum += values[i] * this->coefficient(i);
    }

    return sum;
}

LinearEquation LinearEquation::substitute(int variable, double value) const {
    this->testIndex(variable, "substitute (single)");
    
    double constant = this->constant() - this->coefficient(variable)*value;
    std::vector<double> coefficients = this->coefficients();
    coefficients.erase(coefficients.begin() + variable);

    LinearEquation leq(coefficients, constant);
    return leq;
}

LinearEquation LinearEquation::substitute(const std::vector<int>& variables,
                                          const std::vector<double>& values) const {
    if(variables.size() != values.size()) {
        /* TODO THROW ERROR */
    }

    std::vector<double> coefficients = this->coefficients();
    double constant = this->constant();

    for(int i = 0; i < variables.size(); i++) {
        this->testIndex(variables[i], "substitute (multiple)");
        constant -= this->coefficient(variables[i])*values[i];
    }
    for(int i = variables.size() - 1; i >= 0; i--) {
        coefficients.erase(coefficients.begin() + variables[i]);
    }

    LinearEquation leq(coefficients, constant);
    return leq;
}

void LinearEquation::testCoefficients(const std::vector<double>& coefficients, 
                                      const std::string& tag) const {
    if(coefficients.size() != _coefficients.size()) {
        /* TODO THROW ERROR */
    }
}

void LinearEquation::testIndex(const int& index, const std::string& tag) const {
    if(index >= _coefficients.size()) {
        /* TODO THROW ERROR */
    }
}
