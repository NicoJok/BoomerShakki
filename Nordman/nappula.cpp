#include <list>
#include <string>
#include "asema.h"
#include "nappula.h"
using namespace std;


// Apufunktio: liiku suuntaan (dr, dc) kunnes reuna tai oma nappula (ei lis?t?) tai vastustaja (lis?t??n ja lopetetaan)
static void lisaLiukuvatSiirrot(std::list<Siirto>& lista, Ruutu* ruutu, Asema* asema, int vari,
	int dr, int dc)
{
	int r = ruutu->getRivi();
	int c = ruutu->getSarake();
	Ruutu alku(c, r);
	for (int k = 1; ; ++k) {
		int nr = r + k * dr;
		int nc = c + k * dc;
		if (nr < 0 || nr >= 8 || nc < 0 || nc >= 8) break;
		Nappula* kohde = asema->getNappula(nr, nc);
		if (kohde == nullptr) {
			lista.push_back(Siirto(alku, Ruutu(nc, nr)));
		}
		else {
			if (kohde->getVari() != vari)
				lista.push_back(Siirto(alku, Ruutu(nc, nr)));
			break;
		}
	}
}

void Torni::annaSiirrot(std::list<Siirto>& lista, Ruutu* ruutu, Asema* asema, int vari)
{
	lisaLiukuvatSiirrot(lista, ruutu, asema, vari, 0, 1);
	lisaLiukuvatSiirrot(lista, ruutu, asema, vari, 0, -1);
	lisaLiukuvatSiirrot(lista, ruutu, asema, vari, 1, 0);
	lisaLiukuvatSiirrot(lista, ruutu, asema, vari, -1, 0);
}

void Lahetti::annaSiirrot(std::list<Siirto>& lista, Ruutu* ruutu, Asema* asema, int vari)
{
	lisaLiukuvatSiirrot(lista, ruutu, asema, vari, 1, 1);
	lisaLiukuvatSiirrot(lista, ruutu, asema, vari, 1, -1);
	lisaLiukuvatSiirrot(lista, ruutu, asema, vari, -1, 1);
	lisaLiukuvatSiirrot(lista, ruutu, asema, vari, -1, -1);
}

void Ratsu::annaSiirrot(std::list<Siirto>& lista, Ruutu* ruutu, Asema* asema, int vari)
{
	int r = ruutu->getRivi();
	int c = ruutu->getSarake();
	Ruutu alku(c, r);
	static const int dr[] = { 2, 2, -2, -2, 1, 1, -1, -1 };
	static const int dc[] = { 1, -1, 1, -1, 2, -2, 2, -2 };
	for (int i = 0; i < 8; ++i) {
		int nr = r + dr[i];
		int nc = c + dc[i];
		if (nr < 0 || nr >= 8 || nc < 0 || nc >= 8) continue;
		Nappula* kohde = asema->getNappula(nr, nc);
		if (kohde != nullptr && kohde->getVari() == vari) continue; // oma nappula
		lista.push_back(Siirto(alku, Ruutu(nc, nr)));
	}
}

void Daami::annaSiirrot(std::list<Siirto>& lista, Ruutu* ruutu, Asema* asema, int vari)
{
	lisaLiukuvatSiirrot(lista, ruutu, asema, vari, 0, 1);
	lisaLiukuvatSiirrot(lista, ruutu, asema, vari, 0, -1);
	lisaLiukuvatSiirrot(lista, ruutu, asema, vari, 1, 0);
	lisaLiukuvatSiirrot(lista, ruutu, asema, vari, -1, 0);
	lisaLiukuvatSiirrot(lista, ruutu, asema, vari, 1, 1);
	lisaLiukuvatSiirrot(lista, ruutu, asema, vari, 1, -1);
	lisaLiukuvatSiirrot(lista, ruutu, asema, vari, -1, 1);
	lisaLiukuvatSiirrot(lista, ruutu, asema, vari, -1, -1);
}

void Kuningas::annaSiirrot(std::list<Siirto>& lista, Ruutu* ruutu, Asema* asema, int vari)
{
	int r = ruutu->getRivi();
	int c = ruutu->getSarake();
	Ruutu alku(c, r);
	for (int dr = -1; dr <= 1; ++dr) {
		for (int dc = -1; dc <= 1; ++dc) {
			if (dr == 0 && dc == 0) continue;
			int nr = r + dr;
			int nc = c + dc;
			if (nr < 0 || nr >= 8 || nc < 0 || nc >= 8) continue;
			Nappula* kohde = asema->getNappula(nr, nc);
			if (kohde != nullptr && kohde->getVari() == vari) continue;
			lista.push_back(Siirto(alku, Ruutu(nc, nr)));
		}
	}
}

