#pragma once
#include "CImg.h"
#include <utility>
#include <string>

class immas {
    unsigned char* mas;
    unsigned int h, w;
    int max_capacity;
    int ceed = 12345;

public:

    immas(unsigned char* mas, unsigned int h, unsigned int w);

    unsigned char& operator()(int row, int col, int color);

    void set(int row, int col, int color, char inf);

    char get(int row, int col, int color);
    std::pair<bool, bool> get_bool(int row, int col, int color);

    void set_char(int row, int col, int color, char inf);

    char get_char(int row, int col, int color);

    bool set_string(std::string code);

    std::string get_string();

    bool set_string_encript(std::string code);

    std::string get_string_encript();

};
