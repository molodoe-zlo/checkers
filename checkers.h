#include <iostream>
#include <algorithm>

class checkers
{
private: char** board;
       int n = 8;
       int killblack = 0;
       int killwhite = 0;
       int move = 1;
public:
    checkers()
    {
        // делаем досочку
        board = new char* [n];
        for (int i = 0; i < n; i++)
        {
            board[i] = new char[n];
        }
        for (int i = 0; i < n; i++)
        {
            for (int j = 0; j < n; j++)
            {
                board[i][j] = { '#' };
            }
        };
        // красим досочку, # - черный, _ - белые
        for (int i = 0; i < n; i++)
        {
            for (int j = 0; j < n; j++)
            {
                if (((i % 2 == 0) & (j % 2 == 0)) | ((i % 2 != 0) & (j % 2 != 0))) board[i][j] = { '_' };
            }
        };
        // ставим шашечки, b - черные, w - белые
        for (int i = 0; i < 3; i++)
        {
            for (int j = 0; j < n; j++)
            {
                if (board[i][j] == '#') board[i][j] = { 'b' };
            }
        };
        for (int i = 5; i < n; i++)
        {
            for (int j = 0; j < n; j++)
            {
                if (board[i][j] == '#') board[i][j] = { 'w' };
            }
        };
    };

    //оператор копирования
    checkers(const checkers& ch)
    {
        board = new char* [ch.n];
        for (int i = 0; i < ch.n; i++)
        {
            board[i] = new char[ch.n];
        };
        for (int i = 0; i < ch.n; i++)
        {
            for (int j = 0; j < ch.n; j++)
                board[i][j] = ch.board[i][j];
        }
    };

    // определяем какая шашка сейчас должна ходить
    void play(char& letter, int& num, char& letter1, int& num1)
    {
        if (move % 2 == 0) playBlack(letter, num, letter1, num1);
        else playWhite(letter, num, letter1, num1);
    }

    // берем символ из массива
    char& getsymbol(int& x, int& y)
    {
        return board[x][y];
    };

    // ставим шашку в новую клетку
    char nextpos(int letter, int num, int letter1, int num1)
    {
        board[num1][letter1] = getsymbol(num, letter);
        if ((num1 == 0) | (num1 == 7)) 
            board[num1][letter1] = toupper(getsymbol(num1, letter1));
        return board[num1][letter1];
    }

    // убираем шашку с клетки, из которой ходим
    char nowpos(int letter, int num)
    {
        board[num][letter] = { '#' };
        return board[num][letter];
    };

    void checkill(int letter, int num, int letter1, int num1)
    {
        int letter1_next = letter1;
        if (letter1 > letter) letter1_next = letter1 + 1;
        else letter1_next = letter - 2;
        // ход белой
        if (getsymbol(num, letter) == 'b')
        {
            int num1_next = num1 + 1;
            if ((num1_next >= 0) && (letter1_next >= 0) && (letter1_next <= 8))
            {
                if ((getsymbol(num1_next, letter1_next) != 'w') && (getsymbol(num1_next, letter1_next) != 'b'))
                {
                    killwh(letter, num, letter1, num1);
                    num1_next = num1_next + 1;
                    int letter1_next_1 = letter1_next - 1;
                    letter1_next = letter1_next + 1;
                    if ((getsymbol(num1_next, letter1_next) == 'w') | (getsymbol(num1_next, letter1_next_1) == 'w'))
                    {
                        num1 = num1 + 1;
                        if (letter1 > letter) letter1 = letter1 + 1;
                           else letter1 = letter - 2;
                        letter = letter1;
                        num = num1;
                        num1 = num1 + 1;
                        if (getsymbol(num1_next, letter1_next) == 'w') letter1 = letter1_next;
                        else letter1 = letter1_next_1;
                        move = move - 1;
                        checkill(letter, num, letter1, num1);
                    }
                }
            }
        }
        // ход черной
        if (getsymbol(num, letter) == 'w')
        {
            int num1_next = num1 - 1;
            if ((num1_next <= 8) && (letter1_next >= 0) && (letter1_next <= 8))
            {
                if ((getsymbol(num1_next, letter1_next) != 'w') && (getsymbol(num1_next, letter1_next) != 'b'))
                {
                    killb(letter, num, letter1, num1);
                    num1_next = num1_next - 1;
                    int letter1_next_1 = letter1_next - 1;
                    letter1_next = letter1_next + 1;
                    if ((getsymbol(num1_next, letter1_next) == 'b') | (getsymbol(num1_next, letter1_next_1) == 'b'))
                    {
                        num1 = num1 - 1;
                        if (letter1 > letter) letter1 = letter1 + 1;
                        else letter1 = letter - 2;
                        letter = letter1;
                        num = num1;
                        num1 = num1 - 1;
                        if (getsymbol(num1_next, letter1_next) == 'b') letter1 = letter1_next;
                        else letter1 = letter1_next_1;
                        move = move - 1;
                        checkill(letter, num, letter1, num1);
                    }
                }
            }
        }
    }

