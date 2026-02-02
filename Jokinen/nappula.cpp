#include "asema.h"
#include "nappula.h"

Nappula::Nappula(std::wstring u, int v, int n) : unicode(u), vari(v), _nimi(n) {}
Nappula::Nappula() : unicode(L" "), vari(0), _nimi(0) {}

void Nappula::setNimi(int n) { _nimi = n; }
int Nappula::getNimi() { return _nimi; }

void Nappula::setUnicode(std::wstring u) { unicode = u; }
std::wstring Nappula::getUnicode() { return unicode; }

void Nappula::setVari(int v) { vari = v; }
int Nappula::getVari() { return vari; }

void Torni::annaSiirrot(std::list<Siirto> &lista, Ruutu *r, Asema *a, int vari)
{
    int alkuRivi = r->getRivi();
    int alkupRivi = r->getpRivi();
    
    int suunta[4][2] = {
        {1, 0},
        {-1, 0}, 
        {0, 1},
        {0, -1}
    };

    for (int i = 0; i < 4; i++) {
        int dr = suunta[i][0];
        int dp = suunta[i][1];
        int uusiRivi = alkuRivi + dr;
        int uuspRivi = alkupRivi + dp;

        while (uusiRivi >= 0 && uusiRivi < 8 && uuspRivi >= 0 && uuspRivi < 8) {
            Nappula *kohde = a->lauta[uusiRivi][uuspRivi];
            if (kohde == nullptr) {
                lista.push_back(Siirto(Ruutu(alkuRivi, alkupRivi), Ruutu(uusiRivi, uuspRivi)));
            } else {
                if (kohde->getVari() != vari) {
                    lista.push_back(Siirto(Ruutu(alkuRivi, alkupRivi), Ruutu(uusiRivi, uuspRivi)));
                }
                break;
            }
            uusiRivi += dr;
            uuspRivi += dp;
        }
    }
}

void Daami::annaSiirrot(std::list<Siirto> &lista, Ruutu *r, Asema *a, int vari)
{
    int alkuRivi = r->getRivi();
    int alkupRivi = r->getpRivi();

    int suunta[8][2] = {
        {1, 0},     {-1, 0},
        {0, 1},     {0, -1},
        {1, 1},     {1, -1},
        {-1, 1},    {-1, -1}
    };

    for (int i = 0; i < 8; i++) {
        int dr = suunta[i][0];
        int dp = suunta[i][1];
        int uusiRivi = alkuRivi + dr;
        int uuspRivi = alkupRivi + dp;

        while (uusiRivi >= 0 && uusiRivi < 8 && uuspRivi >= 0 && uuspRivi < 8) {
            Nappula *kohde = a->lauta[uusiRivi][uuspRivi];
            if (kohde == nullptr) {
                lista.push_back(Siirto(Ruutu(alkuRivi, alkupRivi), Ruutu(uusiRivi, uuspRivi)));
            } else {
                if (kohde->getVari() != vari) {
                    lista.push_back(Siirto(Ruutu(alkuRivi, alkupRivi), Ruutu(uusiRivi, uuspRivi)));
                }
                break;
            }
            uusiRivi += dr;
            uuspRivi += dp;
        }
    }
}

void Kuningas::annaSiirrot(std::list<Siirto> &lista, Ruutu *r, Asema *a, int vari)
{
    int alkuRivi = r->getRivi();
    int alkupRivi = r->getpRivi();

    int suunta[8][2] = {
        {1, 0},     {-1, 0},
        {0, 1},     {0, -1},
        {1, 1},     {1, -1},
        {-1, 1},    {-1, -1}
    };

    for (int i = 0; i < 8; i++) {
        int dr = suunta[i][0];
        int dp = suunta[i][1];
        int uusiRivi = alkuRivi + dr;
        int uuspRivi = alkupRivi + dp;

        if (uusiRivi >= 0 && uusiRivi < 8 && uuspRivi >= 0 && uuspRivi < 8) {
            Nappula *kohde = a->lauta[uusiRivi][uuspRivi];
            if (kohde == nullptr || kohde->getVari() != vari) {
                lista.push_back(Siirto(Ruutu(alkuRivi, alkupRivi), Ruutu(uusiRivi, uuspRivi)));
            }
        }
    }

    if (vari == 0) {
        if (!a->getVKLiikkunut()) {
            if (!a->getVKTLiikkunut() && 
                a->lauta[7][5] == nullptr && 
                a->lauta[7][6] == nullptr) {
                lista.push_back(Siirto(true, false));
            }
            if (!a->getVDTLiikkunut() && 
                a->lauta[7][1] == nullptr && 
                a->lauta[7][2] == nullptr && 
                a->lauta[7][3] == nullptr) {
                lista.push_back(Siirto(false, true));
            }
        }
    } else {
        if (!a->getMKLiikkunut()) {
            if (!a->getMKTLiikkunut() && 
                a->lauta[0][5] == nullptr && 
                a->lauta[0][6] == nullptr) {
                lista.push_back(Siirto(true, false));
            }
            if (!a->getMDTLiikkunut() && 
                a->lauta[0][1] == nullptr && 
                a->lauta[0][2] == nullptr && 
                a->lauta[0][3] == nullptr) {
                lista.push_back(Siirto(false, true));
            }
        }
    }
}

