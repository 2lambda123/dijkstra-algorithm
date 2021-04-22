/* util.cpp */
#include "util.h"

#include <iostream>
#include <string>

using namespace std;

// command line
commands current(char c) {
    commands command = NONE;
    if (c == 'p') {
        command = WRITE;
    }
    if (c == 'f') {
        command = FIND;
    }
    if (c == 's') {
        command = STOP;
    }
    return command;
}

// command line input
int getInput(int* source, int* x, int* y, int* destination, int* flag) {
    string takeInput;
    string array[10] = {};
    string inpt; // input
    int i = 0;
    char val = ' ';
    // program is running
    while (1) {
        cin >> inpt;
        // while it is not space or new line
        while (inpt.compare(" ") == 0 || inpt.compare("\n") == 0) {
            cin >> inpt;
        }
        // found
        if (inpt.compare("find") == 0) {
            getline(cin, takeInput, '\n');
            string line = " ";
            takeInput += line;
            size_t position = 0;
            std::string::size_type stype;
            string token;
            while ((position = takeInput.find(line)) != std::string::npos) {
                token = takeInput.substr(0, position);
                array[i] = token;
                takeInput.erase(0, position + line.length());
                i++;
            }
            *destination = stoi(array[2], &stype);
            *source = stoi(array[1], &stype);
            if (array[3].compare("") == 0) {
                break;
            }
            *flag = stoi(array[3], &stype);
            val = 'f';
            break;
        }
        if (inpt.compare("path") == 0) {
            cin >> *x;
            cin >> *y;
            val  = 'p';
            break;
        }
        if (inpt.compare("stop") == 0) {
            val = 's';
            break;
        }
    }
    return val;
}
