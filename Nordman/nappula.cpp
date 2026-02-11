#include "nappula.h"
#include "ruutu.h"
#include "asema.h"
#include <string>
#include <vector>

Nappula::Nappula(std::wstring u, int vari, int koodi) : unicode(u), vari(vari), _koodi(koodi) {}
void Nappula::setKoodi(int k) {
	_koodi = k;
}
void Nappula::setUnicode(std::wstring u) {
	unicode = u;
}

std::wstring Nappula::getUnicode() {
	return unicode;
}
int Nappula::getKoodi() {
	return _koodi;
}
void Nappula::setVari(int v) {
	vari = v;
}
int Nappula::getVari() {
	return vari;
}

void Nappula::lisaaSuoratSiirrot(std::vector<Siirto>& lista, Ruutu* ruutu, Asema* asema, int vari) {
	int alkuRivi = ruutu->getRivi();
	int alkuSarake = ruutu->getSarake();

	//Torni voi liikkua vaakasuoraan ja pystysuoraan, joten käydään kaikki mahdolliset ruudut läpi
	int suunnat[4][2] = { {1, 0}, {-1, 0}, {0, 1}, {0, -1} };//Ylös, alas, oikealle, vasemmalle

	//Käydään kaikki suunnat läpi
	for (int i = 0; i < 4; i++) {
		int rivinMuutos = suunnat[i][0];
		int sarakkeenMuutos = suunnat[i][1];

		int rivi = alkuRivi;
		int sarake = alkuSarake;

		while (true) {
			rivi += rivinMuutos;
			sarake += sarakkeenMuutos;

			//Tarkistetaan, että ruutu on laudan sisällä
			if (rivi < 0 || rivi > 7 || sarake < 0 || sarake > 7) {
				break;
			}

			Nappula* nappulaRuudussa = asema->lauta[rivi][sarake];

			if (nappulaRuudussa == nullptr) {
				//Ruutu on tyhjä, joten torni voi liikkua sinne
				lista.push_back(Siirto(Ruutu(alkuRivi, alkuSarake), Ruutu(rivi, sarake)));
			}
			else {
				// Ruutu on varattu, tarkistetaan onko siellä vastustajan vai oman värinen nappula
				if (nappulaRuudussa->getVari() != vari) {
					// Vastustajan nappula, torni voi syödä sen
					lista.push_back(Siirto(Ruutu(alkuRivi, alkuSarake), Ruutu(rivi, sarake)));
				}
				break;
			}
		}

	}
}

void Nappula::lisaaVinotSiirrot(std::vector<Siirto>& lista, Ruutu* ruutu, Asema* asema, int vari) {
	int alkuRivi = ruutu->getRivi();
	int alkuSarake = ruutu->getSarake();

	//Lähetti voi liikkua vinottain
	int suunnat[4][2] = { {1, 1}, {1, -1}, {-1, 1}, {-1, -1} };//Ylös, alas, oikealle, vasemmalle rivi + sarake

	//Sama kun torni, mutta liikkeet vinottain
	for (int i = 0; i < 4; i++) {
		int rivinMuutos = suunnat[i][0];
		int sarakkeenMuutos = suunnat[i][1];

		int rivi = alkuRivi;
		int sarake = alkuSarake;

		while (true) {
			rivi += rivinMuutos;
			sarake += sarakkeenMuutos;

			//Tarkistetaan, että ruutu on laudan sisällä
			if (rivi < 0 || rivi > 7 || sarake < 0 || sarake > 7) {
				break;
			}

			Nappula* nappulaRuudussa = asema->lauta[rivi][sarake];

			if (nappulaRuudussa == nullptr) {
				//Ruutu on tyhjä, joten torni voi liikkua sinne
				lista.push_back(Siirto(Ruutu(alkuRivi, alkuSarake), Ruutu(rivi, sarake)));
			}
			else {
				// Ruutu on varattu, tarkistetaan onko siellä vastustajan vai oman värinen nappula
				if (nappulaRuudussa->getVari() != vari) {
					// Vastustajan nappula, torni voi syödä sen
					lista.push_back(Siirto(Ruutu(alkuRivi, alkuSarake), Ruutu(rivi, sarake)));
				}
				break;
			}
		}

	}
}

void Torni::annaSiirrot(std::vector<Siirto>& lista, Ruutu* ruutu, Asema* asema, int vari) {
	lisaaSuoratSiirrot(lista, ruutu, asema, vari);
}

