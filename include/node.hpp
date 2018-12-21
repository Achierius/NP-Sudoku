#ifndef __NP_SUDOKU_NODE
#define __NP_SUDOKU_NODE

class Node {
public:
    Node();
    Node(unsigned int value);

    ~Node();
    Node(const Node& to_copy);
    Node& operator=(const Node& to_copy);

    Node& operator=(const int& to_set);

    void empty();
    void set(unsigned int value);

    unsigned int value();
    bool determined();
private:
    unsigned int _value;
    bool _determined;
}

#endif//__NP_SUDOKU_NODE
