#ifndef SIIRTO_H
#define SIIRTO_H

#include "ruutu.h"

class Siirto
{
public:
    Siirto(Ruutu alku, Ruutu loppu);
    Siirto(bool lyhytL, bool pitkaL);

    Ruutu getAlkuruutu();
    Ruutu getLoppuruutu();
    bool LyhytLinna();
    bool PitkaLinna();

private:
    Ruutu alkuRuutu;
    Ruutu loppuRuutu;
    int miksiKorotetaan = 0;
    bool lyhytLinna = false;
    bool pitkalinna = false;
};

#endif