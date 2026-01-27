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
    if (siirto->LyhytLinna()) {
        if (siirtovuoro == 0) {
            lauta[7][6] = lauta[7][4]; 
            lauta[7][5] = lauta[7][7];
            lauta[7][7] = nullptr;
            VKliikkunut = true;
            VKTliikkunut = true;

        } else {
            lauta[0][6] = lauta[0][4];
            lauta[0][5] = lauta[0][7];
            lauta[0][4] = nullptr;
            lauta[0][7] = nullptr;
            MKliikkunut = true;
            MKTliikkunut = true;
        }
            if (siirtovuoro == 0) {
                siirtovuoro = 1;
            } 
            else {
                siirtovuoro = 0;
            }
        return;
    }

    if (siirto->PitkaLinna()) {
        if (siirtovuoro == 0) {
            lauta[7][2] = lauta[7][4];
            lauta[7][3] = lauta[7][0];
            lauta[7][4] = nullptr;
            lauta[7][0] = nullptr;
            VKliikkunut = true;
            VDTliikkunut = true;

        } else { 
            lauta[0][2] = lauta[0][4];
            lauta[0][3] = lauta[0][0];
            lauta[0][4] = nullptr;
            lauta[0][0] = nullptr;
            MKliikkunut = true;
            MDTliikkunut = true;
        }
            if (siirtovuoro == 0) {
                siirtovuoro = 1;
            } 
            else {
                siirtovuoro = 0;
            }
            return;
    }

    int mistaRivi = siirto->getAlkuruutu().getRivi();
    int mistapRivi = siirto->getAlkuruutu().getpRivi();
    int mihinRivi = siirto->getLoppuruutu().getRivi();
    int mihinpRivi = siirto->getLoppuruutu().getpRivi();

    Nappula *n = lauta[mistaRivi][mistapRivi];
    if (n == nullptr)
        return;

    int tyyppi = n->getNimi();

    if (tyyppi == VK)
        VKliikkunut = true;
    else if (tyyppi == MK)
        MKliikkunut = true;
    else if (tyyppi == VT)
    {
        if (mistapRivi == 0)
            VDTliikkunut = true;
        if (mistapRivi == 7)
            VKTliikkunut = true;
    }
    else if (tyyppi == MT)
    {
        if (mistapRivi == 0)
            MDTliikkunut = true;
        if (mistapRivi == 7)
            MKTliikkunut = true;
    }
    lauta[mihinRivi][mihinpRivi] = n;
    lauta[mistaRivi][mistapRivi] = nullptr;
    siirtovuoro = (siirtovuoro == 0) ? 1 : 0;
}