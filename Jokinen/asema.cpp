#include "asema.h"

Asema::Asema()
{
    vk = new Nappula(L"\u2654", 0, VK);
    vd = new Nappula(L"\u2655", 0, VD);
    vt = new Nappula(L"\u2656", 0, VT);
    vl = new Nappula(L"\u2657", 0, VL);
    vr = new Nappula(L"\u2658", 0, VR);
    vs = new Nappula(L"\u2659", 0, VS);

    mk = new Nappula(L"\u265A", 1, MK);
    md = new Nappula(L"\u265B", 1, MD);
    mt = new Nappula(L"\u265C", 1, MT);
    ml = new Nappula(L"\u265D", 1, ML);
    mr = new Nappula(L"\u265E", 1, MR);
    ms = new Nappula(L"\u265F", 1, MS);

    for (int rivi = 0; rivi < 8; rivi++)
    {
        for (int pRivi = 0; pRivi < 8; pRivi++)
        {
            lauta[rivi][pRivi] = nullptr;
        }
    }

    lauta[0][0] = mt;
    lauta[0][1] = mr;
    lauta[0][2] = ml;
    lauta[0][3] = md;
    lauta[0][4] = mk;
    lauta[0][5] = ml;
    lauta[0][6] = mr;
    lauta[0][7] = mt;
    for (int i = 0; i < 8; i++)
        lauta[1][i] = ms;


    lauta[7][0] = vt;
    lauta[7][1] = vr;
    lauta[7][2] = vl;
    lauta[7][3] = vd;
    lauta[7][4] = vk;
    lauta[7][5] = vl;
    lauta[7][6] = vr;
    lauta[7][7] = vt;
    for (int i = 0; i < 8; i++)
        lauta[6][i] = vs;

    siirtovuoro = 0;
    VKliikkunut = false;
    MKliikkunut = false;
    VDTliikkunut = false;
    MDTliikkunut = false;
    VKTliikkunut = false;
    MKTliikkunut = false;
}

void Asema::paivitaAsema(Siirto *siirto)
{
    int mistaRivi = siirto->getAlkuruutu().getRivi();
    int mistaSarake = siirto->getAlkuruutu().getpRivi();
    int mihinRivi = siirto->getLoppuruutu().getRivi();
    int mihinSarake = siirto->getLoppuruutu().getpRivi();

    Nappula *n = lauta[mistaRivi][mistaSarake];
    if (n == nullptr)
        return;

    int tyyppi = n->getNimi();

    if (tyyppi == VK)
        VKliikkunut = true;
    else if (tyyppi == MK)
        MKliikkunut = true;
    else if (tyyppi == VT)
    {
        if (mistaSarake == 0)
            VDTliikkunut = true;
        if (mistaSarake == 7)
            VKTliikkunut = true;
    }
    else if (tyyppi == MT)
    {
        if (mistaSarake == 0)
            MDTliikkunut = true;
        if (mistaSarake == 7)
            MKTliikkunut = true;
    }
    lauta[mihinRivi][mihinSarake] = n;
    lauta[mistaRivi][mistaSarake] = nullptr;
    siirtovuoro = (siirtovuoro == 0) ? 1 : 0;
}