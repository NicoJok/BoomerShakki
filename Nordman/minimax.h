#pragma once
#include "asema.h"
#include "siirto.h"

class MinMaxPaluu {
public:
    double evaluointiArvo;
    Siirto parasSiirto;
};

class Minimax {
public:
    static MinMaxPaluu maxi(Asema asema, int syvyys);
    static MinMaxPaluu mini(Asema asema, int syvyys);
};