void Ratsu::annaSiirrot(std::vector<Siirto>& lista, Ruutu* ruutu, Asema* asema, int vari) {
	int alkurivi = ruutu->getRivi();
	int alkusarake = ruutu->getSarake();

	//Ratsu voi liikkua L-muodossa, joten käydään kaikki mahdolliset ruudut läpi
	int liikkeet[8][2] = {
		{2, 1}, {2, -1}, {-2, 1}, {-2, -1}, //2 ylös/alas, 1 oikealle/vasemmalle
		{1, 2}, {1, -2}, {-1, 2}, {-1, -2} }; //1 ylös/alas, 2 oikealle/vasemmalle

	for (int i = 0; i < 8; i++) {
		int rivi = alkurivi + liikkeet[i][0];
		int sarake = alkusarake + liikkeet[i][1];

		//Tarkistetaan, että ruutu on laudan sisällä
		if (rivi < 0 || rivi > 7 || sarake < 0 || sarake > 7) {
			continue; //Ei lisätä listaan, mutta jatketaan seuraavaan liikkeeseen
		}

		Nappula* nappulaRuudussa = asema->lauta[rivi][sarake];

		if (nappulaRuudussa == nullptr || nappulaRuudussa->getVari() != vari) {
			//Ruutu on tyhjä tai siellä on vastustajan nappula, joten ratsu voi liikkua sinne
			lista.push_back(Siirto(Ruutu(alkurivi, alkusarake), Ruutu(rivi, sarake)));
		}
	}
}

void Lahetti::annaSiirrot(std::vector<Siirto>& lista, Ruutu* ruutu, Asema* asema, int vari) {
	lisaaVinotSiirrot(lista, ruutu, asema, vari);
}

void Daami::annaSiirrot(std::vector<Siirto>& lista, Ruutu* ruutu, Asema* asema, int vari) {
	//Daami yhdistää tornin ja lähetin liikkeet, joten kutsutaan lisaaSuoratSiirrot ja lisaaVinotSiirrot
	lisaaSuoratSiirrot(lista, ruutu, asema, vari);
	lisaaVinotSiirrot(lista, ruutu, asema, vari);
}

void Kuningas::annaSiirrot(std::vector<Siirto>& lista, Ruutu* ruutu, Asema* asema, int vari) {
	int alkurivi = ruutu->getRivi();
	int alkusarake = ruutu->getSarake();

	//Kuningas voi liikkua yhden ruudun mihin tahansa suuntaan, joten käydään kaikki mahdolliset ruudut läpi
	int liikkeet[8][2] = {
		{1, 0}, {-1, 0}, {0, 1}, {0, -1}, //Ylös, alas, oikealle, vasemmalle
		{1, 1}, {1, -1}, {-1, 1}, {-1, -1} }; //Vinottain

	for (int i = 0; i < 8; i++) {
		int rivi = alkurivi + liikkeet[i][0];
		int sarake = alkusarake + liikkeet[i][1];

		if (rivi < 0 || rivi > 7 || sarake < 0 || sarake > 7) {
			continue; //Ei lisätä listaan, mutta jatketaan seuraavaan liikkeeseen
		}

		Nappula* nappulaRuudussa = asema->lauta[rivi][sarake];

		if (nappulaRuudussa == nullptr || nappulaRuudussa->getVari() != vari) {
			//Ruutu on tyhjä tai siellä on vastustajan nappula, joten kuningas voi liikkua sinne
			lista.push_back(Siirto(Ruutu(alkurivi, alkusarake), Ruutu(rivi, sarake))); //Lisätään siirto listaan
		}
	}

	//Tarkistetaan linnoitusmahdollisuudet, mutta vain jos kuningas ei ole liikkunut
	if ((vari == 0 && alkurivi == 0 && alkusarake == 4) || (vari == 1 && alkurivi == 7 && alkusarake == 4)) {
		//Lyhyt linnoitus
		if(vari == 0) //Valkean linnoitus
		{
			if (!asema->getOnkoValkeaKuningasLiikkunut() && !asema->getOnkoValkeaKTliikkunut() &&
				asema->lauta[0][5] == nullptr && asema->lauta[0][6] == nullptr) { //Ruutujen pitää olla tyhjiä
				lista.push_back(Siirto(Ruutu(0, 4), Ruutu(0, 6))); 
			}
		}
		else //Mustan linnoitus
		{
			if (!asema->getOnkoMustaKuningasLiikkunut() && !asema->getOnkoMustaKTliikkunut() &&
				asema->lauta[7][5] == nullptr && asema->lauta[7][6] == nullptr) {
				lista.push_back(Siirto(Ruutu(7, 4), Ruutu(7, 6)));
			}
		}

		//Pitkä linnoitus
		if(vari == 0){
			if (!asema->getOnkoValkeaKuningasLiikkunut() && !asema->getOnkoValkeaDTliikkunut() &&
				asema->lauta[0][1] == nullptr && asema->lauta[0][2] == nullptr && asema->lauta[0][3] == nullptr) { //sama kuin lyhyessä, mutta ruutuja on yksi enemmän
				lista.push_back(Siirto(Ruutu(0, 4), Ruutu(0, 2)));
			}
		}
		else{
			if (!asema->getOnkoMustaKuningasLiikkunut() && !asema->getOnkoMustaDTliikkunut() &&
				asema->lauta[7][1] == nullptr && asema->lauta[7][2] == nullptr && asema->lauta[7][3] == nullptr) {
				lista.push_back(Siirto(Ruutu(7, 4), Ruutu(7, 2)));
			}
		}
	}
}

