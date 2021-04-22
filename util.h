/* util.hpp */
#ifndef util_h
#define util_h

#include <iostream>
#include <string>

// enum declaration types
enum commands {WRITE, FIND, STOP, NONE };
// character
commands current(char c);

// util.cpp
int getInput(int* source, int* x, int* y, int* destination, int* flag);

#endif /* util_h */
