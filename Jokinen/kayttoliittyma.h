#ifndef KAYTTOLIITTYMA_H
#define KAYTTOLIITTYMA_H

#include "asema.h"
#include "siirto.h"
#include <windows.h>
#include <io.h>
#include <fcntl.h>
#include <iostream>
#include <string>

class Kayttoliittyma
{
public:
    Asema *asema;

    Kayttoliittyma(Asema *a) : asema(a)
    {
        _setmode(_fileno(stdout), _O_U16TEXT);
        _setmode(_fileno(stdin), _O_U16TEXT);
    }

    void piirraLauta()
    {
        HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
        for (int row = 0; row < 8; row++)
        {
            SetConsoleTextAttribute(hConsole, FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_BLUE);
            std::wcout << (8 - row) << L" ";
            for (int col = 0; col < 8; col++)
            {
                if ((row + col) % 2 == 0)
                    SetConsoleTextAttribute(hConsole, BACKGROUND_RED | BACKGROUND_GREEN | BACKGROUND_BLUE);
                else
                    SetConsoleTextAttribute(hConsole, BACKGROUND_BLUE);

                if (asema->lauta[row][col] != nullptr)
                    std::wcout << asema->lauta[row][col]->getUnicode() << L" ";
                else
                    std::wcout << L"  ";
            }
            SetConsoleTextAttribute(hConsole, FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_BLUE);
            std::wcout << std::endl;
        }
        std::wcout << L"  ";
        for (int col = 0; col < 8; col++)
            std::wcout << (wchar_t)(L'A' + col) << L" ";
        std::wcout << std::endl;
    }

    Siirto annaVastustajanSiirto()
    {
        std::wstring syote;
        std::wcout << L"Siirtosi: ";
        std::wcin >> syote;

        if (syote == L"O-O") 
            return Siirto(true, false);
        if (syote == L"O-O-O") 
            return Siirto(false, true);
        
        int mistapRivi = syote[0] - L'a';
        int mistaRivi = 8 - (syote[1] - L'0');
        int mihinpRivi = syote[2] - L'a';
        int mihinRivi = 8 - (syote[3] - L'0');

        Ruutu alku(mistaRivi, mistapRivi);
        Ruutu loppu(mihinRivi, mihinpRivi);
        return Siirto(alku, loppu);
    }
};

#endif