#include <iostream>
#include "minimax.h"
#include "evaluointifunktio.h"
#include <vector>
#include <limits>
#include <chrono>
#include <algorithm>

// Maxi: valkean vuoro, yritetään maksimoida arvo
MinMaxPaluu Minimax::maxi(Asema asema, int syvyys, double alfa, double beta) {
    solmuLaskuri++;
    if ((solmuLaskuri & 2047) == 0) {
        AjanTarkistus();
    }
    if (aikaStop) {
        return {0, Siirto()};
    }

    MinMaxPaluu paluu;
    paluu.evaluointiArvo = -std::numeric_limits<double>::infinity();

    std::vector<Siirto> siirrot;
    asema.annaLaillisetSiirrot(siirrot);

    MoveOrdering(siirrot, asema);

    // Matti tai patti
    if (siirrot.empty()) {
        int kuningasKoodi = (asema.getSiirtoVuoro() == 0) ? VK : MK;
        int kuningasRivi = -1, kuningasSarake = -1;
        for (int r = 0; r < 8; r++)
            for (int s = 0; s < 8; s++)
                if (asema.lauta[r][s] && asema.lauta[r][s]->getKoodi() == kuningasKoodi) {
                    kuningasRivi = r; 
                    kuningasSarake = s;
                }

        int vastustaja = (asema.getSiirtoVuoro() == 0) ? 1 : 0;
        if (asema.onkoRuutuUhattu(kuningasRivi, kuningasSarake, vastustaja))
            paluu.evaluointiArvo = -100000; //Matti
        else
            paluu.evaluointiArvo = 0; //Patti
        return paluu;
    }

    // Lehtisolmu
    if (syvyys == 0) {
        paluu.evaluointiArvo = QSMaxi(asema, alfa, beta);
        return paluu;
    }

    for (const auto& siirto : siirrot) {
        Asema kopio = asema;
        Siirto s = siirto;
        kopio.paivitaAsema(&s);

        MinMaxPaluu tulos = mini(kopio, syvyys - 1, alfa, beta);

        if (tulos.evaluointiArvo > paluu.evaluointiArvo) {
            paluu.evaluointiArvo = tulos.evaluointiArvo;
            paluu.parasSiirto = siirto;
        }

        if (paluu.evaluointiArvo >= beta) {
            break;
        }
        if (paluu.evaluointiArvo > alfa) {
            alfa = paluu.evaluointiArvo;
        }
    }
    
    return paluu;
}

