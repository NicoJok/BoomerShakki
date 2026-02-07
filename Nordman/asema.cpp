#include "asema.h"

Asema::Asema() {
	// Alustetaan shakkilauta tyhj‰ksi (nullptr)
	for (int rivi = 0; rivi < 8; rivi++) {
		for (int sarake = 0; sarake < 8; sarake++) {
			lauta[rivi][sarake] = nullptr;
		}
	}

	// Alustetaan kaikki nappulat alkuasentoon
	// Valkeat nappulat
	vk = new Kuningas(L"\u2654", 0, VK);  // Valkea kuningas
	vd = new Daami(L"\u2655", 0, VD);  // Valkea daami
	vt1 = new Torni(L"\u2656", 0, VT);  // Valkea torni 1 (a1)
	vt2 = new Torni(L"\u2656", 0, VT);  // Valkea torni 2 (h1)
	vl1 = new Lahetti(L"\u2657", 0, VL);  // Valkea l‰hetti 1 (c1)
	vl2 = new Lahetti(L"\u2657", 0, VL);  // Valkea l‰hetti 2 (f1)
	vr1 = new Ratsu(L"\u2658", 0, VR);  // Valkea ratsu 1 (b1)
	vr2 = new Ratsu(L"\u2658", 0, VR);  // Valkea ratsu 2 (g1)
	vs1 = new Sotilas(L"\u2659", 0, VS);  // Valkea sotilas 1 (a2)
	vs2 = new Sotilas(L"\u2659", 0, VS);  // Valkea sotilas 2 (b2)
	vs3 = new Sotilas(L"\u2659", 0, VS);  // Valkea sotilas 3 (c2)
	vs4 = new Sotilas(L"\u2659", 0, VS);  // Valkea sotilas 4 (d2)
	vs5 = new Sotilas(L"\u2659", 0, VS);  // Valkea sotilas 5 (e2)
	vs6 = new Sotilas(L"\u2659", 0, VS);  // Valkea sotilas 6 (f2)
	vs7 = new Sotilas(L"\u2659", 0, VS);  // Valkea sotilas 7 (g2)
	vs8 = new Sotilas(L"\u2659", 0, VS);  // Valkea sotilas 8 (h2)

	// Mustat nappulat
	mk = new Kuningas(L"\u265A", 1, MK);  // Musta kuningas
	md = new Daami(L"\u265B", 1, MD);  // Musta daami
	mt1 = new Torni(L"\u265C", 1, MT);  // Musta torni 1 (a8)
	mt2 = new Torni(L"\u265C", 1, MT);  // Musta torni 2 (h8)
	ml1 = new Lahetti(L"\u265D", 1, ML);  // Musta l‰hetti 1 (c8)
	ml2 = new Lahetti(L"\u265D", 1, ML);  // Musta l‰hetti 2 (f8)
	mr1 = new Ratsu(L"\u265E", 1, MR);  // Musta ratsu 1 (b8)
	mr2 = new Ratsu(L"\u265E", 1, MR);  // Musta ratsu 2 (g8)
	ms1 = new Sotilas(L"\u265F", 1, MS);  // Musta sotilas 1 (a7)
	ms2 = new Sotilas(L"\u265F", 1, MS);  // Musta sotilas 2 (b7)
	ms3 = new Sotilas(L"\u265F", 1, MS);  // Musta sotilas 3 (c7)
	ms4 = new Sotilas(L"\u265F", 1, MS);  // Musta sotilas 4 (d7)
	ms5 = new Sotilas(L"\u265F", 1, MS);  // Musta sotilas 5 (e7)
	ms6 = new Sotilas(L"\u265F", 1, MS);  // Musta sotilas 6 (f7)
	ms7 = new Sotilas(L"\u265F", 1, MS);  // Musta sotilas 7 (g7)
	ms8 = new Sotilas(L"\u265F", 1, MS);  // Musta sotilas 8 (h7)

	// Asetetaan valkeat nappulat laudalle
	lauta[0][0] = vt1;  // a1
	lauta[0][1] = vr1;  // b1
	lauta[0][2] = vl1;  // c1
	lauta[0][3] = vd;   // d1
	lauta[0][4] = vk;   // e1
	lauta[0][5] = vl2;  // f1
	lauta[0][6] = vr2;  // g1
	lauta[0][7] = vt2;  // h1
	lauta[1][0] = vs1;  // a2
	lauta[1][1] = vs2;  // b2
	lauta[1][2] = vs3;  // c2
	lauta[1][3] = vs4;  // d2
	lauta[1][4] = vs5;  // e2
	lauta[1][5] = vs6;  // f2
	lauta[1][6] = vs7;  // g2
	lauta[1][7] = vs8;  // h2

	// Asetetaan mustat nappulat laudalle
	lauta[7][0] = mt1;  // a8
	lauta[7][1] = mr1;  // b8
	lauta[7][2] = ml1;  // c8
	lauta[7][3] = md;   // d8
	lauta[7][4] = mk;   // e8
	lauta[7][5] = ml2;  // f8
	lauta[7][6] = mr2;  // g8
	lauta[7][7] = mt2;  // h8
	lauta[6][0] = ms1;  // a7
	lauta[6][1] = ms2;  // b7
	lauta[6][2] = ms3;  // c7
	lauta[6][3] = ms4;  // d7
	lauta[6][4] = ms5;  // e7
	lauta[6][5] = ms6;  // f7
	lauta[6][6] = ms7;  // g7
	lauta[6][7] = ms8;  // h7
}

