#pragma once

#include <list>
#include <string>
#include "siirto.h"


// Ns. "forward declaration". Nyt Asema-luokassa voidaan esitellä Nappula-osoittimia ilman,
// että nappula.h -tiedostoa täytyy includoida.
class Nappula;


// Asema sisältää kaiken tarvittavan informaation pelitilanteen kuvaamiseksi
// (nappuloiden sijainti, siirtovuoro, linnoitusoikeudet jne.).
class Asema
{

public:
	// Pelilauta sisältää osoittimet kunkin ruudun nappula-olioon (nullptr/NULL/0 jos ruutu on tyhjä).
	// Public-määreellä, koska tätä käytetään paljon muualla.
	Nappula* _lauta[8][8];
	
	Nappula* getNappula(int rivi, int sarake);

	// Nappula-oliot. Huomaa, että samaa nappulaa voidaan käyttää useissa eri ruuduissa.
	// Määritelty static-määreellä, joten nappulat ovat kaikkien lauta-olioiden "yhteiskäytössä"
	// (suorituskyvyn vuoksi).
	static Nappula* vk, * vd, * vt, * vl, * vr, * vs;	// Valkeat nappulat.
	static Nappula* mk, * md, * mt, * ml, * mr, * ms;	// Mustat nappulat.

	Asema();												// Asettaa alkuaseman.
	void paivitaAsema(Siirto*);								// Päivittää aseman annetulla siirrolla.
	int getSiirtovuoro();									// Palauttaa siirtovuoron (0 = valkea, 1 = musta).
	void setSiirtovuoro(int vari);							// Asettaa siirtovuoron.
	bool getOnkoValkeaKuningasLiikkunut();					// Linnoittuminen mahdollista?
	bool getOnkoMustaKuningasLiikkunut();					// Linnoittuminen mahdollista?
	bool getOnkoValkeaDTliikkunut();							// Linnoittuminen mahdollista?
	bool getOnkoValkeaKTliikkunut();							// Linnoittuminen mahdollista?
	bool getOnkoMustaDTliikkunut();							// Linnoittuminen mahdollista?
	bool getOnkoMustaKTliikkunut();							// Linnoittuminen mahdollista?


private:

	// Lisäinformaatio pelitilanteesta.
	int _siirtovuoro;										// 0 = valkea, 1 = musta
	bool _onkoValkeaKuningasLiikkunut;	// Linnoitus ei ole sallittu, jos kuningas on liikkunut.
	bool _onkoMustaKuningasLiikkunut;	// Linnoitus ei ole sallittu, jos kuningas on liikkunut.
	bool _onkoValkeaDTliikkunut;		// Linnoitus ei ole sallittu, jos daamisivustan torni on liikkunut.
	bool _onkoValkeaKTliikkunut;		// Linnoitus ei ole sallittu, jos kuningassivustan torni on liikkunut.
	bool _onkoMustaDTliikkunut;		// Linnoitus ei ole sallittu, jos daamisuvustan torni on liikkunut.	
	bool _onkoMustaKTliikkunut;		// Linnoitus ei ole sallittu, jos kuningassivustan torni on liikkunut.

};
