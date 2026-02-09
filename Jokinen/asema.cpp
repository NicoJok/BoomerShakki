#include "asema.h"

Asema::Asema()
{

    for (int rivi = 0; rivi < 8; rivi++)
    {
        for (int pRivi = 0; pRivi < 8; pRivi++)
        {
            lauta[rivi][pRivi] = nullptr;
        }
    }

    lauta[7][0] = new Torni(L"\u2656", 0, VT);
    lauta[7][1] = new Ratsu(L"\u2658", 0, VR);
    lauta[7][2] = new Lahetti(L"\u2657", 0, VL);
    lauta[7][3] = new Daami(L"\u2655", 0, VD);
    lauta[7][4] = new Kuningas(L"\u2654", 0, VK);
    lauta[7][5] = new Lahetti(L"\u2657", 0, VL);
    lauta[7][6] = new Ratsu(L"\u2658", 0, VR);
    lauta[7][7] = new Torni(L"\u2656", 0, VT);


    for (int i = 0; i < 8; i++)
        lauta[6][i] = new Sotilas(L"\u265F", 0, MS);

    lauta[0][0] = new Torni(L"\u265C", 1, MT);
    lauta[0][1] = new Ratsu(L"\u265E", 1, MR);
    lauta[0][2] = new Lahetti(L"\u265D", 1, ML);
    lauta[0][3] = new Daami(L"\u265B", 1, MD);
    lauta[0][4] = new Kuningas(L"\u265A", 1, MK);
    lauta[0][5] = new Lahetti(L"\u265D", 1, ML);
    lauta[0][6] = new Ratsu(L"\u265E", 1, MR);
    lauta[0][7] = new Torni(L"\u265C", 1, MT);

    for (int i = 0; i < 8; i++)
        lauta[1][i] = new Sotilas(L"\u265F", 1, MS);

    siirtovuoro = 0;
    VKliikkunut = false;
    MKliikkunut = false;
    VDTliikkunut = false;
    MDTliikkunut = false;
    VKTliikkunut = false;
    MKTliikkunut = false;
}

void Asema::paivitaAsema(Siirto *siirto)
{
    if (siirto->LyhytLinna()) {
        if (siirtovuoro == 0) {
            lauta[7][6] = lauta[7][4]; 
            lauta[7][5] = lauta[7][7];
            lauta[7][4] = nullptr;
            lauta[7][7] = nullptr;
            VKliikkunut = true;
            VKTliikkunut = true;

        } else {
            lauta[0][6] = lauta[0][4];
            lauta[0][5] = lauta[0][7];
            lauta[0][4] = nullptr;
            lauta[0][7] = nullptr;
            MKliikkunut = true;
            MKTliikkunut = true;
        }
            if (siirtovuoro == 0) {
                siirtovuoro = 1;
            } 
            else {
                siirtovuoro = 0;
            }
        return;
    }

    if (siirto->PitkaLinna()) {
        if (siirtovuoro == 0) {
            lauta[7][2] = lauta[7][4];
            lauta[7][3] = lauta[7][0];
            lauta[7][4] = nullptr;
            lauta[7][0] = nullptr;
            VKliikkunut = true;
            VDTliikkunut = true;

        } else { 
            lauta[0][2] = lauta[0][4];
            lauta[0][3] = lauta[0][0];
            lauta[0][4] = nullptr;
            lauta[0][0] = nullptr;
            MKliikkunut = true;
            MDTliikkunut = true;
        }
            if (siirtovuoro == 0) {
                siirtovuoro = 1;
            } 
            else {
                siirtovuoro = 0;
            }
            return;
    }

    int mistaRivi = siirto->getAlkuruutu().getRivi();
    int mistapRivi = siirto->getAlkuruutu().getpRivi();
    int mihinRivi = siirto->getLoppuruutu().getRivi();
    int mihinpRivi = siirto->getLoppuruutu().getpRivi();

    Nappula *n = lauta[mistaRivi][mistapRivi];
    int vari = n->getVari();
    Korotus koro = siirto->getKorotus();

    lauta[mistaRivi][mistapRivi] = nullptr;
    delete lauta[mihinRivi][mihinpRivi];

    if (koro != ei_koro) {
        delete n;
        switch (koro) {
        case daami: lauta[mihinRivi][mihinpRivi] = new Daami(L"\u2655", vari, MD); 
        break;
        case torni: lauta[mihinRivi][mihinpRivi] = new Torni(L"\u2656", vari, MT); 
        break;
        case lahetti: lauta[mihinRivi][mihinpRivi] = new Lahetti(L"\u2657", vari, VL); 
        break;
        case ratsu: lauta[mihinRivi][mihinpRivi] = new Ratsu(L"\u2658", vari, VR); 
        break;
        default: break;
        }
    } else {
        lauta[mihinRivi][mihinpRivi] = n;
    }


    if (n == nullptr)
        return;

    int tyyppi = n->getNimi();

    if (tyyppi == VK)
        VKliikkunut = true;
    else if (tyyppi == MK)
        MKliikkunut = true;
    else if (tyyppi == VT)
    {
        if (mistapRivi == 0)
            VDTliikkunut = true;
        if (mistapRivi == 7)
            VKTliikkunut = true;
    }
    else if (tyyppi == MT)
    {
        if (mistapRivi == 0)
            MDTliikkunut = true;
        if (mistapRivi == 7)
            MKTliikkunut = true;
    }
    lauta[mihinRivi][mihinpRivi] = n;
    lauta[mistaRivi][mistapRivi] = nullptr;
    siirtovuoro = (siirtovuoro == 0) ? 1 : 0;
}

