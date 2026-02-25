#include "minimax.h"
#include "evaluointifunktio.h"
#include <vector>
#include <limits>

// Maxi: valkean vuoro, yritet‰‰n maksimoida arvo
MinMaxPaluu Minimax::maxi(Asema asema, int syvyys) {
    MinMaxPaluu paluu;
    paluu.evaluointiArvo = -std::numeric_limits<double>::infinity();

    std::vector<Siirto> siirrot;
    asema.annaLaillisetSiirrot(siirrot);

    // Matti tai patti
    if (siirrot.empty()) {
        int kuningasKoodi = (asema.getSiirtoVuoro() == 0) ? VK : MK;
        int kuningasRivi = -1, kuningasSarake = -1;
        for (int r = 0; r < 8; r++)
            for (int s = 0; s < 8; s++)
                if (asema.lauta[r][s] && asema.lauta[r][s]->getKoodi() == kuningasKoodi)
                {
                    kuningasRivi = r;
                    kuningasSarake = s;
                }

        int vastustaja = (asema.getSiirtoVuoro() == 0) ? 1 : 0;
        if (asema.onkoRuutuUhattu(kuningasRivi, kuningasSarake, vastustaja))
            paluu.evaluointiArvo = -100000; // Matti, valkea h‰visi
        else
            paluu.evaluointiArvo = 0; // Patti
        return paluu;
    }

    // Lehtisolmu
    if (syvyys == 0) {
        paluu.evaluointiArvo = Evaluointifunktio::evaluoi(&asema);
        return paluu;
    }

    for (const auto& siirto : siirrot) {
        Asema kopio = asema;
        Siirto s = siirto;
        kopio.paivitaAsema(&s);

        MinMaxPaluu tulos = mini(kopio, syvyys - 1);

        if (tulos.evaluointiArvo > paluu.evaluointiArvo) {
            paluu.evaluointiArvo = tulos.evaluointiArvo;
            paluu.parasSiirto = siirto;
        }
    }

    return paluu;
}

// Mini: mustan vuoro, yritet‰‰n minimoida arvo
MinMaxPaluu Minimax::mini(Asema asema, int syvyys) {
    MinMaxPaluu paluu;
    paluu.evaluointiArvo = std::numeric_limits<double>::infinity();

    std::vector<Siirto> siirrot;
    asema.annaLaillisetSiirrot(siirrot);

    // Matti tai patti
    if (siirrot.empty()) {
        int kuningasKoodi = (asema.getSiirtoVuoro() == 0) ? VK : MK;
        int kuningasRivi = -1, kuningasSarake = -1;
        for (int r = 0; r < 8; r++)
            for (int s = 0; s < 8; s++)
                if (asema.lauta[r][s] && asema.lauta[r][s]->getKoodi() == kuningasKoodi)
                {
                    kuningasRivi = r; kuningasSarake = s;
                }

        int vastustaja = (asema.getSiirtoVuoro() == 0) ? 1 : 0;
        if (asema.onkoRuutuUhattu(kuningasRivi, kuningasSarake, vastustaja))
            paluu.evaluointiArvo = 100000; // Matti, musta h‰visi
        else
            paluu.evaluointiArvo = 0; // Patti
        return paluu;
    }

    // Lehtisolmu
    if (syvyys == 0) {
        paluu.evaluointiArvo = Evaluointifunktio::evaluoi(&asema);
        return paluu;
    }

    for (const auto& siirto : siirrot) {
        Asema kopio = asema;
        Siirto s = siirto;
        kopio.paivitaAsema(&s);

        MinMaxPaluu tulos = maxi(kopio, syvyys - 1);

        if (tulos.evaluointiArvo < paluu.evaluointiArvo) {
            paluu.evaluointiArvo = tulos.evaluointiArvo;
            paluu.parasSiirto = siirto;
        }
    }

    return paluu;
}