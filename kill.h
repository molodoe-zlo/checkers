#include <iostream>
#include <algorithm>
#include "checkers.h"
using namespace std;

// рубка белой пешки
int killwh(int letter, int num, int letter1, int num1)
{
    int letter1_next = letter1;
    if (letter1 > letter) letter1_next = letter1 + 1;
    else letter1_next = letter - 2;
    if ((getsymbol(num1, letter1) == 'w') && (getsymbol(num, letter) == 'b'))
    {
        int num1_next = num1 + 1;
        if ((getsymbol(num1_next, letter1_next) != 'w') && (getsymbol(num1_next, letter1_next) != 'b'))
        {
            killwhite = killwhite + 1;
            nowpos(letter1, num1);
            num1 = num1 + 1;
            if (letter1 > letter) letter1 = letter1 + 1;
            else letter1 = letter - 2;
            nextpos(letter, num, letter1, num1);
            nowpos(letter, num);
            return (killwhite);
        }
        else cout << "listen go okay freak" << endl;
    }
}

// рубка черной пешки
int killb(int letter, int num, int letter1, int num1)
{
    int letter1_next = letter1;
    if (letter1 > letter) letter1_next = letter1 + 1;
    else letter1_next = letter - 2;
    if ((getsymbol(num1, letter1) == 'b') && (getsymbol(num, letter) == 'w'))
    {
        int num1_next = num1 - 1;
        if ((getsymbol(num1_next, letter1_next) != 'w') && (getsymbol(num1_next, letter1_next) != 'b'))
        {
            killblack = killblack + 1;
            nowpos(letter1, num1);
            num1 = num1 - 1;
            if (letter1 > letter) letter1 = letter1 + 1;
            else letter1 = letter - 2;
            nextpos(letter, num, letter1, num1);
            nowpos(letter, num);
            return (killblack);
        }
        else cout << "listen go okay freak" << endl;
    }
}