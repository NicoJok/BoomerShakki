#include "siirto.h"

Siirto::Siirto(Ruutu alkuRuutu, Ruutu loppuRuutu) : alkuRuutu(alkuRuutu), loppuRuutu(loppuRuutu), lyhytLinna(false), pitkaLinna(false), miksiKorotetaan(0) {}
Siirto::Siirto(bool lyhytLinna, bool pitkaLinna) : lyhytLinna(lyhytLinna), pitkaLinna(pitkaLinna) {}

Ruutu Siirto::getAlkuRuutu() const {
	return alkuRuutu;
}
Ruutu Siirto::getLoppuRuutu() const {
	return loppuRuutu;
}
bool Siirto::onkoLyhytLinna() const {
	return lyhytLinna;
}
bool Siirto::onkoPitkaLinna() const {
	return pitkaLinna;
}