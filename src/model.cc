#include "model.hpp"

#include <assert.h>

Model::Model() {
    for(int i = 0; i < ROWS*COLS; i++) {
        _grid[i].reset();
    }
}

Model::Model(Model::Grid grid) {
    for(int i = 0; i < ROWS*COLS; i++) {
        _grid[i] = grid[i];
    }
}

Model::~Model() {
}

Model::Model(const Model& to_copy) {
    for(int i = 0; i < ROWS*COLS; i++) {
        _grid[i] = to_copy._grid[i];
    }
}

Model& Model::operator=(const Model& to_copy) {
    for(int i = 0; i < ROWS*COLS; i++) {
        _grid[i] = to_copy._grid[i];
    }
}

void Model::unset(int region, int row, int col) {
    unset(getIndex(region, row, col));
}

void Model::unset(int row, int col) {
    unset(getIndex(row, col));
}

void Model::unset(int index) {
    assert(index >= 0 && index < ROWS*COLS);

    _grid[index].reset();
}

void Model::set(int region, int row, int col, int value) {
    set(getIndex(region, row, col), value);
}

void Model::set(int row, int col, int value) {
    set(getIndex(row, col), value);
}

void Model::set(int index, int value) {
    assert(index >= 0 && index < ROWS*COLS);

    _grid[index] = value;
}

Model::Node Model::value(int region, int row, int col) const {
    return value(getIndex(region, row, col));
}

Model::Node Model::value(int row, int col) const {
    return value(getIndex(row, col));
}

Model::Node Model::value(int index) const {
    assert(index >= 0 && index < ROWS*COLS);

    return _grid[index].value();
}

int Model::getIndex(int region, int row, int col) const {
    return getIndex(row + ((ROWS / REGIONS_PER_SIDE) * (region / REGIONS_PER_SIDE)),
                    col + ((COLS / REGIONS_PER_SIDE) * (region % REGIONS_PER_SIDE)));
}

int Model::getIndex(int row, int col) const {
    return col + (ROWS * row);
}

bool Model::determined() const {
    for(int i = 0; i < ROWS*COLS; i++) {
        if(!_grid[i]) {
            return false;
        }
    }
    return true;
}
