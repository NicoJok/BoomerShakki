#include "asema.h"
#include "nappula.h"   


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

	// Ohestalyönti: poista lyöty sotilas (sama rivi kuin lähtöruutu, sama sarake kuin kohderuutu)
	if (siirto->onkoOhestalyonti()) {
		_lauta[alkuRivi][loppuSarake] = nullptr;
	}
	// Korotus: käytä valittua nappulaa
	Nappula* siirrettava = (siirto->_miksikorotetaan != nullptr) ? siirto->_miksikorotetaan : nappula;
	_lauta[alkuRivi][alkuSarake] = nullptr;
	_lauta[loppuRivi][loppuSarake] = siirrettava;

	// En passant -kohde: kaksoisaskel
	_epKohdeRivi = -1;
	_epKohdeSarake = -1;
	if (nappulaKoodi == VS && alkuRivi == 6 && loppuRivi == 4) {
		_epKohdeRivi = 5;
		_epKohdeSarake = loppuSarake;
	}
	else if (nappulaKoodi == MS && alkuRivi == 1 && loppuRivi == 3) {
		_epKohdeRivi = 2;
		_epKohdeSarake = loppuSarake;
	}

	// Vaihdetaan siirtovuoro
	_siirtovuoro = 1 - _siirtovuoro;
}

Nappula* Asema::getNappula(int rivi, int sarake)
{
	if (rivi < 0 || rivi >= 8 || sarake < 0 || sarake >= 8) return nullptr;
	return _lauta[rivi][sarake];
}

void Asema::annaPseudoLaillisetSiirrot(std::list<Siirto>& lista)
{
	lista.clear();
	int vari = getSiirtovuoro();
	for (int rivi = 0; rivi < 8; ++rivi) {
		for (int sarake = 0; sarake < 8; ++sarake) {
			Nappula* n = getNappula(rivi, sarake);
			if (n == nullptr) continue;
			if (n->getVari() != vari) continue;
			Ruutu ruutu(sarake, rivi);
			n->annaSiirrot(lista, &ruutu, this, vari);
		}
	}
	// Linnoitus: lisää kun sallittu (tarkista että reitti ja kohde eivät ole vastustajan uhan alla)
	int vastustajanVari = 1 - vari;
	if (vari == 0) {
		if (!_onkoValkeaKuningasLiikkunut && !onkoRuutuUhattuVarilla(7, 4, vastustajanVari)) {
			if (!_onkoValkeaKTliikkunut && getNappula(7, 5) == nullptr && getNappula(7, 6) == nullptr
				&& !onkoRuutuUhattuVarilla(7, 5, vastustajanVari) && !onkoRuutuUhattuVarilla(7, 6, vastustajanVari))
				lista.push_back(Siirto(true, false));
			if (!_onkoValkeaDTliikkunut && getNappula(7, 1) == nullptr && getNappula(7, 2) == nullptr && getNappula(7, 3) == nullptr
				&& !onkoRuutuUhattuVarilla(7, 3, vastustajanVari) && !onkoRuutuUhattuVarilla(7, 2, vastustajanVari))
				lista.push_back(Siirto(false, true));
		}
	}
	else {
		if (!_onkoMustaKuningasLiikkunut && !onkoRuutuUhattuVarilla(0, 4, vastustajanVari)) {
			if (!_onkoMustaKTliikkunut && getNappula(0, 5) == nullptr && getNappula(0, 6) == nullptr
				&& !onkoRuutuUhattuVarilla(0, 5, vastustajanVari) && !onkoRuutuUhattuVarilla(0, 6, vastustajanVari))
				lista.push_back(Siirto(true, false));
			if (!_onkoMustaDTliikkunut && getNappula(0, 1) == nullptr && getNappula(0, 2) == nullptr && getNappula(0, 3) == nullptr
				&& !onkoRuutuUhattuVarilla(0, 3, vastustajanVari) && !onkoRuutuUhattuVarilla(0, 2, vastustajanVari))
				lista.push_back(Siirto(false, true));
		}
	}
}

bool Asema::onkoRuutuUhattu(int rivi, int sarake)
{
	return onkoRuutuUhattuVarilla(rivi, sarake, getSiirtovuoro());
}

