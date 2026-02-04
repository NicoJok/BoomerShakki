#pragma once
#include "ruutu.h"

// Ns. "forward declaration". Nyt Asema-luokassa voidaa esitell? Nappula-osoittimia ilman,
// ett? nappula.h -tiedostoa t?ytyy includoida.
class Nappula;


// Siirto kuvaa nappulan siirtymisen ruudusta toiseen, mukaanlukien erikoissiirrot
// (linnoitus ja ohestaly?nti).
class Siirto
{
public:
	Siirto(Ruutu alku, Ruutu loppu);
	Siirto() : _alkuRuutu(0, 0), _loppuRuutu(0, 0), _lyhytLinna(false), _pitkaLinna(false) {}
	Siirto(bool lyhytLinna, bool pitkaLinna); // Linnoitus lyhyt (K-siipi) tai pitkä (D-siipi)
	Ruutu getAlkuruutu() const;
	Ruutu getLoppuruutu() const;
	bool onkoLyhytLinna() const;
	bool onkoPitkalinna() const;
	bool onkoOhestalyonti() const;
	void setOhestalyonti(bool b) { _onkoOhestalyonti = b; }
	// Vertaa onko siirto sama (alku, loppu, linna, ohestaly?nti, korotus)
	bool samaKuin(const Siirto& o) const;
	Nappula* _miksikorotetaan = 0;

private:
	Ruutu _alkuRuutu;
	Ruutu _loppuRuutu;
	bool _lyhytLinna;
	bool _pitkaLinna;
	bool _onkoOhestalyonti = false;
};