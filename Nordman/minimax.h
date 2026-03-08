#pragma once
#include <chrono>
#include <vector>
#include "asema.h"
#include "siirto.h"

struct MinMaxPaluu {
    double evaluointiArvo;
    Siirto parasSiirto;
};

class Minimax {
public:
    Siirto etsiParasSiirto(Asema asema, int maksimiAikaMs); 
    MinMaxPaluu maxi(Asema asema, int syvyys, double alfa, double beta);
    MinMaxPaluu mini(Asema asema, int syvyys, double alfa, double beta);

private:
    std::chrono::steady_clock::time_point aloitusAika;
    int sekunttiAika;
    bool aikaStop;
    long solmuLaskuri;

    void AjanTarkistus();
    void MoveOrdering(std::vector<Siirto>& siirrot, Asema& asema);

    double QSMaxi(Asema asema, double alfa, double beta);
    double QSMini(Asema asema, double alfa, double beta);
};