bool Asema::onkoRuutuUhattuVarilla(int rivi, int sarake, int uhkaavaVari)
{
	std::list<Siirto> siirrot;
	for (int r = 0; r < 8; ++r) {
		for (int c = 0; c < 8; ++c) {
			Nappula* n = getNappula(r, c);
			if (n == nullptr || n->getVari() != uhkaavaVari) continue;
			Ruutu ruutu(c, r);
			n->annaSiirrot(siirrot, &ruutu, this, uhkaavaVari);
		}
	}
	for (Siirto s : siirrot) {
		Ruutu loppu = s.getLoppuruutu();
		if (loppu.getRivi() == rivi && loppu.getSarake() == sarake)
			return true;
	}
	return false;
}

void Asema::teeSiirto(Siirto s)
{
	_viimeisinSiirto = s;
	_edellinenSiirtoLinna = s.onkoLyhytLinna() || s.onkoPitkalinna();
	_edellinenSiirtoEnPassant = s.onkoOhestalyonti();
	_viimValkeaKuningas = _onkoValkeaKuningasLiikkunut;
	_viimValkeaDT = _onkoValkeaDTliikkunut;
	_viimValkeaKT = _onkoValkeaKTliikkunut;
	_viimMustaKuningas = _onkoMustaKuningasLiikkunut;
	_viimMustaDT = _onkoMustaDTliikkunut;
	_viimMustaKT = _onkoMustaKTliikkunut;
	_viimEpRivi = _epKohdeRivi;
	_viimEpSarake = _epKohdeSarake;
	_epKohdeRivi = -1;
	_epKohdeSarake = -1;
	_viimeisinSyotyNappula = nullptr;
	_viimeisinSyotyRivi = -1;
	_viimeisinSyotySarake = -1;
	_viimeisinSiirrettyNappula = nullptr;

	if (s.onkoLyhytLinna()) {
		if (_siirtovuoro == 0) {
			_lauta[7][4] = nullptr;
			_lauta[7][7] = nullptr;
			_lauta[7][6] = vk;
			_lauta[7][5] = vt;
			_onkoValkeaKuningasLiikkunut = true;
			_onkoValkeaKTliikkunut = true;
		}
		else {
			_lauta[0][4] = nullptr;
			_lauta[0][7] = nullptr;
			_lauta[0][6] = mk;
			_lauta[0][5] = mt;
			_onkoMustaKuningasLiikkunut = true;
			_onkoMustaKTliikkunut = true;
		}
		_siirtovuoro = 1 - _siirtovuoro;
		return;
	}
	if (s.onkoPitkalinna()) {
		if (_siirtovuoro == 0) {
			_lauta[7][4] = nullptr;
			_lauta[7][0] = nullptr;
			_lauta[7][2] = vk;
			_lauta[7][3] = vt;
			_onkoValkeaKuningasLiikkunut = true;
			_onkoValkeaDTliikkunut = true;
		}
		else {
			_lauta[0][4] = nullptr;
			_lauta[0][0] = nullptr;
			_lauta[0][2] = mk;
			_lauta[0][3] = mt;
			_onkoMustaKuningasLiikkunut = true;
			_onkoMustaDTliikkunut = true;
		}
		_siirtovuoro = 1 - _siirtovuoro;
		return;
	}

	Ruutu alku = s.getAlkuruutu();
	Ruutu loppu = s.getLoppuruutu();
	int ar = alku.getRivi(), ac = alku.getSarake();
	int lr = loppu.getRivi(), lc = loppu.getSarake();
	Nappula* nappula = _lauta[ar][ac];
	if (!nappula) { _siirtovuoro = 1 - _siirtovuoro; return; }
	_viimeisinSiirrettyNappula = nappula;

	if (s.onkoOhestalyonti()) {
		_viimeisinSyotyNappula = _lauta[lr + (_siirtovuoro == 0 ? 1 : -1)][lc];
		_viimeisinSyotyRivi = lr + (_siirtovuoro == 0 ? 1 : -1);
		_viimeisinSyotySarake = lc;
		_lauta[_viimeisinSyotyRivi][_viimeisinSyotySarake] = nullptr;
	}
	else if (_lauta[lr][lc] != nullptr) {
		_viimeisinSyotyNappula = _lauta[lr][lc];
		_viimeisinSyotyRivi = lr;
		_viimeisinSyotySarake = lc;
	}

	Nappula* siirrettava = nappula;
	if (s._miksikorotetaan != nullptr)
		siirrettava = s._miksikorotetaan;

	_lauta[ar][ac] = nullptr;
	_lauta[lr][lc] = siirrettava;

	int koodi = nappula->getKoodi();
	if (koodi == VK) _onkoValkeaKuningasLiikkunut = true;
	else if (koodi == MK) _onkoMustaKuningasLiikkunut = true;
	else if (koodi == VT) {
		if (ar == 7 && ac == 0) _onkoValkeaDTliikkunut = true;
		else if (ar == 7 && ac == 7) _onkoValkeaKTliikkunut = true;
	}
	else if (koodi == MT) {
		if (ar == 0 && ac == 0) _onkoMustaDTliikkunut = true;
		else if (ar == 0 && ac == 7) _onkoMustaKTliikkunut = true;
	}

	if (koodi == VS || koodi == MS) {
		if (ar == 6 && lr == 4) { _epKohdeRivi = 5; _epKohdeSarake = lc; }
		else if (ar == 1 && lr == 3) { _epKohdeRivi = 2; _epKohdeSarake = lc; }
	}

	_siirtovuoro = 1 - _siirtovuoro;
}

