#include "kayttoliittyma.h"
#include <iostream>

Kayttoliittyma::Kayttoliittyma(Asema* a) : asema(a) {}

void Kayttoliittyma::piirraLauta() {
    // Käy läpi lauta ylhäältä alas (rivi 7 -> 0)
    for (int rivi = 7; rivi >= 0; rivi--) {
		std::wcout << rivi + 1 << L"|"; // Tulosta rivinumero
        for (int sarake = 0; sarake < 8; sarake++) {

            // TODO: Vaihda ruudun taustaväri
            // Jos (rivi + sarake) on parillinen -> vaalea ruutu
            // Jos (rivi + sarake) on pariton -> tumma ruutu
			if ((rivi + sarake) % 2 == 0) {
                SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 240); // Vaalea
            } else {
                SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 32); // Vihreä
            }

            // TODO: Tulosta nappula tai tyhjä välilyönti
            // Jos asema->lauta[rivi][sarake] != nullptr
            //     tulosta nappulan unicode
            // Muuten tulosta L" "
			if (asema->lauta[rivi][sarake] != nullptr) {
                std::wcout << asema->lauta[rivi][sarake]->getUnicode() << L" ";
            } else {
                std::wcout << L"  "; // Kaksi välilyöntiä, jotta ruudut pysyvät tasaisina
            }

        }
        std::wcout << std::endl;  // Rivinvaihto
    }
	std::wcout << L"  a b c d e f g h" << std::endl; // Tulosta sarakenumerot

    // Palauta normaali väri
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 7);
}

Siirto Kayttoliittyma::annaVastustajanSiirto() {
    std::wstring syote;
	std::wcout << L"Anna siirto: ";
	std::wcin >> syote;

    //Tarkista erikoistapaukset
	if (syote == L"O-O") {
        return Siirto(true, false); //Lyhyt linna
    } else if(syote == L"O-O-O") {
        return Siirto(false, true); //Pitkä linna
    }

    int alkurivi;
	int alkusarake;
	int loppurivi;
	int loppusarake;

    //Normaali siirto
	//Onko ensimmäinen merkki iso kirjain? Jos on, niin se on nappula, muuten sotilas
	wchar_t ekaMerkki = syote[0];

    //Nappula on upseeri
    if (ekaMerkki == L'R' ||
        ekaMerkki == L'D' ||
        ekaMerkki == L'K' ||
        ekaMerkki == L'L' ||
        ekaMerkki == L'T') {

		alkusarake = syote[1] - L'a'; // 'g' - 'a' = 6
		alkurivi = syote[2] - L'1';   // '1' - '1' = 0
		loppusarake = syote[4] - L'a'; // 'f' - 'a' = 5
		loppurivi = syote[5] - L'1';   // '3' - '1' = 2     
    }
    else {
        //Nappula on sotilas
		alkusarake = syote[0] - L'a'; // 'e' - 'a' = 4
		alkurivi = syote[1] - L'1';   // '2' - '1' = 1
		loppusarake = syote[3] - L'a'; // 'e' - 'a' = 4
		loppurivi = syote[4] - L'1';   // '4' - '1' = 3
    }
    
	return Siirto(Ruutu(alkurivi, alkusarake), Ruutu(loppurivi, loppusarake));
}