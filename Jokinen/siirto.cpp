#include "siirto.h"

Siirto::Siirto(Ruutu alku, Ruutu loppu) : alkuRuutu(alku), loppuRuutu(loppu), lyhytLinna(false), pitkalinna(false) {}

Siirto::Siirto(bool lyhyt, bool pitka) : lyhytLinna(lyhyt), pitkalinna(pitka) {}

Ruutu Siirto::getAlkuruutu() { return alkuRuutu; }
Ruutu Siirto::getLoppuruutu() { return loppuRuutu; }
bool Siirto::LyhytLinna() { return lyhytLinna; }
bool Siirto::PitkaLinna() { return pitkalinna; }