void Lahetti::annaSiirrot(std::list<Siirto> &lista, Ruutu *r, Asema *a, int vari)
{
    int alkuRivi = r->getRivi();
    int alkupRivi = r->getpRivi();

    int suunta[4][2] = {
        {1, 1},
        {1, -1},
        {-1, 1},
        {-1, -1}
    };

    for (int i = 0; i < 4; i++) {
        int dr = suunta[i][0];
        int dp = suunta[i][1];
        int uusiRivi = alkuRivi + dr;
        int uuspRivi = alkupRivi + dp;

        while (uusiRivi >= 0 && uusiRivi < 8 && uuspRivi >= 0 && uuspRivi < 8) {
            Nappula *kohde = a->lauta[uusiRivi][uuspRivi];
            if (kohde == nullptr) {
                lista.push_back(Siirto(Ruutu(alkuRivi, alkupRivi), Ruutu(uusiRivi, uuspRivi)));
            } else {
                if (kohde->getVari() != vari) {
                    lista.push_back(Siirto(Ruutu(alkuRivi, alkupRivi), Ruutu(uusiRivi, uuspRivi)));
                }
                break;
            }
            uusiRivi += dr;
            uuspRivi += dp;
        }
    }
}

void Ratsu::annaSiirrot(std::list<Siirto> &lista, Ruutu *r, Asema *a, int vari)
{
    int alkuRivi = r->getRivi();
    int alkupRivi = r->getpRivi();

    int suunta[8][2] = {
        {-2, -1},   {-2, 1},
        {2, -1},    {2, 1},
        {1, -2},    {1, 2},
        {-1, -2},    {-1, 2}
    };

    for (int i = 0; i < 8; i++) {
        int dr = suunta[i][0];
        int dp = suunta[i][1];
        int uusiRivi = alkuRivi + dr;
        int uuspRivi = alkupRivi + dp;

        if (uusiRivi >= 0 && uusiRivi < 8 && uuspRivi >= 0 && uuspRivi < 8) {
            Nappula *kohde = a->lauta[uusiRivi][uuspRivi];
            if (kohde == nullptr || kohde->getVari() != vari) {
                lista.push_back(Siirto(Ruutu(alkuRivi, alkupRivi), Ruutu(uusiRivi, uuspRivi)));
            }
        }
    }
}

void Sotilas::annaSiirrot(std::list<Siirto> &lista, Ruutu *r, Asema *a, int vari)
{
    int alkuRivi = r->getRivi();
    int alkupRivi = r->getpRivi();
    int suunta = (vari == 0) ? -1 : 1;

    int uusiRivi = alkuRivi + suunta;
    if (uusiRivi >= 0 && uusiRivi < 8) {
        if (a->lauta[uusiRivi][alkupRivi] == nullptr) {
            lista.push_back(Siirto(Ruutu(alkuRivi, alkupRivi), Ruutu(uusiRivi, alkupRivi)));

            if ((vari == 0 && alkuRivi == 6) || (vari == 1 && alkuRivi == 1)) {
                int kaksiaskeltaRivi = alkuRivi + 2 * suunta;
                if (a->lauta[kaksiaskeltaRivi][alkupRivi] == nullptr) {
                    lista.push_back(Siirto(Ruutu(alkuRivi, alkupRivi), Ruutu(kaksiaskeltaRivi, alkupRivi)));
                }
            }
        }

        for (int dp = -1; dp <= 1; dp += 2) {
            int uuspRivi = alkupRivi + dp;
            if (uuspRivi >= 0 && uuspRivi < 8) {
                Nappula *kohde = a->lauta[uusiRivi][uuspRivi];
                if (kohde != nullptr && kohde->getVari() != vari) {
                    lista.push_back(Siirto(Ruutu(alkuRivi, alkupRivi), Ruutu(uusiRivi, uuspRivi)));
                } // Enpassant joskus perkele
            }
        }
    }   

}


