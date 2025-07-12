#include "PhotoCode.h"
#include <iostream>



immas::immas(unsigned char* mas, unsigned int h, unsigned int w) {
    this->mas = mas;
    this->h = h;
    this->w = w;
    max_capacity = 3 * h * w / 4;
}

unsigned char& immas::operator()(int row, int col, int color)
{
    if (row > 0) {
        return mas[color * w * h + (row)*w + col];
    }
    else {
        return mas[color * w * h + col];
    }
}

void immas::set(int row, int col, int color, char inf) {
    char code = inf & (char)3;
    char color_ref;
    //*
    if (row > 0) {
        color_ref = mas[color * w * h + (row)*w + col];
    }
    else {
        color_ref = mas[color * w * h + col];
    }//*/
    char color_add = color_ref & 252;
    char color_new = code | color_add;
    (*this)(row, col, color) = color_new;
}

char immas::get(int row, int col, int color) {
    char col_encoded = (*this)(row, col, color);
    return (col_encoded & (char)3);
}

std::pair<bool, bool> immas::get_bool(int row, int col, int color) {
    char col_encoded = (*this)(row, col, color);
    return std::make_pair((col_encoded & (char)1), (col_encoded & (char)2));
}
//теперь нужно разбить изображение на ячейки по байту, разбиение должно быть оптимальным сопереносом строки
void immas::set_char(int row, int col, int color, char inf) {
    if (row == h and w - col < 4) {
        //no enougth place
    }
    else {
        for (int i = 0; i < 4; ++i) {
            if (col < w) {
                set(row, col, color, inf);
                col++;
            }
            else {
                ++row;
                col = 0;
                set(row, col, color, inf);
                ++col;
            }
            inf >>= 2;
        }
    }
}

char immas::get_char(int row, int col, int color) {
    if (row == h and w - col < 4) {
        //no enougth place
        std::cout << "error" << std::endl;
        return 0;
    }
    else {
        char code = get(row, col, color);
        ++col;
        for (int i = 1; i < 4; ++i) {
            if (col < w) {
                char db = get(row, col, color);
                code |= (db << (i * 2));
                col++;
            }
            else {
                ++row;
                col = 0;
                char db = get(row, col, color);
                code |= (db << (i * 2));
                col++;
            }
        }
        return code;
    }
}

//можно сделать оболочку, которая даёт адресацию по картинке как по одинарному масссиву.
bool immas::set_string(std::string code) {//первые 11 пикселей это сид и длина строки.
    if (code.length() + 11 >= max_capacity) {
        return false;
    }
    else {
        int col = 0, row = 5;
        long long len = code.length();
        std::cout << "length:        " << len;
        set(row, col, 0, len & 3);
        len >>= 2;
        //++col;
        std::cout << (len & 3) << std::endl;
        for (int i = 1; i < 16; ++i) {
            if (i % 3 == 0) {
                col++;
            }
            //set_char(row, col, i%3, len & 3);
            set(row, col, i % 3, len & 3);
            //cout << (len & 3) <<endl;
            len >>= 2;
        }
        //set_char(row, col, 1, ceed & 3);
        set(row, col, 1, ceed & 3);
        ceed >>= 2;
        for (int i = 2; i < 16; ++i) {
            if (i % 3 == 0) {
                col++;
            }//set_char(row, col, i % 3, ceed & 3);
            set(row, col, i % 3, ceed & 3);
            ceed >>= 2;
        }
        //cout << "col encode" << col << endl << endl;
        col++;////
        for (int i = 0; i < code.length(); ++i) {
            if ((i % 3) == 0) {
                col += 4;
                if (col >= w) {
                    col %= w;//
                    ++row;
                }
            }
            //cout << "setting    " << (char)code[i]<<"   "<<col << endl;
            set_char(row, col, i % 3, code[i]);
        }
        return true;
    }
}

std::string immas::get_string() {
    std::string code;
    int col = 0, row = 5;
    int len = 0;
    len = get(row, col, 0);
    //++col;
    //cout << "len:  " << len << endl;
    for (int i = 1; i < 16; ++i) {
        if (i % 3 == 0) {
            col++;
        }
        //long long int tmp = get_char(row, col, i%3);
        long long int tmp = get(row, col, i % 3);
        //long long int t;
        len += (tmp << (2 * i));
        //cout << "len:  " << len <<"tmp    "<<tmp << endl;
    }
    //cout << "length:        " << len;
    int ceed = 0;
    //len = get_char(row, col, 0);
    ceed = get(row, col, 1);
    //++col;
    //cout << "ceed:  " << ceed << endl;
    for (int i = 2; i < 16; ++i) {
        if (i % 3 == 0) {
            col++;
        }
        //long long int tmp = get_char(row, col, i%3);
        long long int tmp = get(row, col, i % 3);
        //long long int t;
        ceed += (tmp << (2 * (i - 1)));
        //cout << "ceed:  " << ceed << "tmp    " << tmp << endl;
    }
    //cout << "ceed:        " << ceed<<endl;
    col++;////
    for (int i = 0; i < len; ++i) {
        if (i % 3 == 0) {
            col += 4;
            if (col >= w) {
                col %= w;
                ++row;
            }
        }
        char tms = get_char(row, col, i % 3);
        //cout << "tmpstring    " << tms <<"col   "<<col<< endl;
        code += tms;
        //set_char(row, col, i / 3, code[i]);
    }//*/
    return code;
}

//нужно хранить в картинке длину строки



