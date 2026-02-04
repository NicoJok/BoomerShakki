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

    int fd = _fileno(stdout);
    if (_setmode(fd, _O_U16TEXT) == -1) {
		//Ongelma Unicode-tilaan asettamisessa
    }

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

    // Linnoitus: hyväksy "O-O" / "o-o" ja "O-O-O" / "o-o-o" (isot ja pienet kirjaimet)
    if (syote == L"O-O" || syote == L"o-o") {
        return Siirto(true, false);
    }
    if (syote == L"O-O-O" || syote == L"o-o-o") {
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

    // Loppuruutu: 2 merkkiä (e8) tai 4 merkkiä korotuksella (e8=D). Korotus: =D, =T, =L, =R
    wchar_t promKirjain = 0;  // 0 = ei korotusta, D/T/L/R = daami/torni/lähetti/ratsu
    if (loppuOsa.length() == 2) {
        // Ei korotusta
    }
    else if (loppuOsa.length() == 4 && loppuOsa[2] == L'=') {
        promKirjain = loppuOsa[3];
        if (promKirjain != L'D' && promKirjain != L'T' && promKirjain != L'L' && promKirjain != L'R') {
            wcout << L"Korotus: käytä =D (daami), =T (torni), =L (lähetti) tai =R (ratsu). K (kuningas) on kielletty." << endl;
            return Siirto();
        }
    }
    else {
        wcout << L"Virheellinen loppuruutu! Esim. e8 tai e8=D" << endl;
        return Siirto();
    }

    // Muunna loppuruutu (2 ensimmäistä merkkiä)
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

    // Varmista että alkuruudussa on nappula, merkintä vastaa nappulaa ja vuoro oikein
    if (!_asema) return Siirto(alkuRuutu, loppuRuutu);
    int ar = alkuRuutu.getRivi(), ac = alkuRuutu.getSarake();
    Nappula* n = _asema->getNappula(ar, ac);
    if (n == nullptr) {
        wcout << L"Virhe: Alkuruudussa ei ole nappulaa.\n";
        return Siirto();
    }
    if (n->getVari() != _asema->getSiirtovuoro()) {
        wcout << L"Virhe: Siirto ei ole sinun vuorollasi.\n";
        return Siirto();
    }
    int koodi = n->getKoodi();
    bool onkoSotilas = (koodi == VS || koodi == MS);
    if (onkoSotilas) {
        if (alkuOsa.length() != 2) {
            wcout << L"Sotilassiirrot: vain koordinaatit (esim. e2-e4).\n";
            return Siirto();
        }
    }
    else {
        if (alkuOsa.length() != 3) {
            wcout << L"Nappulasiirrot vaativat kirjaimen: T, R, L, D tai K (esim. Rg1-f3).\n";
            return Siirto();
        }
        wchar_t oikeaKirjain = L'K';
        if (koodi == VT || koodi == MT) oikeaKirjain = L'T';
        else if (koodi == VR || koodi == MR) oikeaKirjain = L'R';
        else if (koodi == VL || koodi == ML) oikeaKirjain = L'L';
        else if (koodi == VD || koodi == MD) oikeaKirjain = L'D';
        if (alkuOsa[0] != oikeaKirjain) {
            wcout << L"Väärä nappulakirjain; tässä ruudussa on " << oikeaKirjain << L".\n";
            return Siirto();
        }
    }

    // Ohestalyönti: sotilas liikkuu diagonaalisesti tyhjään ruutuun, joka on EP-kohde
    if (onkoSotilas && (ac != loppuSarake) && _asema->getNappula(loppuRivi, loppuSarake) == nullptr) {
        if (_asema->getEpTargetRivi() == loppuRivi && _asema->getEpTargetSarake() == loppuSarake) {
            Siirto ep(alkuRuutu, loppuRuutu);
            ep.setOhestalyonti(true);
            return ep;
        }
    }

    // Normaali siirto; aseta korotus jos sotilas saavuttaa viimeisen rivin
    Siirto s(alkuRuutu, loppuRuutu);
    if (onkoSotilas && ((koodi == VS && loppuRivi == 0) || (koodi == MS && loppuRivi == 7))) {
        Nappula* korotus = nullptr;
        if (promKirjain == L'D') korotus = (koodi == VS) ? Asema::vd : Asema::md;
        else if (promKirjain == L'T') korotus = (koodi == VS) ? Asema::vt : Asema::mt;
        else if (promKirjain == L'L') korotus = (koodi == VS) ? Asema::vl : Asema::ml;
        else if (promKirjain == L'R') korotus = (koodi == VS) ? Asema::vr : Asema::mr;
        else korotus = (koodi == VS) ? Asema::vd : Asema::md;  // oletus daami kun ei =X
        s._miksikorotetaan = korotus;
    }
    return s;
}


int Kayttoliittyma::kysyVastustajanVari()
{
    return 0;
}
