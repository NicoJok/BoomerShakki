#pragma once

class Nappula;

class Asema {
	public:
		Asema();
		Nappula* lauta[8][8];

		Nappula* getNappula(int rivi, int sarake);

		//Valkeat nappulat
		static Nappula *vk, *vs, *vl, *vr, *vd, *vt;
		//Mustat nappulat
		static Nappula *mk, *ms, *ml, *mr, *md, *mt;
};
