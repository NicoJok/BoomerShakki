#pragma once
#include <chrono>
#include "asema.h"
#include "siirto.h"

struct MinMaxPaluu {
    double evaluointiArvo;
    Siirto parasSiirto;
};

class Minimax {
public:
    Siirto etsiParasSiirto(Asema asema, int maksimiAikaMs); 
    MinMaxPaluu maxi(Asema asema, int syvyys);
    MinMaxPaluu mini(Asema asema, int syvyys);

private:
    std::chrono::steady_clock::time_point aloitusAika;
    int sekunttiAika;
    bool aikaStop;
    long solmuLaskuri;

    void AjanTarkistus();
};