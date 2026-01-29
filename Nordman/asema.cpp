#include "asema.h"
#include "nappula.h" 
#include <cstring>   


Nappula* Asema::vk = nullptr;
Nappula* Asema::vd = nullptr;
Nappula* Asema::vt = nullptr;
Nappula* Asema::vl = nullptr;
Nappula* Asema::vr = nullptr;
Nappula* Asema::vs = nullptr;

Nappula* Asema::mk = nullptr;
Nappula* Asema::md = nullptr;
Nappula* Asema::mt = nullptr;
Nappula* Asema::ml = nullptr;
Nappula* Asema::mr = nullptr;
Nappula* Asema::ms = nullptr;

Asema::Asema()
{
	
	for (int r = 0; r < 8; ++r)
		for (int c = 0; c < 8; ++c)
			_lauta[r][c] = nullptr;


	_siirtovuoro = 0; // Alussa valkea aloittaa
	_onkoValkeaKuningasLiikkunut = false;
	_onkoMustaKuningasLiikkunut = false;
	_onkoValkeaDTliikkunut = false;
	_onkoValkeaKTliikkunut = false;
	_onkoMustaDTliikkunut = false;
	_onkoMustaKTliikkunut = false;


	if (!vt) {		
		vt = new Torni(L"\u2656", 0, VT);      
		vr = new Ratsu(L"\u2658", 0, VR);      
		vl = new Lahetti(L"\u2657", 0, VL);    
		vd = new Daami(L"\u2655", 0, VD);      
		vk = new Kuningas(L"\u2654", 0, VK);   
		vs = new Sotilas(L"\u2659", 0, VS);    

		mt = new Torni(L"\u265C", 1, MT);      
		mr = new Ratsu(L"\u265E", 1, MR);      
		ml = new Lahetti(L"\u265D", 1, ML);    
		md = new Daami(L"\u265B", 1, MD);      
		mk = new Kuningas(L"\u265A", 1, MK);   
		ms = new Sotilas(L"\u265F", 1, MS);    
	}

	_lauta[0][0] = mt;  
	_lauta[0][1] = mr;  
	_lauta[0][2] = ml;  
	_lauta[0][3] = md;  
	_lauta[0][4] = mk;  
	_lauta[0][5] = ml;  
	_lauta[0][6] = mr;  
	_lauta[0][7] = mt;  

	for (int c = 0; c < 8; ++c)
		_lauta[1][c] = ms;

	for (int c = 0; c < 8; ++c)
		_lauta[6][c] = vs;

	_lauta[7][0] = vt; 
	_lauta[7][1] = vr; 
	_lauta[7][2] = vl;  
	_lauta[7][3] = vd;  
	_lauta[7][4] = vk;  
	_lauta[7][5] = vl;  
	_lauta[7][6] = vr;  
	_lauta[7][7] = vt;  
}

