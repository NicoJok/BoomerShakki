#include "nappula.h"

Nappula::Nappula(std::wstring unicode, int vari, int koodi) {
	this->unicode = unicode;
	this->vari = vari;
	this->_koodi = koodi;
}

void Nappula::setKoodi(int k) { this->_koodi = k; }
int Nappula::getKoodi() { return this->_koodi; }
void Nappula::setUnicode(std::wstring u) { this->unicode = u; }
std::wstring Nappula::getUnicode() { return this->unicode; }
void Nappula::setVari(int v) { this->vari = v; }
int Nappula::getVari() { return this->vari; }

