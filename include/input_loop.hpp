#ifndef __NP_SUDOKU_INPUT_LOOP
#define __NP_SUDOKU_INPUT_LOOP

#include <vector>
#include <tuple>
#include <string>
#include "model.hpp"

using InputCommand = void (*)(int);

std::vector<Model> boards;

int inputLoop();

void parseLine(std::string line);

InputCommand parseCommand(std::string commandString);

int parseInt(std::string intString);

int embedN4(int a, int b, int c, int d);
int embedN3(int a, int b, int c);
int embedN2(int a, int b);

std::tuple<int, int> revertN2(int e);
std::tuple<int, int, int> revertN3(int e);
std::tuple<int, int, int, int> revertN4(int e);

void commandExit(int unused);

void commandNewBoard(int boardID);

void commandClearBoard(int boardID);

void commandDisplayBoard(int boardID);

void commandDeleteBoard(int boardID);

void commandRandomizeBoard(int boardID);

void verifyBoard(int boardID);

#endif//__NP_SUDOKU_INPUT_LOOP
