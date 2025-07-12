#include <iostream>
#include "PhotoCode.h"

int main()
{
    int ceed;//сид для псевдослучайных чисел, которые определяют порядок считывания байтов. Можно взять первый байт (возможно инвертированный)
    srand(100);
    int a = rand();
    std::cout << a;
    unsigned char num = 255;
    for (int i = 0; i < 8; ++i) {
        if (i == 0) {
            std::cout << (num & (char)1);
        }
        else {
            std::cout << ((num >> i) & 1);
        }

    }std::cout << std::endl;
    char code = 0;
    code = num & (char)3;
    for (int i = 0; i < 8; ++i) {
        if (i == 0) {
            std::cout << (code & (char)1);
        }
        else {
            std::cout << ((code >> i) & 1);
        }

    }std::cout << std::endl;
    char codeadd = num & 252;
    for (int i = 0; i < 8; ++i) {
        if (i == 0) {
            std::cout << (codeadd & (char)1);
        }
        else {
            std::cout << ((codeadd >> i) & 1);
        }

    }std::cout << std::endl;

    //return 0;


    //CImg<unsigned char> image("cat_.png");
    cimg_library::CImg<unsigned char> image("cat_ref.png");
    unsigned char* mas = image.data();
    int w = image.width();//ширина картинки
    int h = image.height();//высота картинки
    std::cout << w << std::endl;
    immas matr(mas, h, w);
    /*
    for (int i = 0; i < 20; ++i) {
         matr(55, i, 1) = 250;
         //mas[i] = 250;
    }*/
    //matr.set(101, 100, 0, 2);
    //char out = matr.get(101, 100, 0);
    //cout << "out: ";
    /*
    for (int i = 0; i < 8; ++i) {
        if (i == 0) {
            cout << (out & (char)1);
        }
        else {
            cout << ((out >> i) & 1);
        }

    }cout << endl << endl;*/

    //cout << "cap: " << matr.max_capacity << endl;
    matr.set_string("setted string");
    ///char p = matr.get_char(0, 15, 0);
    //cout << "p           " << p << endl;
    std::string outs = matr.get_string();
    std::cout << "out string      " << outs << std::endl << std::endl;

    //p = matr.get_char(0, 15, 0);
    //cout <<"p           " << p<<endl;


    matr.set_string_encript("stringencript");
    outs = matr.get_string_encript();
    std::cout << "out string      " << outs << std::endl << std::endl;
    /*
    int c = 0;
    char out = matr.get(0, 0, 0);
    cout << "out: ";

    for (int i = 0; i < 8; ++i) {
        if (i == 0) {
            cout << (out & (char)1);
        }
        else {
            cout << ((out >> i) & 1);
        }

    }cout << endl << endl;
    for (int i = 1; i < 17; ++i) {
        if (i % 3 == 0) {
            ++c;
        }
        char out = matr.get(c, 1, i%3);
        cout << "out: ";
        for (int i = 0; i < 8; ++i) {
            if (i == 0) {
                cout << (out & (char)1);
            }
            else {
                cout << ((out >> i) & 1);
            }

        }cout << endl << endl;
    }*/



    /*
    matr.set_char(150, 150, 0, 'a');
    char ans = matr.get_char(150, 150, 0);
    cout << "ans: " << ans << endl;
    matr(100, 799, 2) = 255;
    matr.set_char(150, 799, 0, 'b');
    ans = matr.get_char(150, 799, 0);
    cout << "ans: " << ans << endl;*/
    image.save("cat.png");


    image.display();

}
