#include "siirto.h"

Siirto::Siirto(Ruutu alku, Ruutu loppu, Korotus koro) : alkuRuutu(alku), loppuRuutu(loppu), koro(koro), lyhytLinna(false), pitkalinna(false) {}

Siirto::Siirto(bool lyhyt, bool pitka) : lyhytLinna(lyhyt), pitkalinna(pitka) {}

Ruutu Siirto::getAlkuruutu() { return alkuRuutu; }
Ruutu Siirto::getLoppuruutu() { return loppuRuutu; }
bool Siirto::LyhytLinna() { return lyhytLinna; }
bool Siirto::PitkaLinna() { return pitkalinna; }
Korotus Siirto::getKorotus() { return koro; }