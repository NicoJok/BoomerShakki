#ifndef KAYTTOLIITTYMA_H
#define KAYTTOLIITTYMA_H

#include "asema.h"
#include <windows.h>
#include <io.h>
#include <fcntl.h>
#include <iostream>

class Kayttoliittyma
{
public:
    Asema *asema;

    Kayttoliittyma(Asema *a) : asema(a)
    {
        _setmode(_fileno(stdout), _O_U16TEXT);
    }

    void piirraLauta()
    {
        HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);

        for (int row = 0; row < 8; row++)
        {
            SetConsoleTextAttribute(hConsole, 7);
            std::wcout << (8 - row) << L" ";

            for (int col = 0; col < 8; col++)
            {
                if ((row + col) % 2 == 0)
                {
                    SetConsoleTextAttribute(
                        hConsole, BACKGROUND_INTENSITY | BACKGROUND_RED |
                        BACKGROUND_GREEN | BACKGROUND_BLUE);
                }
                else
                {
                    SetConsoleTextAttribute(hConsole, BACKGROUND_BLUE);
                }

                if (asema->lauta[row][col] != nullptr)
                {
                    std::wcout << asema->lauta[row][col]->getUnicode() << L" ";
                }
                else
                {
                    std::wcout << L"  ";
                }
            }

            SetConsoleTextAttribute(hConsole, 7);
            std::wcout << std::endl;
        }
        std::wcout << L"  ";
        for (int col = 0; col < 8; col++)
        {
            std::wcout << (wchar_t)(L'A' + col) << L" ";
        }
        std::wcout << std::endl;
    }
};

#endif