void Asema::paivitaAsema(Siirto* siirto)
{
	if (!siirto) return;

	// Tarkistetaan onko siirto linnoitus
	if (siirto->onkoLyhytLinna()) {
		// Lyhyt linna (O-O)
		if (_siirtovuoro == 0) {
			// Valkea lyhyt linna: kuningas e1->g1, torni h1->f1
			_lauta[7][4] = nullptr;  // e1 tyhjäksi
			_lauta[7][7] = nullptr;  // h1 tyhjäksi
			_lauta[7][6] = vk;       // g1 kuningas
			_lauta[7][5] = vt;       // f1 torni
			_onkoValkeaKuningasLiikkunut = true;
			_onkoValkeaKTliikkunut = true;
		}
		else {
			// Musta lyhyt linna: kuningas e8->g8, torni h8->f8
			_lauta[0][4] = nullptr;  // e8 tyhjäksi
			_lauta[0][7] = nullptr;  // h8 tyhjäksi
			_lauta[0][6] = mk;       // g8 kuningas
			_lauta[0][5] = mt;       // f8 torni
			_onkoMustaKuningasLiikkunut = true;
			_onkoMustaKTliikkunut = true;
		}
		_siirtovuoro = 1 - _siirtovuoro; // Vaihdetaan siirtovuoro
		return;
	}

	if (siirto->onkoPitkalinna()) {
		// Pitkä linna (O-O-O)
		if (_siirtovuoro == 0) {
			// Valkea pitkä linna: kuningas e1->c1, torni a1->d1
			_lauta[7][4] = nullptr;  // e1 tyhjäksi
			_lauta[7][0] = nullptr;  // a1 tyhjäksi
			_lauta[7][2] = vk;       // c1 kuningas
			_lauta[7][3] = vt;       // d1 torni
			_onkoValkeaKuningasLiikkunut = true;
			_onkoValkeaDTliikkunut = true;
		}
		else {
			// Musta pitkä linna: kuningas e8->c8, torni a8->d8
			_lauta[0][4] = nullptr;  // e8 tyhjäksi
			_lauta[0][0] = nullptr;  // a8 tyhjäksi
			_lauta[0][2] = mk;       // c8 kuningas
			_lauta[0][3] = mt;       // d8 torni
			_onkoMustaKuningasLiikkunut = true;
			_onkoMustaDTliikkunut = true;
		}
		_siirtovuoro = 1 - _siirtovuoro; // Vaihdetaan siirtovuoro
		return;
	}

	// Normaali siirto
	Ruutu alkuRuutu = siirto->getAlkuruutu();
	Ruutu loppuRuutu = siirto->getLoppuruutu();
	
	int alkuRivi = alkuRuutu.getRivi();
	int alkuSarake = alkuRuutu.getSarake();
	int loppuRivi = loppuRuutu.getRivi();
	int loppuSarake = loppuRuutu.getSarake();

	// Otetaan alkuruudussa oleva nappula talteen
	Nappula* nappula = _lauta[alkuRivi][alkuSarake];
	
	if (!nappula) return; // Jos alkuruudussa ei ole nappulaa, ei tehdä mitään

	// Tarkistetaan onko liikkunut nappula kuningas tai torni
	int nappulaKoodi = nappula->getKoodi();
	
	// Päivitetään kuninkaan liikkumislippu
	if (nappulaKoodi == VK) {
		_onkoValkeaKuningasLiikkunut = true;
	}
	else if (nappulaKoodi == MK) {
		_onkoMustaKuningasLiikkunut = true;
	}
	
	// Päivitetään tornien liikkumislippu
	if (nappulaKoodi == VT) {
		// Tarkistetaan kumpi torni
		if (alkuRivi == 7 && alkuSarake == 0) {
			_onkoValkeaDTliikkunut = true; // Daamisivustan torni
		}
		else if (alkuRivi == 7 && alkuSarake == 7) {
			_onkoValkeaKTliikkunut = true; // Kuningassivustan torni
		}
	}
	else if (nappulaKoodi == MT) {
		// Tarkistetaan kumpi torni
		if (alkuRivi == 0 && alkuSarake == 0) {
			_onkoMustaDTliikkunut = true; // Daamisivustan torni
		}
		else if (alkuRivi == 0 && alkuSarake == 7) {
			_onkoMustaKTliikkunut = true; // Kuningassivustan torni
		}
	}

	// Siirretään nappula uuteen ruutuun
	_lauta[alkuRivi][alkuSarake] = nullptr;
	_lauta[loppuRivi][loppuSarake] = nappula;

	// Vaihdetaan siirtovuoro
	_siirtovuoro = 1 - _siirtovuoro;
}

Nappula* Asema::getNappula(int rivi, int sarake)
{
	if (rivi < 0 || rivi >= 8 || sarake < 0 || sarake >= 8) return nullptr;
	return _lauta[rivi][sarake];
}

int Asema::getSiirtovuoro()
{
	return _siirtovuoro;
}

void Asema::setSiirtovuoro(int vari)
{
	_siirtovuoro = vari;
}

bool Asema::getOnkoValkeaKuningasLiikkunut()
{
	return _onkoValkeaKuningasLiikkunut;
}

bool Asema::getOnkoMustaKuningasLiikkunut()
{
	return _onkoMustaKuningasLiikkunut;
}

bool Asema::getOnkoValkeaDTliikkunut()
{
	return _onkoValkeaDTliikkunut;
}

bool Asema::getOnkoValkeaKTliikkunut()
{
	return _onkoValkeaKTliikkunut;
}

bool Asema::getOnkoMustaDTliikkunut()
{
	return _onkoMustaDTliikkunut;
}

bool Asema::getOnkoMustaKTliikkunut()
{
	return _onkoMustaKTliikkunut;
}
