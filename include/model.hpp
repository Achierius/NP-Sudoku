#ifndef __NP_SUDOKU_MODEL
#define __NP_SUDOKU_MODEL

#include <optional>
#include <array>

class Model {
public:
    static const int REGIONS = 9;
    static const int REGIONS_PER_SIDE = 3;
    static const int ROWS = 9;
    static const int COLS = 9;
    static const int REGION_COLS = COLS/REGIONS_PER_SIDE;
    static const int REGION_ROWS = ROWS/REGIONS_PER_SIDE;


    using Node = std::optional<int>;
    using Grid = std::array<Node, ROWS*COLS>;

    Model(); //Generates an empty board
    Model(Grid grid);

    ~Model();
    Model(const Model& to_copy);
    Model& operator=(const Model& to_copy);

    void unset(int region, int row, int col);
    void unset(int row, int col);
    void unset(int index);

    void set(int region, int row, int col, int value);
    void set(int row, int col, int value);
    void set(int index, int value);

    Node value(int region, int row, int col) const;
    Node value(int row, int col) const;
    Node value(int index) const;

    bool determined() const;
private:
    int getIndex(int region, int row, int col) const;
    int getIndex(int row, int col) const;

    Grid _grid;
};

#endif//__NP_SUDOKU_MODEL
