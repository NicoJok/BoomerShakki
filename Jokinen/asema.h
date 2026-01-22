#ifndef ASEMA_H
#define ASEMA_H

#include "nappula.h"
#include "siirto.h"

class Asema
{
private:
    Nappula *vk, *vd, *vt, *vl, *vr, *vs;
    Nappula *mk, *md, *mt, *ml, *mr, *ms;

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

    void paivitaAsema(Siirto *siirto);
    int getSiirtovuoro() {return siirtovuoro;}
    void getSiirtovuoro(int vari) {siirtovuoro = vari;}

    bool getVKLiikkunut() { return VKliikkunut; }
    bool getMKLiikkunut() { return MKliikkunut; }
    bool getVDTLiikkunut() { return VDTliikkunut; }
    bool getMDTLiikkunut() { return MDTliikkunut; }
    bool getVKTLiikkunut() { return VKTliikkunut; }
    bool getMKTLiikkunut() { return MKTliikkunut; }
};

#endif