void Sotilas::annaSiirrot(std::vector<Siirto>& lista, Ruutu* ruutu, Asema* asema, int vari) {
	int alkuRivi = ruutu->getRivi();
	int alkuSarake = ruutu->getSarake();
	int suunta = (vari == 0) ? 1 : -1;  // Valkea ylös (+1), Musta alas (-1)
	

	//Eteenpäin 1 ruutu
	int uusiRivi = alkuRivi + suunta;
	if (uusiRivi >= 0 && uusiRivi <= 7) {
		if (asema->lauta[uusiRivi][alkuSarake] == nullptr) {

			// Tarkistetaan voidaanko korottaa (Valkea rivi 7, Musta rivi 0)
			if ((vari == 0 && uusiRivi == 7) || (vari == 1 && uusiRivi == 0)) {
				//Lisätänä 4 siirtoa korotusta varten, koska sotilaan korotus tapahtuu siirron jälkeen, eikä ennen, joten kaikki 4 vaihtoehtoa pitää lisätä
				int nappulat[4];
				if (vari == 0) {
					nappulat[0] = VD;  // Daami
					nappulat[1] = VT;  // Torni
					nappulat[2] = VR;  // Ratsu
					nappulat[3] = VL;  // Lähetti
				}
				else {
					nappulat[0] = MD;
					nappulat[1] = MT;
					nappulat[2] = MR;
					nappulat[3] = ML;
				}

				for (int i = 0; i < 4; i++) {
					Siirto siirto(Ruutu(alkuRivi, alkuSarake), Ruutu(uusiRivi, alkuSarake));
					siirto.setKorotusNappula(nappulat[i]);
					lista.push_back(siirto);
				}
			}
			else {
				// Normaali siirto (ei korotusta)
				lista.push_back(Siirto(Ruutu(alkuRivi, alkuSarake), Ruutu(uusiRivi, alkuSarake)));
			}
		}
	}

	//Kahden ruudun eteenpäin siirto, mutta vain alkuriviltä ja jos edessä ei ole nappulaa
	int alkurivi = (vari == 0) ? 1 : 6;  // Valkea rivi 1, Musta rivi 6
	if (alkuRivi == alkurivi) {
		int uusiRivi2 = alkuRivi + 2 * suunta;
		if (asema->lauta[uusiRivi2][alkuSarake] == nullptr &&
			asema->lauta[alkuRivi + suunta][alkuSarake] == nullptr) {
			lista.push_back(Siirto(Ruutu(alkuRivi, alkuSarake), Ruutu(uusiRivi2, alkuSarake)));
		}
	}

	//Syöminen vinottain
	for (int sarakkeenMuutos = -1; sarakkeenMuutos <= 1; sarakkeenMuutos += 2) {
		int uusiSarake = alkuSarake + sarakkeenMuutos;
		if (uusiSarake >= 0 && uusiSarake <= 7 && uusiRivi >= 0 && uusiRivi <= 7) {
			Nappula* kohde = asema->lauta[uusiRivi][uusiSarake];
			if (kohde != nullptr && kohde->getVari() != vari) {

				//Tarkistetaan voidaanko korottaa syödessä (Valkea rivi 7, Musta rivi 0)
				if ((vari == 0 && uusiRivi == 7) || (vari == 1 && uusiRivi == 0)) {
					//Korotus syödessä, sama logiikka kuin normaalissa korotuksessa
					int nappulat[4];
					if (vari == 0) {
						nappulat[0] = VD;
						nappulat[1] = VT;
						nappulat[2] = VR;
						nappulat[3] = VL;
					}
					else {
						nappulat[0] = MD;
						nappulat[1] = MT;
						nappulat[2] = MR;
						nappulat[3] = ML;
					}

					for (int i = 0; i < 4; i++) {
						Siirto siirto(Ruutu(alkuRivi, alkuSarake), Ruutu(uusiRivi, uusiSarake));
						siirto.setKorotusNappula(nappulat[i]);
						lista.push_back(siirto);
					}
				}
				else {
					// Normaali syönti (ei korotusta)
					lista.push_back(Siirto(Ruutu(alkuRivi, alkuSarake), Ruutu(uusiRivi, uusiSarake)));
				}
			}
		}
	}
}