void Asema::annaLaillisetSiirrot(std::list<Siirto> &lista)
{
    std::list<Siirto> raakaSiirrot;

    for (int rivi = 0; rivi < 8; rivi++) {
        for (int pRivi = 0; pRivi < 8; pRivi++) {
            Nappula *nappula = lauta[rivi][pRivi];
            if (nappula != nullptr && nappula->getVari() == siirtovuoro) {
                Ruutu ruutu(rivi, pRivi);
                nappula->annaSiirrot(raakaSiirrot, &ruutu, this, siirtovuoro);
            }
        }
    }

    for (auto it = raakaSiirrot.begin(); it != raakaSiirrot.end(); ) {
        int nykyinenVuoro = siirtovuoro;
        bool vk = VKliikkunut, mk = MKliikkunut;
        bool vdt = VDTliikkunut, mdt = MDTliikkunut;
        bool vkt = VKTliikkunut, mkt = MKTliikkunut;

        Nappula* syoty = nullptr;
        if (!it->LyhytLinna() && !it->PitkaLinna()) {
            syoty = lauta[it->getLoppuruutu().getRivi()][it->getLoppuruutu().getpRivi()];
            lauta[it->getLoppuruutu().getRivi()][it->getLoppuruutu().getpRivi()] = nullptr;
        }

        paivitaAsema(&(*it));

        Ruutu kuninkaanPaikka(-1, -1);
        int omaKuningas = (nykyinenVuoro == 0) ? VK : MK;
        
        for (int rivi = 0; rivi < 8; rivi++) {
            for (int pRivi = 0; pRivi < 8; pRivi++) {
                if (lauta[rivi][pRivi] != nullptr && lauta[rivi][pRivi]->getNimi() == omaKuningas) {
                    kuninkaanPaikka = Ruutu(rivi, pRivi);
                    break;
                }
            }
        }

        if (onkoRuutuUhattu(kuninkaanPaikka, siirtovuoro)) {
            peruutaSiirto(&(*it), syoty, vk, mk, vdt, mdt, vkt, mkt);
            it = raakaSiirrot.erase(it);
        } else {
            peruutaSiirto(&(*it), syoty, vk, mk, vdt, mdt, vkt, mkt);
            lista.push_back(*it);
            ++it;
        }
    }
}

bool Asema::onkoRuutuUhattu(Ruutu r, int hyokkaavaVari) {
    std::list<Siirto> vastustajanSiirrot;
    for (int rivi = 0; rivi < 8; rivi++) {
        for (int pRivi = 0; pRivi < 8; pRivi++) {
            Nappula *n = lauta[rivi][pRivi];
            if (n != nullptr && n->getVari() == hyokkaavaVari) {
                Ruutu alku(rivi, pRivi);
                n->annaSiirrot(vastustajanSiirrot, &alku, this, hyokkaavaVari);
            }
        }
    }
    for (auto& s : vastustajanSiirrot) {
        if (!s.LyhytLinna() && !s.PitkaLinna()) {
            if (s.getLoppuruutu().getRivi() == r.getRivi() && 
                s.getLoppuruutu().getpRivi() == r.getpRivi()) {
                return true;
            }
        }
    }
    return false;
}

void Asema::peruutaSiirto(Siirto *s, Nappula *syoty, bool vk, bool mk, bool vdt, bool mdt, bool vkt, bool mkt) {
    if (s->LyhytLinna()) {
        int rivi = (siirtovuoro == 1) ? 7 : 0;
        lauta[rivi][4] = lauta[rivi][6]; lauta[rivi][7] = lauta[rivi][5];
        lauta[rivi][6] = nullptr; lauta[rivi][5] = nullptr;
    } else if (s->PitkaLinna()) {
        int rivi = (siirtovuoro == 1) ? 7 : 0;
        lauta[rivi][4] = lauta[rivi][2]; lauta[rivi][0] = lauta[rivi][3];
        lauta[rivi][2] = nullptr; lauta[rivi][3] = nullptr;
    } else {
        Ruutu alku = s->getAlkuruutu();
        Ruutu loppu = s->getLoppuruutu();
        lauta[alku.getRivi()][alku.getpRivi()] = lauta[loppu.getRivi()][loppu.getpRivi()];
        lauta[loppu.getRivi()][loppu.getpRivi()] = syoty;
        if (s->getKorotus() != ei_koro) {
            int vari = (siirtovuoro == 1) ? 0 : 1;
            delete lauta[alku.getRivi()][alku.getpRivi()];
            lauta[alku.getRivi()][alku.getpRivi()] = new Sotilas(L"\u265F", vari, (vari==0?VS:MS));
        }
    }
    siirtovuoro = (siirtovuoro == 0) ? 1 : 0;
    VKliikkunut = vk; MKliikkunut = mk;
    VDTliikkunut = vdt; MDTliikkunut = mdt;
    VKTliikkunut = vkt; MKTliikkunut = mkt;
}