#include "nappula.h"

Nappula::Nappula(std::wstring u, int v, int n) : unicode(u), vari(v), _nimi(n) {}
Nappula::Nappula() : unicode(L" "), vari(0), _nimi(0) {}

void Nappula::setNimi(int n) { _nimi = n; }
int Nappula::getNimi() { return _nimi; }

void Nappula::setUnicode(std::wstring u) { unicode = u; }
std::wstring Nappula::getUnicode() { return unicode; }

void Nappula::setVari(int v) { vari = v; }
int Nappula::getVari() { return vari; }