#include <Windows.h>
#include <iostream>
#include <string>
#include <fcntl.h>
#include <io.h>
#include "kayttoliittyma.h"

using namespace std;

//Testaus git ongelma
Kayttoliittyma* Kayttoliittyma::instance = 0;

Kayttoliittyma* Kayttoliittyma::getInstance()
{
    if (instance == 0)
        instance = new Kayttoliittyma();
    return instance;
}

void Kayttoliittyma::piirraLauta() {
    if (!_asema) return;

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
                std::wcout << nappula->getUnicode() << L" ";
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


/*
    Aliohjelma tarkistaa ett� k�ytt�j�n antama sy�te siirroksi on
    muodollisesti korretti (ei tarkista aseman laillisuutta)
    Ottaa irti my�s nappulan kirjaimen (K/D/L/R/T), tarkistaa ett� kirjain korretti
*/
Siirto Kayttoliittyma::annaVastustajanSiirto()
{
    wstring syote;
    wcout << L"Anna siirto: ";
    wcin >> syote;

    // Tarkista linnoitus
    if (syote == L"O-O") {
        // Lyhyt linna
        return Siirto(true, false);
    }
    else if (syote == L"O-O-O") {
        // Pitkä linna
        return Siirto(false, true);
    }

    // Normaali siirto: muoto "Rg1-f3" tai "g1-f3" (sotilas)
    size_t viivaPos = syote.find(L'-');
    if (viivaPos == wstring::npos || viivaPos == 0) {
        // Virheellinen muoto
        wcout << L"Virheellinen siirto! Käytä muotoa: NappulaAlkuruutu-Loppuruutu (esim. Rg1-f3)" << endl;
        return Siirto();
    }

    wstring alkuOsa = syote.substr(0, viivaPos);
    wstring loppuOsa = syote.substr(viivaPos + 1);

    // Tarkista että loppuruutu on oikean pituinen (2 merkkiä: sarake + rivi)
    if (loppuOsa.length() != 2) {
        wcout << L"Virheellinen loppuruutu!" << endl;
        return Siirto();
    }

    // Muunna loppuruutu
    int loppuSarake = loppuOsa[0] - L'a';
    int loppuRivi = 8 - (loppuOsa[1] - L'0');
    
    if (loppuSarake < 0 || loppuSarake >= 8 || loppuRivi < 0 || loppuRivi >= 8) {
        wcout << L"Virheellinen loppuruutu!" << endl;
        return Siirto();
    }

    Ruutu loppuRuutu(loppuSarake, loppuRivi);

    // Tarkista alkuruutu
    Ruutu alkuRuutu;
    
    if (alkuOsa.length() == 2) {
        // Sotilaan siirto (ei nappulakirjainta)
        int alkuSarake = alkuOsa[0] - L'a';
        int alkuRivi = 8 - (alkuOsa[1] - L'0');
        
        if (alkuSarake < 0 || alkuSarake >= 8 || alkuRivi < 0 || alkuRivi >= 8) {
            wcout << L"Virheellinen alkuruutu!" << endl;
            return Siirto();
        }
        
        alkuRuutu = Ruutu(alkuSarake, alkuRivi);
    }
    else if (alkuOsa.length() == 3) {
        // Nappulan siirto (nappulakirjain + ruutu)
        wchar_t nappulaKirjain = alkuOsa[0];
        
        // Tarkista että nappulakirjain on sallittu
        if (nappulaKirjain != L'T' && nappulaKirjain != L'R' && nappulaKirjain != L'L' && 
            nappulaKirjain != L'D' && nappulaKirjain != L'K') {
            wcout << L"Virheellinen nappulakirjain! Käytä: T (torni), R (ratsu), L (lähetti), D (daami), K (kuningas)" << endl;
            return Siirto();
        }
        
        int alkuSarake = alkuOsa[1] - L'a';
        int alkuRivi = 8 - (alkuOsa[2] - L'0');
        
        if (alkuSarake < 0 || alkuSarake >= 8 || alkuRivi < 0 || alkuRivi >= 8) {
            wcout << L"Virheellinen alkuruutu!" << endl;
            return Siirto();
        }
        
        alkuRuutu = Ruutu(alkuSarake, alkuRivi);
    }
    else {
        wcout << L"Virheellinen siirto! Käytä muotoa: NappulaAlkuruutu-Loppuruutu (esim. Rg1-f3)" << endl;
        return Siirto();
    }

    return Siirto(alkuRuutu, loppuRuutu);
}


int Kayttoliittyma::kysyVastustajanVari()
{
    return 0;
}
