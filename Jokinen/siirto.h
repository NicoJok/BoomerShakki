#ifndef SIIRTO_H
#define SIIRTO_H
#pragma once
#include "ruutu.h"

enum Korotus {
    ei_koro, daami, torni, ratsu, lahetti
    };

class Siirto
{
public:
    Siirto(Ruutu alku, Ruutu loppu, Korotus koro = ei_koro);
    Siirto(bool lyhytL, bool pitkaL);

    Ruutu getAlkuruutu();
    Ruutu getLoppuruutu();
    bool LyhytLinna();
    bool PitkaLinna();
    Korotus getKorotus();

private:
    Ruutu alkuRuutu;
    Ruutu loppuRuutu;
    Korotus koro = ei_koro;
    bool lyhytLinna = false;
    bool pitkalinna = false;
};

#endif