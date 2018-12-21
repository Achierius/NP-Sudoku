#include "model.hpp"

Model::Model() {
    _grid = new Node[ROWS*COLS];
    
    for(int i = 0; i < ROWS*COLS; i++) {
        _grid[i].empty();
    }
}

Model::Model(Model::Grid grid) {
    _grid = new Node[ROWS*COLS];
    
    for(int i = 0; i < ROWS*COLS; i++) {
        _grid[i] = grid[i];
    }
}

~Model() {
    delete[] grid;
}

Model::Model(const Model& to_copy) {
    _grid = new Node[ROWS*COLS];

    for(int i = 0; i < ROWS*COLS; i++) {
        _grid[i] = to_copy._grid[i];
    }
}

Model& Model::operator=(const Model& to_copy) {
    for(int i = 0; i < ROWS*COLS; i++) {
        _grid[i] = to_copy._grid[i];
    }
}

void Model::undetermine(int region, int row, int col) {
    undetermine(getIndex(region, row, col));
}

void Model::undetermine(int row, int col) {
    undetermine(getIndex(row, col));
}

void Model::undetermine(int index) {
    assert(index >= 0 && index < ROWS*COLS);

    _grid[i].empty();
}

void Model::set(int region, int row, int col, unsigned int value) {
    set(getIndex(region, row, col, value);
}

void Model::set(int row, int col, unsigned int value) {
    set(getIndex(row, col), value);
}

void Model::set(int index, unsigned int value) {
    assert(index >= 0 && index < ROWS*COLS);

    _grid[index] = value;
}

unsigned int Model::value(int region, int row, int col) {
    return value(getIndex(region, row, col));
}

unsigned int Model::value(int row, int col) {
    return value(getIndex(row, col));
}

unsigned int Model::value(int index) {
    assert(index >= 0 && index < ROWS*COLS);

    return _grid[index].value();
}

int Model::getIndex(int region, int row, int col) {
    return getIndex(row + ((ROWS / REGIONS_PER_SIDE) * (region / REGIONS_PER_SIDE)),
                    col + ((COLS / REGIONS_PER_SIDE) * (region % REGIONS_PER_SIDE)))
}

int Model::getIndex(int row, int col) {
    return col + (ROWS * row);
}