// Mini: mustan vuoro, yritetään minimoida arvo
MinMaxPaluu Minimax::mini(Asema asema, int syvyys, double alfa, double beta) {
    solmuLaskuri++;
    if ((solmuLaskuri & 2047) == 0) {
        AjanTarkistus();
    }
    if (aikaStop) {
        return {0, Siirto()};
    }

    MinMaxPaluu paluu;
    paluu.evaluointiArvo = std::numeric_limits<double>::infinity();

    std::vector<Siirto> siirrot;
    asema.annaLaillisetSiirrot(siirrot);

    MoveOrdering(siirrot, asema); // alfabeta karsinta

    // Matti tai patti
    if (siirrot.empty()) {
        int kuningasKoodi = (asema.getSiirtoVuoro() == 0) ? VK : MK;
        int kuningasRivi = -1, kuningasSarake = -1;
        for (int r = 0; r < 8; r++)
            for (int s = 0; s < 8; s++)
                if (asema.lauta[r][s] && asema.lauta[r][s]->getKoodi() == kuningasKoodi) {
                    kuningasRivi = r; kuningasSarake = s;
                }

        int vastustaja = (asema.getSiirtoVuoro() == 0) ? 1 : 0;
        if (asema.onkoRuutuUhattu(kuningasRivi, kuningasSarake, vastustaja))
            paluu.evaluointiArvo = 100000; //Matti
        else
            paluu.evaluointiArvo = 0; //Patti
        return paluu;
    }

    // Lehtisolmu
    if (syvyys == 0) {
        paluu.evaluointiArvo = QSMini(asema, alfa, beta);
        return paluu;
    }

    for (const auto& siirto : siirrot) {
        Asema kopio = asema;
        Siirto s = siirto;
        kopio.paivitaAsema(&s);

        MinMaxPaluu tulos = maxi(kopio, syvyys - 1, alfa, beta);

        if (tulos.evaluointiArvo < paluu.evaluointiArvo) {
            paluu.evaluointiArvo = tulos.evaluointiArvo;
            paluu.parasSiirto = siirto;
        }

        if (paluu.evaluointiArvo <= alfa) {
            break;
        }
        if (paluu.evaluointiArvo < beta) {
            beta = paluu.evaluointiArvo;
        }
    }

    return paluu;
}
//syvyyden laskenta (5 sekunttia ja break(aika varmasti vain syvyyteen 4 asti))
Siirto Minimax::etsiParasSiirto(Asema asema, int maksimiAikaMs) {
    aloitusAika = std::chrono::steady_clock::now();
    sekunttiAika = maksimiAikaMs;
    aikaStop = false;
    solmuLaskuri = 0;

    Siirto parasSiirto;
    int vuoro = asema.getSiirtoVuoro();
    for (int d = 1; d < 20; d++) {
        std::wcout << L"\rSyvyys: " << d << L"  ||  " << std::flush;
        
        MinMaxPaluu tulos;

        if (vuoro == 0) {
            tulos = maxi(asema, d, -std::numeric_limits<double>::infinity(), std::numeric_limits<double>::infinity()); //Valkea maksimoimaan
        } 
        else {
            tulos = mini(asema, d, -std::numeric_limits<double>::infinity(), std::numeric_limits<double>::infinity()); //Musta minimoimaan
        }
        
        if (aikaStop) {
            break;
        }
        parasSiirto = tulos.parasSiirto;
    }
    return parasSiirto;
}

void Minimax::AjanTarkistus() {
    auto nyt = std::chrono::steady_clock::now();
    auto mennyt = std::chrono::duration_cast<std::chrono::milliseconds>(nyt - aloitusAika).count();
    if (mennyt >= sekunttiAika) {
        aikaStop = true;
    }
}

    //Koko Move Ordering
void Minimax::MoveOrdering(std::vector<Siirto>& siirrot, Asema& asema) {
    auto nappulanArvo = [](int koodi) {
        int (perusKoodi) = koodi % 6;
        switch (perusKoodi) {
            case 5: return 100; // Sotilas (VS = 100, MS = -100)
            case 1: return 300; // Ratsu (VR = 300, MR = -300)
            case 2: return 310; // Lähetti (VL = 310, ML = -310)
            case 0: return 500; // Torni   (VT = 500, MT = -500)
            case 3: return 900; // Daami    (VD = 900, MD = -900)
            case 4: return 10000; // Kuningas   (VK = 10000, MK = -10000)
            default: return 0;
        }
    };
    auto siirronPisteytys = [&](const Siirto& siirto) {
        int arvo = 0;
        Nappula* hyokkaysNappula = asema.lauta[siirto.getLoppuRuutu().getRivi()][siirto.getLoppuRuutu().getSarake()];
        Nappula* puolustusNappula = asema.lauta[siirto.getAlkuRuutu().getRivi()][siirto.getAlkuRuutu().getSarake()];

        if (puolustusNappula != nullptr && hyokkaysNappula != nullptr) {
            int hyokkaysArvo = nappulanArvo(hyokkaysNappula->getKoodi());
            int puolustusArvo = nappulanArvo(puolustusNappula->getKoodi());
            arvo = 10 * puolustusArvo - hyokkaysArvo; // eli esim jos sotilas syö daamin -> 10*900 - 100 = 8900, ja jos D x S -> 10*100 - 900 = 1000-900 = 100
        }

        if (hyokkaysNappula != nullptr && (hyokkaysNappula->getKoodi() == VS || hyokkaysNappula->getKoodi() == MS)) { //En passant
            if (siirto.getAlkuRuutu().getSarake() != siirto.getLoppuRuutu().getSarake() && puolustusNappula == nullptr) {
                arvo = 10 * 100 - 100; //sotilas syö sotilaan en passantilla -> 10*100 - 100 = 900
            }
        }

        if (siirto.getKorotusNappula() != 0) {
            int korotusArvo = siirto.getKorotusNappula() % 6;
            if (korotusArvo == 3) arvo += 9000; // Sotilas korotetaan daamiksi -> 9000
            else if (korotusArvo == 2) arvo += 3100; // Sotilas korotetaan lähetiksi -> 3100
            else if (korotusArvo == 1) arvo += 3000; // Sotilas korotetaan ratsuksi -> 3000
            else if (korotusArvo == 0) arvo += 5000; // Sotilas korotetaan torniksi -> 5000
        }
        return arvo;
    };

    std::sort(siirrot.begin(), siirrot.end(), [&](const Siirto& a, const Siirto& b) {
        return siirronPisteytys(a) > siirronPisteytys(b);
    });
}