static void lisaSotilasSiirto(std::list<Siirto>& lista, const Ruutu& alku, int lc, int lr, int vari)
{
	if ((vari == 0 && lr == 0) || (vari == 1 && lr == 7)) {
		Nappula* korotteet[] = { vari == 0 ? (Nappula*)Asema::vd : (Nappula*)Asema::md,
			vari == 0 ? (Nappula*)Asema::vt : (Nappula*)Asema::mt,
			vari == 0 ? (Nappula*)Asema::vl : (Nappula*)Asema::ml,
			vari == 0 ? (Nappula*)Asema::vr : (Nappula*)Asema::mr };
		for (int i = 0; i < 4; ++i) {
			Siirto prom(alku, Ruutu(lc, lr));
			prom._miksikorotetaan = korotteet[i];
			lista.push_back(prom);
		}
	}
	else
		lista.push_back(Siirto(alku, Ruutu(lc, lr)));
}

void Sotilas::annaSiirrot(std::list<Siirto>& lista, Ruutu* ruutu, Asema* asema, int vari)
{
	int r = ruutu->getRivi();
	int c = ruutu->getSarake();
	Ruutu alku(c, r);
	if (vari == 0) {
		// Valkea: liiku "yl?s" (r pienenee)
		if (r > 0 && asema->getNappula(r - 1, c) == nullptr) {
			lisaSotilasSiirto(lista, alku, c, r - 1, vari);
			if (r == 6 && asema->getNappula(r - 2, c) == nullptr)
				lista.push_back(Siirto(alku, Ruutu(c, r - 2)));
		}
		// Sy?nn?t
		if (r > 0 && c > 0) {
			Nappula* kohde = asema->getNappula(r - 1, c - 1);
			if (kohde != nullptr && kohde->getVari() == 1)
				lisaSotilasSiirto(lista, alku, c - 1, r - 1, vari);
		}
		if (r > 0 && c < 7) {
			Nappula* kohde = asema->getNappula(r - 1, c + 1);
			if (kohde != nullptr && kohde->getVari() == 1)
				lisaSotilasSiirto(lista, alku, c + 1, r - 1, vari);
		}
		// Ohestalyönti: valkea rank 5 (r=3), EP-kohde on rank 6 (rivi 2) kun musta juuri e7-e5
		if (r == 3 && asema->getEpTargetRivi() == 2) {
			if (asema->getEpTargetSarake() == c - 1) {
				Siirto ep(alku, Ruutu(c - 1, 2));
				ep.setOhestalyonti(true);
				lista.push_back(ep);
			}
			if (asema->getEpTargetSarake() == c + 1) {
				Siirto ep(alku, Ruutu(c + 1, 2));
				ep.setOhestalyonti(true);
				lista.push_back(ep);
			}
		}
	}
	else {
		// Musta: liiku "alas" (r kasvaa)
		if (r < 7 && asema->getNappula(r + 1, c) == nullptr) {
			lisaSotilasSiirto(lista, alku, c, r + 1, vari);
			if (r == 1 && asema->getNappula(r + 2, c) == nullptr)
				lista.push_back(Siirto(alku, Ruutu(c, r + 2)));
		}
		if (r < 7 && c > 0) {
			Nappula* kohde = asema->getNappula(r + 1, c - 1);
			if (kohde != nullptr && kohde->getVari() == 0)
				lisaSotilasSiirto(lista, alku, c - 1, r + 1, vari);
		}
		if (r < 7 && c < 7) {
			Nappula* kohde = asema->getNappula(r + 1, c + 1);
			if (kohde != nullptr && kohde->getVari() == 0)
				lisaSotilasSiirto(lista, alku, c + 1, r + 1, vari);
		}
		if (r == 4 && asema->getEpTargetRivi() == 5) {
			if (asema->getEpTargetSarake() == c - 1) {
				Siirto ep(alku, Ruutu(c - 1, 5));
				ep.setOhestalyonti(true);
				lista.push_back(ep);
			}
			if (asema->getEpTargetSarake() == c + 1) {
				Siirto ep(alku, Ruutu(c + 1, 5));
				ep.setOhestalyonti(true);
				lista.push_back(ep);
			}
		}
	}
}

void Sotilas::lisaaSotilaanKorotukset(Siirto* siirto, std::list<Siirto>& lista, Asema* asema) {
	// Korotukset: my?hemmin lis?t??n daami/torni/l?hetti/ratsu-vaihtoehdot
	// T?ss? vaiheessa pseudo-lailliset siirrot eiv?t viel? merkitse korotusta.
}
