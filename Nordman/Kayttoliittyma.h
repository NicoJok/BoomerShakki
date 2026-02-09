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
};