double Minimax::QSMaxi(Asema asema, double alfa, double beta) {
    double stand_pat = Evaluointifunktio::evaluoi(&asema);
    if (stand_pat >= beta) {
        return beta;
    }
    if (stand_pat > alfa) {
        alfa = stand_pat;
    }

    std::vector<Siirto> siirrot;
    asema.annaLaillisetSiirrot(siirrot);
    MoveOrdering(siirrot, asema);

    for (const auto& siirto : siirrot) {
        Ruutu loppuRuutu = siirto.getLoppuRuutu();
        Nappula* kohdeNappula = asema.lauta[loppuRuutu.getRivi()][loppuRuutu.getSarake()];
        bool onSyotetty = (kohdeNappula != nullptr);
        
        Nappula* liikkuvaNappula = asema.lauta[siirto.getAlkuRuutu().getRivi()][siirto.getAlkuRuutu().getSarake()];
        if (liikkuvaNappula != nullptr && (liikkuvaNappula->getKoodi() == VS || liikkuvaNappula->getKoodi() == MS)) {
            if (siirto.getAlkuRuutu().getSarake() != siirto.getLoppuRuutu().getSarake() && kohdeNappula == nullptr) {
                onSyotetty = true; // En passant
            }
        }

        if (!onSyotetty && siirto.getKorotusNappula() == 0) {
            continue;
        }
        
        Asema kopio = asema;
        Siirto s = siirto;
        kopio.paivitaAsema(&s);

        double tulos = QSMini(kopio, alfa, beta);
        
        if (tulos >= beta) {
            return beta;
        }
        if (tulos > alfa) {
            alfa = tulos;
        }
    }

    return alfa;
}

double Minimax::QSMini(Asema asema, double alfa, double beta) {
    double stand_pat = Evaluointifunktio::evaluoi(&asema);
    if (stand_pat <= alfa) {
        return alfa;
    }
    if (stand_pat < beta) {
        beta = stand_pat;
    }

    std::vector<Siirto> siirrot;
    asema.annaLaillisetSiirrot(siirrot);
    MoveOrdering(siirrot, asema);

    for (const auto& siirto : siirrot) {
        Ruutu loppuRuutu = siirto.getLoppuRuutu();
        Nappula* kohdeNappula = asema.lauta[loppuRuutu.getRivi()][loppuRuutu.getSarake()];
        bool onSyotetty = (kohdeNappula != nullptr);
        
        Nappula* liikkuvaNappula = asema.lauta[siirto.getAlkuRuutu().getRivi()][siirto.getAlkuRuutu().getSarake()];
        if (liikkuvaNappula != nullptr && (liikkuvaNappula->getKoodi() == VS || liikkuvaNappula->getKoodi() == MS)) {
            if (siirto.getAlkuRuutu().getSarake() != siirto.getLoppuRuutu().getSarake() && kohdeNappula == nullptr) {
                onSyotetty = true; // En passant
            }
        }

        if (!onSyotetty && siirto.getKorotusNappula() == 0) {
            continue;
        }
        
        Asema kopio = asema;
        Siirto s = siirto;
        kopio.paivitaAsema(&s);

        double tulos = QSMaxi(kopio, alfa, beta);
        
        if (tulos <= alfa) {
            return alfa;
        }
        if (tulos < beta) {
            beta = tulos;
        }
    }

    return beta;
}