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
	void annaPseudoLaillisetSiirrot(std::list<Siirto>& lista);	// Pseudo-lailliset siirrot (ei tarkista shakkia).
	void annaLaillisetSiirrot(std::list<Siirto>& lista);		// Lailliset siirrot (suodattaa shakin jättävät pois).
	bool onkoSiirtoLaillinen(const Siirto& s);					// Onko annettu siirto laillisten listalla?
	bool onkoRuutuUhattu(int rivi, int sarake);				// Onko ruutu uhattu siirtovuoron nappuloilla?
	int getSiirtovuoro();									// Palauttaa siirtovuoron (0 = valkea, 1 = musta).
	void teeSiirto(Siirto s);									// Tee siirto (käytetään laillisuustarkistuksessa).
	void peruSiirto();										// Peru viimeinen teeSiirto.
	int getEpTargetRivi() const { return _epKohdeRivi; }
	int getEpTargetSarake() const { return _epKohdeSarake; }
	void setSiirtovuoro(int vari);							// Asettaa siirtovuoron.
	bool getOnkoValkeaKuningasLiikkunut();					// Linnoittuminen mahdollista?
	bool getOnkoMustaKuningasLiikkunut();					// Linnoittuminen mahdollista?
	bool getOnkoValkeaDTliikkunut();							// Linnoittuminen mahdollista?
	bool getOnkoValkeaKTliikkunut();							// Linnoittuminen mahdollista?
	bool getOnkoMustaDTliikkunut();							// Linnoittuminen mahdollista?
	bool getOnkoMustaKTliikkunut();							// Linnoittuminen mahdollista?


private:
	bool onkoRuutuUhattuVarilla(int rivi, int sarake, int uhkaavaVari);	// Onko ruutu uhattu annetun värin nappuloilla (linnoitusta varten).

	// Lisäinformaatio pelitilanteesta.
	int _siirtovuoro;										// 0 = valkea, 1 = musta
	bool _onkoValkeaKuningasLiikkunut;	// Linnoitus ei ole sallittu, jos kuningas on liikkunut.
	bool _onkoMustaKuningasLiikkunut;	// Linnoitus ei ole sallittu, jos kuningas on liikkunut.
	bool _onkoValkeaDTliikkunut;		// Linnoitus ei ole sallittu, jos daamisivustan torni on liikkunut.
	bool _onkoValkeaKTliikkunut;		// Linnoitus ei ole sallittu, jos kuningassivustan torni on liikkunut.
	bool _onkoMustaDTliikkunut;		// Linnoitus ei ole sallittu, jos daamisuvustan torni on liikkunut.	
	bool _onkoMustaKTliikkunut;		// Linnoitus ei ole sallittu, jos kuningassivustan torni on liikkunut.
	int _epKohdeRivi = -1;			// Ohestalyönti: kohderuudun rivi (-1 = ei mahdollista).
	int _epKohdeSarake = -1;		// Ohestalyönti: kohderuudun sarake.

	// PeruSiirto-tila
	Siirto _viimeisinSiirto;
	Nappula* _viimeisinSiirrettyNappula = nullptr;  // alkuruudussa ollut nappula (korotuksen peruutusta varten)
	Nappula* _viimeisinSyotyNappula = nullptr;
	int _viimeisinSyotyRivi = -1, _viimeisinSyotySarake = -1;
	bool _viimValkeaKuningas = false, _viimValkeaDT = false, _viimValkeaKT = false;
	bool _viimMustaKuningas = false, _viimMustaDT = false, _viimMustaKT = false;
	int _viimEpRivi = -1, _viimEpSarake = -1;
	bool _edellinenSiirtoLinna = false;
	bool _edellinenSiirtoEnPassant = false;

};

