#pragma once
#include "ruutu.h"

class Siirto {
private:
	Ruutu alkuRuutu;
	Ruutu loppuRuutu;
	int miksiKorotetaan = 0; //Sotilaan korotus
	bool lyhytLinna;
	bool pitkaLinna;
public:
	Siirto(Ruutu alkuRuutu, Ruutu loppuRuutu);
	Siirto() {};
	Siirto(bool lyhytLinna, bool pitkaLinna); //Konstruktori linnoitukselle

	Ruutu getAlkuRuutu() const;
	Ruutu getLoppuRuutu() const;
	bool onkoLyhytLinna() const;
	bool onkoPitkaLinna() const;
};
