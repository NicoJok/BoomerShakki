#include "asema.h"

Asema::Asema()
{

    for (int rivi = 0; rivi < 8; rivi++)
    {
        for (int pRivi = 0; pRivi < 8; pRivi++)
        {
            lauta[rivi][pRivi] = nullptr;
        }
    }

    lauta[7][0] = new Torni(L"\u2656", 0, VT);
    lauta[7][1] = new Ratsu(L"\u2658", 0, VR);
    lauta[7][2] = new Lahetti(L"\u2657", 0, VL);
    lauta[7][3] = new Daami(L"\u2655", 0, VD);
    lauta[7][4] = new Kuningas(L"\u2654", 0, VK);
    lauta[7][5] = new Lahetti(L"\u2657", 0, VL);
    lauta[7][6] = new Ratsu(L"\u2658", 0, VR);
    lauta[7][7] = new Torni(L"\u2656", 0, VT);


    for (int i = 0; i < 8; i++)
        lauta[6][i] = new Sotilas(L"\u265F", 1, MS);

    lauta[0][0] = new Torni(L"\u265C", 1, MT);
    lauta[0][1] = new Ratsu(L"\u265E", 1, MR);
    lauta[0][2] = new Lahetti(L"\u265D", 1, ML);
    lauta[0][3] = new Daami(L"\u265B", 1, MD);
    lauta[0][4] = new Kuningas(L"\u265A", 1, MK);
    lauta[0][5] = new Lahetti(L"\u265D", 1, ML);
    lauta[0][6] = new Ratsu(L"\u265E", 1, MR);
    lauta[0][7] = new Torni(L"\u265C", 1, MT);

    for (int i = 0; i < 8; i++)
        lauta[1][i] = new Sotilas(L"\u265F", 1, MS);

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
            lauta[7][4] = nullptr;
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