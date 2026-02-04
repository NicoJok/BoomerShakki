#include "siirto.h"


Siirto::Siirto(Ruutu alkuRuutu, Ruutu loppuRuutu)
	: _alkuRuutu(alkuRuutu), _loppuRuutu(loppuRuutu), _lyhytLinna(false), _pitkaLinna(false), _onkoOhestalyonti(false)
{
}


Siirto::Siirto(bool lyhytLinna, bool pitkaLinna)
	: _alkuRuutu(0, 0), _loppuRuutu(0, 0), _lyhytLinna(lyhytLinna), _pitkaLinna(pitkaLinna), _onkoOhestalyonti(false)
{
}


Ruutu Siirto::getAlkuruutu() const
{
	return _alkuRuutu;
}


Ruutu Siirto::getLoppuruutu() const
{
	return _loppuRuutu;
}


bool Siirto::onkoLyhytLinna() const
{
	return _lyhytLinna;
}


bool Siirto::onkoPitkalinna() const
{
	return _pitkaLinna;
}

bool Siirto::onkoOhestalyonti() const
{
	return _onkoOhestalyonti;
}

bool Siirto::samaKuin(const Siirto& o) const
{
	if (onkoLyhytLinna() != o.onkoLyhytLinna() || onkoPitkalinna() != o.onkoPitkalinna()
		|| onkoOhestalyonti() != o.onkoOhestalyonti())
		return false;
	if (onkoLyhytLinna() || onkoPitkalinna())
		return true;
	Ruutu a1 = getAlkuruutu(), a2 = o.getAlkuruutu();
	Ruutu b1 = getLoppuruutu(), b2 = o.getLoppuruutu();
	if (a1.getRivi() != a2.getRivi() || a1.getSarake() != a2.getSarake()) return false;
	if (b1.getRivi() != b2.getRivi() || b1.getSarake() != b2.getSarake()) return false;
	if (_miksikorotetaan != o._miksikorotetaan) return false;
	return true;
}
