#ifndef ASEMA_H
#define ASEMA_H

#include "nappula.h"
#include "siirto.h"
#include <list>

class Asema
{
private:

    int siirtovuoro;
    bool VKliikkunut = false;
    bool MKliikkunut = false;
    bool VDTliikkunut = false;
    bool MDTliikkunut = false;
    bool VKTliikkunut = false;
    bool MKTliikkunut = false;


public:
    Asema();
    Nappula *lauta[8][8];
    void annaLaillisetSiirrot(std::list<Siirto> &lista);
    void paivitaAsema(Siirto *siirto);
    int getSiirtovuoro() {return siirtovuoro;}
    void setSiirtovuoro(int vari) {siirtovuoro = vari;}

    bool onkoRuutuUhattu(Ruutu r, int hyokkaavaVari);
    void peruutaSiirto(Siirto *siirto, Nappula *syotyNappula, bool vkL, bool mkL, bool vdtL, bool mdtL, bool vktL, bool mktL);

    bool getVKLiikkunut() { return VKliikkunut; }
    bool getMKLiikkunut() { return MKliikkunut; }
    bool getVDTLiikkunut() { return VDTliikkunut; }
    bool getMDTLiikkunut() { return MDTliikkunut; }
    bool getVKTLiikkunut() { return VKTliikkunut; }
    bool getMKTLiikkunut() { return MKTliikkunut; }
};

#endif