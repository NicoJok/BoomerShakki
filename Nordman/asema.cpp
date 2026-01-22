#include <iostream>
#include "asema.h"
#include "nappula.h"

Nappula* Asema::vk = new Nappula(L"\u2654", 0, VK);
Nappula* Asema::vs = new Nappula(L"\u2659", 0, VS);
Nappula* Asema::vl = new Nappula(L"\u2658", 0, VL);
Nappula* Asema::vr = new Nappula(L"\u2657", 0, VR);
Nappula* Asema::vd = new Nappula(L"\u2656", 0, VD);
Nappula* Asema::vt = new Nappula(L"\u2655", 0, VT);

Nappula* Asema::mk = new Nappula(L"\u265A", 1, MK);
Nappula* Asema::ms = new Nappula(L"\u265F", 1, MS);
Nappula* Asema::ml = new Nappula(L"\u265E", 1, ML);
Nappula* Asema::mr = new Nappula(L"\u265D", 1, MR);
Nappula* Asema::md = new Nappula(L"\u265C", 1, MD);
Nappula* Asema::mt = new Nappula(L"\u265B", 1, MT);

Asema::Asema() {
	// Tyhjä lauta
	for (int rivi = 0; rivi < 8; rivi++) {
		for (int sarake = 0; sarake < 8; sarake++) {
			lauta[rivi][sarake] = nullptr;
		}
	}
	// Aseta valkeat nappulat
	lauta[7][4] = vk;
	lauta[6][0] = vs; lauta[6][1] = vs; lauta[6][2] = vs; lauta[6][3] = vs;
	lauta[6][4] = vs; lauta[6][5] = vs; lauta[6][6] = vs; lauta[6][7] = vs;
	lauta[7][1] = vl; lauta[7][6] = vl;
	lauta[7][2] = vr; lauta[7][5] = vr;
	lauta[7][0] = vd; lauta[7][7] = vd;
	lauta[7][3] = vt;

	// Aseta mustat nappulat
	lauta[0][4] = mk;
	lauta[1][0] = ms; lauta[1][1] = ms; lauta[1][2] = ms; lauta[1][3] = ms;
	lauta[1][4] = ms; lauta[1][5] = ms; lauta[1][6] = ms; lauta[1][7] = ms;
	lauta[0][1] = ml; lauta[0][6] = ml;
	lauta[0][2] = mr; lauta[0][5] = mr;
	lauta[0][0] = md; lauta[0][7] = md;
	lauta[0][3] = mt;
}

Nappula* Asema::getNappula(int rivi, int sarake) {
	if (rivi < 0 || rivi > 7 || sarake < 0 || sarake > 7) return nullptr;
	return lauta[rivi][sarake];
}




