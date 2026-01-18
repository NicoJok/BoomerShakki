#ifndef NAPPULA_H
#define NAPPULA_H

#include <string>

enum
{
    VT, VR, VL, VD, VK, VS,
    MT, MR, ML, MD, MK, MS
};

class Nappula {
private:
    std::wstring unicode;
    int vari;
    int _koodi;

public:
    Nappula(std::wstring u, int v, int k) : unicode(u), vari(v), _koodi(k) {}
    Nappula() : unicode(L" "), vari(0), _koodi(0) {}
    
    void setKoodi(int k) { _koodi = k; }
    int getKoodi() { return _koodi; }
    
    void setUnicode(std::wstring u) { unicode = u; }
    std::wstring getUnicode() { return unicode; }
    
    void setVari(int v) { vari = v; }
    int getVari() { return vari; }
};

#endif