int Asema::getSiirtoVuoro() {
	return siirtovuoro;
}

void Asema::setSiirtoVuoro(int vari) {
	siirtovuoro = vari;
}

bool Asema::getOnkoValkeaKuningasLiikkunut() {
	return onkoValkeaKuningasLiikkunut;
}

bool Asema::getOnkoMustaKuningasLiikkunut() {
	return onkoMustaKuningasLiikkunut;
}

bool Asema::getOnkoValkeaDTliikkunut() {
	return onkoValkeaDTliikkunut;
}

bool Asema::getOnkoMustaDTliikkunut() {
	return onkoMustaDTliikkunut;
}

bool Asema::getOnkoValkeaKTliikkunut() {
	return onkoValkeaKTliikkunut;
}

bool Asema::getOnkoMustaKTliikkunut() {
	return onkoMustaKTliikkunut;
}

void Asema::paivitaAsema(Siirto* siirto) {
	//Ruudut otetaan siirto-olion avulla
	Ruutu alkuRuutu = siirto->getAlkuRuutu();
	Ruutu loppuRuutu = siirto->getLoppuRuutu();

	int alkuRivi = alkuRuutu.getRivi();
	int alkuSarake = alkuRuutu.getSarake();
	int loppuRivi = loppuRuutu.getRivi();
	int loppuSarake = loppuRuutu.getSarake();

	//Otetaan nappula alkuruudusta
	Nappula* siirrettavaNappula = lauta[alkuRivi][alkuSarake];

	//Siirret‰‰n nappula loppuruutuun
	lauta[loppuRivi][loppuSarake] = siirrettavaNappula;

	//Tyhjennet‰‰n alkuruutu
	lauta[alkuRivi][alkuSarake] = nullptr;

	//Tarkistetaan onko kuningas tai torni liikkunut
	//Kuninkaat
	//Valkoinen kuningas
	if (siirrettavaNappula->getKoodi() == VK) {
		onkoValkeaKuningasLiikkunut = true;
	}
	//Musta kuningas
	if (siirrettavaNappula->getKoodi() == MK) {
		onkoMustaKuningasLiikkunut = true;
	}
	//Valkoiset tornit
	//Daamin torni
	if (alkuRuutu == Ruutu(0, 0)) {
		onkoValkeaDTliikkunut = true;
	}
	//Kuninkaan torni
	if (alkuRuutu == Ruutu(0, 7)){
		onkoValkeaKTliikkunut = true;
	}
	//Mustat tornit
	//Daamin torni
	if (alkuRuutu == Ruutu(7, 0)) {
		onkoMustaDTliikkunut = true;
	}
	//Kuninkaan torni
	if (alkuRuutu == Ruutu(7, 7)) {
		onkoMustaKTliikkunut = true;
	}

	//Vaihdetaan siirtovuoro
	if (siirtovuoro == 0) {
		siirtovuoro = 1;
	}
	else {
		siirtovuoro = 0;
	}
}

void Asema::annaLaillisetSiirrot(std::vector<Siirto>& lista) {
	//K‰yd‰‰n lauta l‰pi
	for (int rivi = 0; rivi < 8; rivi++) {
		for (int sarake = 0; sarake < 8; sarake++) {
			Nappula* nappula = lauta[rivi][sarake];

			//Jos ruudusssa on nappula ja se on siirtovuorossa
			if (nappula != nullptr && nappula->getVari() == siirtovuoro) {
				Ruutu ruutu(rivi, sarake);
					nappula->annaSiirrot(lista, &ruutu, this, siirtovuoro);
			}
		}
	}
}

