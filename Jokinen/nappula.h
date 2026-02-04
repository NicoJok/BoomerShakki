#ifndef NAPPULA_H
#define NAPPULA_H

#include <string>
#include <list>
#include "ruutu.h"
#include "siirto.h"

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
class Asema;

class Nappula
{
private:
    std::wstring unicode;
    int vari;
    int _nimi;

public:
    Nappula(std::wstring u, int v, int n);
    Nappula();

    virtual ~Nappula() = default;
    virtual void annaSiirrot(std::list<Siirto> &lista, Ruutu *r, class Asema *a, int vari) = 0;

    void setNimi(int n);
    int getNimi();

    void setUnicode(std::wstring u);
    std::wstring getUnicode();

    void setVari(int v);
    int getVari();

};
class Torni : public Nappula
{
public:
    Torni(std::wstring u, int v, int n) : Nappula(u, v, n) {}
    void annaSiirrot(std::list<Siirto> &lista, Ruutu *r, class Asema *a, int vari);
};
class Daami : public Nappula
{
public:
    Daami(std::wstring u, int v, int n) : Nappula(u, v, n) {}
    void annaSiirrot(std::list<Siirto> &lista, Ruutu *r, class Asema *a, int vari);
};
class Kuningas : public Nappula
{
public:
    Kuningas(std::wstring u, int v, int n) : Nappula(u, v, n) {}
    void annaSiirrot(std::list<Siirto> &lista, Ruutu *r, class Asema *a, int vari);
};
class Lahetti : public Nappula
{
public:
    Lahetti(std::wstring u, int v, int n) : Nappula(u, v, n) {}
    void annaSiirrot(std::list<Siirto> &lista, Ruutu *r, class Asema *a, int vari);
};
class Ratsu : public Nappula
{
public:
    Ratsu(std::wstring u, int v, int n) : Nappula(u, v, n) {}
    void annaSiirrot(std::list<Siirto> &lista, Ruutu *r, class Asema *a, int vari);
};
class Sotilas : public Nappula
{
public:
    Sotilas(std::wstring u, int v, int n) : Nappula(u, v, n) {}
    void annaSiirrot(std::list<Siirto> &lista, Ruutu *r, class Asema *a, int vari);
};


#endif