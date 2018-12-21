#include "input_loop.hpp"

#include <iostream>
#include <cctype>

int inputLoop() {
    std::string line = "";
    cin >> line;

    std::string buf = "";

    InputCommand cmd = &commandNull;

    int index = 0;
    for( ; !isspace(line[index]); index++) {
        if(line[index] == '\n') {
            
        }
        else {
            buf.append(line[index]);
        }
    }

    cmd = parseCommand(buf);

    for( ; line[index] != '\n'; index++) {
        for( ; ) {
            if() {
            }
        }
    }


}
