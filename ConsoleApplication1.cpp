#include <iostream>
#include <algorithm>
#include "checkers.h"
using namespace std;

int main()
{
    checkers a;
    a.print();
    char letterpos; int numpos; char letterpos1; int numpos1;
    while (true)
    {
            cin >> letterpos >> numpos;
            cin >> letterpos1 >> numpos1;
            a.play(letterpos, numpos, letterpos1, numpos1);
            a.print();
    }
}