bool immas::set_string_encript(std::string code) {//первые 11 пикселей это сид и длина строки.
    /////////////////записывать байты в изображение по генератору случайных чисел
    if (code.length() + 11 >= max_capacity) {
        return false;
    }
    else {
        int col = 0, row = 5;
        long long len = code.length();
        //cout << "length:        " << len;
        //set_char(row, col, 0, len & 3);
        set(row, col, 0, len & 3);
        len >>= 2;
        //++col;
        std::cout << (len & 3) << std::endl;
        for (int i = 1; i < 16; ++i) {
            if (i % 3 == 0) {
                col++;
            }
            //set_char(row, col, i%3, len & 3);
            set(row, col, i % 3, len & 3);
            //cout << (len & 3) << endl;
            len >>= 2;
        }

        //set_char(row, col, 1, ceed & 3);
        set(row, col, 1, ceed & 3);
        ceed >>= 2;
        for (int i = 2; i < 16; ++i) {
            if (i % 3 == 0) {
                col++;
            }
            //set_char(row, col, i % 3, ceed & 3);
            set(row, col, i % 3, ceed & 3);
            ceed >>= 2;
        }

        srand(ceed);
        col = 16 + (4 * rand()) % (max_capacity - 15);////////////////12
        row = col / w;
        col %= w;

        int* fill = new int[max_capacity];//вносить в массив результат rand()
        for (int i = 0; i < max_capacity; ++i) {
            fill[i] = 0;
        }
        //нужно обработать случай, когда в ячейке уже записано значение.
        //col++;///////////////////////////
        for (int i = 0; i < code.length(); ++i) {
            //for (int j = 0; j < 3; ++j) {
            //    set_char(row,col,j,)
            //}

            //col = rand();

            /*
            if ((i % 3) == 0) {
                col += 4;
                if (col >= w) {
                    col %= w;/////////////////////
                    ++row;
                }
            }*/
            std::cout << "setting    " << (char)code[i] << "col:   " << col << "row:  " << row << std::endl;/////////////////////////////////////
            while (fill[((i % 3) * h * w + w * (row == 0 ? 0 : (row - 1)) + col) / 4] == 1) {///////////////////////
                //cout << "fill not div       " << ((i % 3) * h * w + w * (row == 0 ? 0 : (row - 1)) + col)<<endl;
                col = 16 + 4 * rand() % (max_capacity - 15);////////////////12
                row = col / w;
                col %= w;
            }
            set_char(row, col, i % 3, code[i]);
            fill[((i % 3) * h * w + w * (row == 0 ? 0 : (row - 1)) + col) / 4] = 1;//
        }

        return true;
    }
}


std::string immas::get_string_encript() {
    std::string code;
    int col = 0, row = 5;

    int len = 0;
    //len = get_char(row, col, 0);
    len = get(row, col, 0);
    //++col;
    //cout << "len:  " << len << endl;
    for (int i = 1; i < 16; ++i) {
        if (i % 3 == 0) {
            col++;
        }
        //long long int tmp = get_char(row, col, i%3);
        long long int tmp = get(row, col, i % 3);
        //long long int t;
        len += (tmp << (2 * i));
        //cout << "len:  " << len << "tmp    " << tmp << endl;
    }
    // cout << "length:        " << len;


    int ceed = 0;
    //len = get_char(row, col, 0);
    ceed = get(row, col, 1);
    //++col;
    //cout << "ceed:  " << ceed << endl;
    for (int i = 2; i < 16; ++i) {
        if (i % 3 == 0) {
            col++;
        }
        //long long int tmp = get_char(row, col, i%3);
        long long int tmp = get(row, col, i % 3);
        //long long int t;
        ceed += (tmp << (2 * (i - 1)));
        //cout << "ceed:  " << ceed << "tmp    " << tmp << endl;
    }
    // cout << "ceed:        " << ceed;

     //return "0";
     //*
    std::cout << std::endl;

    srand(ceed);
    col = 16 + (4 * rand()) % (max_capacity - 15);////////////////12
    row = col / w;
    col %= w;

    int* fill = new int[max_capacity];//вносить в массив результат rand()
    for (int i = 0; i < max_capacity; ++i) {
        fill[i] = 0;
    }


    //col++;///////////////////
    for (int i = 0; i < len; ++i) {
        //for (int j = 0; j < 3; ++j) {
        //    set_char(row,col,j,)
        //}

        /*
        if (i % 3 == 0) {
            col += 4;
            if (col >= w) {
                col %= w;
                ++row;
            }
        }*/


        //char tms = get_char(row, col, i % 3);
        //cout << "tmpstring    " << tms << "col   " << col << endl;
        //code += tms;


        std::cout << "settinge    " << (char)code[i] << "col:   " << col << "row:  " << row << std::endl;
        while (fill[((i % 3) * h * w + w * ((row == 0) ? 0 : (row - 1)) + col) / 4] == 1) {///////////////////////
            col = 16 + (4 * rand()) % (max_capacity - 15);////////////////12
            row = col / w;
            col %= w;
        }
        char tms = get_char(row, col, i % 3);
        //cout << "tmpstringe    " << tms << "col   " << col << endl;
        code += tms;
        //set_char(row, col, i % 3, code[i]);
        fill[((i % 3) * h * w + w * (row == 0 ? 0 : (row - 1)) + col) / 4] = 1;


        //set_char(row, col, i / 3, code[i]);

    }//*/
    return code;
}






/*
unsigned char& immas::operator()(int row, int col) const
{
    if (row > 0) {
        return mas[(row - 1) * h + row + col];
    }
    else {
        return mas[row + col];
    }
}*/




