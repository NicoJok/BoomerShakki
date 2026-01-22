#ifndef NAPPULA_H
#define NAPPULA_H

#include <string>

enum
{
    VT,
    VR,
    VL,
    VD,
    VK,
    VS,
    MT,
    MR,
    ML,
    MD,
    MK,
    MS
};

class Nappula
{
private:
    std::wstring unicode;
    int vari;
    int _nimi;

public:
    Nappula(std::wstring u, int v, int n);
    Nappula();

    void setNimi(int n);
    int getNimi();

    void setUnicode(std::wstring u);
    std::wstring getUnicode();

    void setVari(int v);
    int getVari();
};

#endif