#include "node.hpp"

Node::Node() {
    _determined = false;
}

Node::Node(unsigned int value) {
    _determined = true;
    _value = value;
}

Node::~Node() {
}

Node::Node(const Node& to_copy) {
    this._determined = to_copy._determined;
    if(_determined) {
        this._value = to_copy._value;
    }
}


Node& Node::operator=(const Node& to_copy) {
    this._determined = to_copy._determined;
    if(_determined) {
        this._value = to_copy._value;
    }
}

Node& Node::operator=(const int& to_set) {
    this.set(to_set);
}

void Node::empty() {
    this._determined = false;
}

void Node::set(unsigned int value) {
    this._determined = true;
    this._value = value;
}

unsigned int Node::value() { //TODO: Exceptions when called while !_determined
    if(_determined) {
        return _value;
    }
    return 0;
}

bool Node::determined() {
    return _determined;
}