void Asema::peruSiirto()
{
	Siirto& s = _viimeisinSiirto;
	_siirtovuoro = 1 - _siirtovuoro;
	_onkoValkeaKuningasLiikkunut = _viimValkeaKuningas;
	_onkoValkeaDTliikkunut = _viimValkeaDT;
	_onkoValkeaKTliikkunut = _viimValkeaKT;
	_onkoMustaKuningasLiikkunut = _viimMustaKuningas;
	_onkoMustaDTliikkunut = _viimMustaDT;
	_onkoMustaKTliikkunut = _viimMustaKT;
	_epKohdeRivi = _viimEpRivi;
	_epKohdeSarake = _viimEpSarake;

	if (s.onkoLyhytLinna()) {
		if (_siirtovuoro == 0) {
			_lauta[7][6] = nullptr;
			_lauta[7][5] = nullptr;
			_lauta[7][4] = vk;
			_lauta[7][7] = vt;
		}
		else {
			_lauta[0][6] = nullptr;
			_lauta[0][5] = nullptr;
			_lauta[0][4] = mk;
			_lauta[0][7] = mt;
		}
		return;
	}
	if (s.onkoPitkalinna()) {
		if (_siirtovuoro == 0) {
			_lauta[7][2] = nullptr;
			_lauta[7][3] = nullptr;
			_lauta[7][4] = vk;
			_lauta[7][0] = vt;
		}
		else {
			_lauta[0][2] = nullptr;
			_lauta[0][3] = nullptr;
			_lauta[0][4] = mk;
			_lauta[0][0] = mt;
		}
		return;
	}

	Ruutu alku = s.getAlkuruutu();
	Ruutu loppu = s.getLoppuruutu();
	int ar = alku.getRivi(), ac = alku.getSarake();
	int lr = loppu.getRivi(), lc = loppu.getSarake();
	Nappula* nappula = _viimeisinSiirrettyNappula ? _viimeisinSiirrettyNappula : _lauta[lr][lc];
	_lauta[ar][ac] = nappula;
	if (_edellinenSiirtoEnPassant) {
		_lauta[lr][lc] = nullptr;
		_lauta[_viimeisinSyotyRivi][_viimeisinSyotySarake] = _viimeisinSyotyNappula;
	}
	else
		_lauta[lr][lc] = _viimeisinSyotyNappula;
}

void Asema::annaLaillisetSiirrot(std::list<Siirto>& lista)
{
	annaPseudoLaillisetSiirrot(lista);
	std::list<Siirto> lailliset;
	for (Siirto s : lista) {
		teeSiirto(s);
		int kuningasVari = 1 - getSiirtovuoro();
		int kr = -1, kc = -1;
		for (int r = 0; r < 8 && kr < 0; ++r)
			for (int c = 0; c < 8; ++c) {
				Nappula* n = getNappula(r, c);
				if (n && ((kuningasVari == 0 && n->getKoodi() == VK) || (kuningasVari == 1 && n->getKoodi() == MK))) {
					kr = r; kc = c; break;
				}
			}
		bool shakissa = (kr >= 0 && onkoRuutuUhattu(kr, kc));
		peruSiirto();
		if (!shakissa)
			lailliset.push_back(s);
	}
	lista = lailliset;
}

bool Asema::onkoSiirtoLaillinen(const Siirto& s)
{
	std::list<Siirto> lailliset;
	annaLaillisetSiirrot(lailliset);
	for (const Siirto& m : lailliset) {
		if (m.samaKuin(s))
			return true;
	}
	return false;
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
