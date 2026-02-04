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
    system("cls");
    
    WORD lightBlueSquare = BACKGROUND_BLUE | BACKGROUND_GREEN; 
    WORD lightGraySquare = BACKGROUND_INTENSITY; 
    
    WORD whitePieceText = FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_BLUE | FOREGROUND_INTENSITY;
    WORD blackPieceText = 0;

    for (int row = 0; row < 8; row++)
    {
        SetConsoleTextAttribute(hConsole, FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_BLUE);
        std::wcout << (8 - row) << L" ";

        for (int col = 0; col < 8; col++)
        {
            WORD currentBg = ((row + col) % 2 == 0) ? lightGraySquare : lightBlueSquare;
            
            if (asema->lauta[row][col] != nullptr)
            {
                Nappula *n = asema->lauta[row][col];
                WORD currentFg = (n->getVari() == 0) ? whitePieceText : blackPieceText;

                SetConsoleTextAttribute(hConsole, currentBg | currentFg);
                std::wcout << n->getUnicode() << L" ";
            }
            else
            {
                SetConsoleTextAttribute(hConsole, currentBg);
                std::wcout << L"  ";
            }
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

    Korotus kysyKorotus() 
    {
        std::wstring s;
        std::wcout << L"Korotus (D, T, L, R): ";
        std::wcin >> s;
        wchar_t c = towupper(s[0]);

        if (c == L'D') return daami;
        if (c == L'T') return torni;
        if (c == L'L') return lahetti;
        if (c == L'R') return ratsu;
        return daami;
    }
};
#endif