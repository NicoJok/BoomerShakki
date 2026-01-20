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
    int _nimi;

public:
    Nappula(std::wstring u, int v, int n) : unicode(u), vari(v), _nimi(n) {}
    Nappula() : unicode(L" "), vari(0), _nimi(0) {}
    
    void setNimi(int n) { _nimi = n; }
    int getNimi() { return _nimi; }
    
    void setUnicode(std::wstring u) { unicode = u; }
    std::wstring getUnicode() { return unicode; }
    
    void setVari(int v) { vari = v; }
    int getVari() { return vari; }
};

#endif