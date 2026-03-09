#pragma once
#include "asema.h"
#include <windows.h>  // SetConsoleTextAttribute varten
#include "siirto.h"

class Kayttoliittyma {
public:
    Kayttoliittyma(Asema* asema);
    Asema* asema;
    void piirraLauta();
	Siirto annaVastustajanSiirto();
	int kysyKorotusNappula();
	// Palauttaa 0 = valkea, 1 = musta pelaajan valitseman varin mukaan
	int valitsePelaajanVari();
};