    // рубка белой пешки
    int killwh(int letter, int num, int letter1, int num1)
    {
        move = move + 1;
        killwhite = killwhite + 1;
        nowpos(letter1, num1);
        num1 = num1 + 1;
        if (letter1 > letter) letter1 = letter1 + 1;
        else letter1 = letter - 2;
        nextpos(letter, num, letter1, num1);
        nowpos(letter, num);
        return (killwhite);
    }

    // рубка черной пешки
    int killb(int letter, int num, int letter1, int num1)
    {
        move = move + 1;
        killwhite = killwhite + 1;
        nowpos(letter1, num1);
        num1 = num1 - 1;
        if (letter1 > letter) letter1 = letter1 + 1;
        else letter1 = letter - 2;
        nextpos(letter, num, letter1, num1);
        nowpos(letter, num);
        return (killwhite);
    }

    // ход белой шашки
    int playWhite(char& letter, int& num, char& letter1, int& num1)
    {
        if ((killblack < 12) && (killwhite < 12))
        {
            int x = letter - 'a';
            num = num - 1;
            int z = letter1 - 'a';
            num1 = num1 - 1;
            if (getsymbol(num, x) == 'W')
            {
                playQueen(x, num, z, num1);
                return (1);
            }
            if ((getsymbol(num, x) != 'w') | (x - z > abs(1)))
            {
                std::cout << "listen go okay freak" << std::endl;
                return (0);
            }
            else if (getsymbol(num1, z) == 'b')
            {
                checkill(x, num, z, num1);
            }
            else if ((getsymbol(num, x)) == 'w')
            {
                if ((num - num1 > 1) | (num < num1))
                {
                    std::cout << "listen go okay freak" << std::endl;
                    return (0);
                }
                else
                {
                    move = move + 1;
                    nextpos(x, num, z, num1);
                    nowpos(x, num);
                }
            }
        }
        else std::cout << "game over";
    };

    // ход черной шашки
    int playBlack(char& letter, int& num, char& letter1, int& num1)
    {
        if ((killblack < 12) && (killwhite < 12))
        {
            int x = letter - 'a';
            num = num - 1;
            int z = letter1 - 'a';
            num1 = num1 - 1;
            if (getsymbol(num, x) == 'B')
            {
                playQueen(x, num, z, num1);
                return (1);
            }
            if ((getsymbol(num, x) != 'b') | (x - z > abs(1)))
            {
                std::cout << "listen go okay freak" << std::endl;
                return (0);
            }

            else if (getsymbol(num1, z) == 'w')
            {
                checkill(x, num, z, num1);
            }
            else if ((getsymbol(num, x)) == 'b')
            {
                if ((num1 - num > 1) | (num1 < num))
                {
                    std::cout << "listen go okay freak" << std::endl;
                    return (0);
                }
                else
                {
                    move = move + 1;
                    nextpos(x, num, z, num1);
                    nowpos(x, num);
                }
            }
        }
        else std :: cout << "game over";
    };

    // ход дамки 
    int playQueen(int& letter, int& num, int& letter1, int& num1)
    {
        if (abs(letter1 - letter) == abs(num1 - num))
        {
            if ((getsymbol(num, letter) == 'W') && (getsymbol(num1, letter1) == 'b'))
                killb(letter, num, letter1, num1);
            else if ((getsymbol(num, letter) == 'B') && (getsymbol(num1, letter1) == 'w'))
                killwh(letter, num, letter1, num1);
            else {

                nextpos(letter, num, letter1, num1);
                nowpos(letter, num);
            };
        }
        else {
            std::cout << "listen go okay freak" << std::endl;
            return (0);
        }
    }

    // выводим доску
    void print()
    {
        std :: cout << "  | a | b | c | d | e | f | g | h" << std :: endl;
        for (int i = 0; i < n; i++)
        {
            std :: cout << "--+---+---+---+---+---+---+---+---" << std :: endl;
            std :: cout << i + 1;
            for (int j = 0; j < n; j++)
            {
                std :: cout << " | " << (getsymbol(i, j));
            }
            std :: cout << std :: endl;
        };
    };

    //деструктор
    ~checkers()
    {
        for (int i = 0; i < n; i++)
            delete[] board[i];
        delete[] board;
    }
};