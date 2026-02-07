#pragma once
#include "nappula.h"
#include "siirto.h"

class Asema {
private:
    // Kaikki 32 nappulaa (pointtereita)
    // Valkeat nappulat
    Nappula* vk;   // Valkea kuningas
    Nappula* vd;   // Valkea daami
    Nappula* vt1;  // Valkea torni 1 (a1)
    Nappula* vt2;  // Valkea torni 2 (h1)
    Nappula* vl1;  // Valkea l‰hetti 1 (c1)
    Nappula* vl2;  // Valkea l‰hetti 2 (f1)
    Nappula* vr1;  // Valkea ratsu 1 (b1)
    Nappula* vr2;  // Valkea ratsu 2 (g1)
    Nappula* vs1;  // Valkea sotilas 1 (a2)
    Nappula* vs2;  // Valkea sotilas 2 (b2)
    Nappula* vs3;  // Valkea sotilas 3 (c2)
    Nappula* vs4;  // Valkea sotilas 4 (d2)
    Nappula* vs5;  // Valkea sotilas 5 (e2)
    Nappula* vs6;  // Valkea sotilas 6 (f2)
    Nappula* vs7;  // Valkea sotilas 7 (g2)
    Nappula* vs8;  // Valkea sotilas 8 (h2)

    // Mustat nappulat
    Nappula* mk;   // Musta kuningas
    Nappula* md;   // Musta daami
    Nappula* mt1;  // Musta torni 1 (a8)
    Nappula* mt2;  // Musta torni 2 (h8)
    Nappula* ml1;  // Musta l‰hetti 1 (c8)
    Nappula* ml2;  // Musta l‰hetti 2 (f8)
    Nappula* mr1;  // Musta ratsu 1 (b8)
    Nappula* mr2;  // Musta ratsu 2 (g8)
    Nappula* ms1;  // Musta sotilas 1 (a7)
    Nappula* ms2;  // Musta sotilas 2 (b7)
    Nappula* ms3;  // Musta sotilas 3 (c7)
    Nappula* ms4;  // Musta sotilas 4 (d7)
    Nappula* ms5;  // Musta sotilas 5 (e7)
    Nappula* ms6;  // Musta sotilas 6 (f7)
    Nappula* ms7;  // Musta sotilas 7 (g7)
    Nappula* ms8;  // Musta sotilas 8 (h7)

	int siirtovuoro; // 0 = valkea, 1 = musta
    bool onkoValkeaKuningasLiikkunut = false;
	bool onkoMustaKuningasLiikkunut = false;
	bool onkoValkeaDTliikkunut = false; //Daamin torni
	bool onkoValkeaKTliikkunut = false; //Kuninkaan torni
	bool onkoMustaDTliikkunut = false; 
	bool onkoMustaKTliikkunut = false; 

public:
    Nappula* lauta[8][8];  // 8x8 shakkilauta

    Asema();  // Constructor luo alkuaseman

	void paivitaAsema(Siirto* siirto); // P‰ivitt‰‰ aseman siirron j‰lkeen
	void annaLaillisetSiirrot(std::vector<Siirto>& lista); // Palauttaa kaikki siirtovuoroisen pelaajan lailliset siirrot

	int getSiirtoVuoro(); // Palauttaa 0 jos valkean vuoro, 1 jos mustan vuoro
	void setSiirtoVuoro(int vari); // Asettaa vuoron (0 = valkea, 1 = musta)

	bool getOnkoValkeaKuningasLiikkunut(); // Palauttaa true jos valkean kuningas on liikkunut, muuten false
	bool getOnkoMustaKuningasLiikkunut(); // Palauttaa true jos mustan kuningas on liikkunut, muuten false
	bool getOnkoValkeaDTliikkunut(); // Palauttaa true jos valkean daami on liikkunut, muuten false
	bool getOnkoMustaDTliikkunut(); // Palauttaa true jos mustan daami on liikkunut, muuten false
	bool getOnkoValkeaKTliikkunut(); // Palauttaa true jos valkean kuningas on liikkunut muuten false
	bool getOnkoMustaKTliikkunut(); // Palauttaa true jos mustan kuningas muuten false
};
