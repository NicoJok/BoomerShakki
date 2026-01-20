#include "Kayttoliittyma.h"
#include "asema.h"
#include <iostream>
#include <windows.h>
#include <io.h>
#include <fcntl.h>


Kayttoliittyma::Kayttoliittyma(Asema* asema) : _asema(asema) {}

void Kayttoliittyma::piirraLauta() {
    _setmode(_fileno(stdout), _O_U16TEXT);

    HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);

    CONSOLE_SCREEN_BUFFER_INFO consoleInfo;
    GetConsoleScreenBufferInfo(hConsole, &consoleInfo);
    WORD alkuperainenVari = consoleInfo.wAttributes;

    WORD vaaleaBg = BACKGROUND_INTENSITY | BACKGROUND_RED | BACKGROUND_GREEN | BACKGROUND_BLUE; 
    WORD tummaBg = BACKGROUND_RED | BACKGROUND_GREEN;

    for (int rivi = 0; rivi < 8; ++rivi) {
        SetConsoleTextAttribute(hConsole, alkuperainenVari);
        std::wcout << 8 - rivi << L" ";

        for (int sarake = 0; sarake < 8; ++sarake) {
            WORD bg = ((rivi + sarake) % 2 == 0) ? vaaleaBg : tummaBg;
            Nappula* nappula = _asema->getNappula(rivi, sarake);

            if (nappula != nullptr) {
                WORD fg = (nappula->getVari() == 0) ? 0 : 0;

                SetConsoleTextAttribute(hConsole, fg | bg);
                std::wcout << nappula->getUnicode() << L'  ';
            }
            else {
                SetConsoleTextAttribute(hConsole, bg);
                std::wcout << L"  ";
            }
        }

        SetConsoleTextAttribute(hConsole, alkuperainenVari);
        std::wcout << L'\n';
    }

    SetConsoleTextAttribute(hConsole, alkuperainenVari);
    std::wcout << L"  ";
    for (int f = 0; f < 8; ++f) std::wcout << static_cast<wchar_t>(L'a' + f) << L' ';
    std::wcout << std::endl;

    SetConsoleTextAttribute(hConsole, alkuperainenVari);
}


