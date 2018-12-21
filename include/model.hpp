#ifndef __NP_SUDOKU_MODEL
#define __NP_SUDOKU_MODEL

#include "Node.hpp"

class Model {
public:
    using Grid = Node*;

    static const int REGIONS = 9;
    static const int REGIONS_PER_SIDE = 3;
    static const int ROWS = 9;
    static const int COLS = 9;
    static const int REGION_COLS = COLS/REGIONS_PER_SIDE;
    static const int REGION_ROWS = ROWS/REGIONS_PER_SIDE;

    Model(); //Generates an empty board
    Model(Grid grid);

    ~Model();
    Model(const Model& to_copy);
    Model& operator=(const Model& to_copy);

    void undetermine(int region, int row, int col);
    void undetermine(int row, int col);
    void undetermine(int index);

    void set(int region, int row, int col, unsigned int value);
    void set(int row, int col, unsigned int value);
    void set(int index, unsigned int value);

    unsigned int value(int region, int row, int col);
    unsigned int value(int row, int col);
    unsigned int value(int index);

    bool determined();
private:
    int getIndex(int region, int row, int col);
    int getIndex(int row, int col);

    Grid _grid;
};

#endif//__NP_SUDOKU_MODEL
