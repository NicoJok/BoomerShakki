#include <iostream>
#include <io.h>
#include <fcntl.h>
#include "asema.h"
#include "kayttoliittyma.h"
#include <vector>

int main() {
    _setmode(_fileno(stdout), _O_U16TEXT);
    _setmode(_fileno(stdin), _O_U16TEXT);

    Asema asema;
    Kayttoliittyma ui(&asema);

    std::wcout << L"---Shakki---" << std::endl;

    while (true) {
        ui.piirraLauta();

        std::wcout << L"\nVuoro: "
            << (asema.getSiirtoVuoro() == 0 ? L"Valkea" : L"Musta")
            << std::endl;

        // Muodosta lailliset siirrot
        std::vector<Siirto> laillisetSiirrot;
        asema.annaLaillisetSiirrot(laillisetSiirrot);

		//Debuggausta varten tulostetaan laillisten siirtojen määrä
        std::wcout << L"Laillisia siirtoja: " << laillisetSiirrot.size() << std::endl;

        // Tarkistetaan onko matti tai patti
        if (laillisetSiirrot.size() == 0) {
            // Tarkista onko kuningas shakissa
            int kuningasKoodi = (asema.getSiirtoVuoro() == 0) ? VK : MK;
			int kuningasRivi = -1; // Alustetaan kuninkaan sijainti -1 joka tarkoittaa, että sitä ei ole löydetty
            int kuningasSarake = -1; //Jos alustusta ei tehdä, saattaa olla että sijainti on virheellinen

            for (int r = 0; r < 8; r++) {
                for (int s = 0; s < 8; s++) {
                    if (asema.lauta[r][s] != nullptr &&
                        asema.lauta[r][s]->getKoodi() == kuningasKoodi) {
						kuningasRivi = r; //Asetetaan kuninkaan sijainti
                        kuningasSarake = s;
                        break;
                    }
                }
				if (kuningasRivi != -1) break; //Tarkistetaan onko kuningas löytynyt, jos löytyy ei tarvitse jatkaa
            }

            int vastustaja = (asema.getSiirtoVuoro() == 0) ? 1 : 0;
            bool onShakissa = asema.onkoRuutuUhattu(kuningasRivi, kuningasSarake, vastustaja);

            if (onShakissa) {
                std::wcout << L"\nShakkimatti! "
                    << (asema.getSiirtoVuoro() == 0 ? L"MUSTA" : L"VALKEA")
                    << L" Voitti!" << std::endl;
            }
            else {
                std::wcout << L"\nPatti! Tasapeli!" << std::endl;
            }
            break;
        }

        // Kysy siirtoa kunnes laillinen
        bool laillinenSiirto = false;
        Siirto valittuSiirto(Ruutu(0, 0), Ruutu(0, 0));

        while (!laillinenSiirto) {
            Siirto siirto = ui.annaVastustajanSiirto();

            // Tarkistetaan onko siirto laillisten listalla?
            for (const auto& laillinen : laillisetSiirrot) {
                if (siirto.getAlkuRuutu() == laillinen.getAlkuRuutu() &&
                    siirto.getLoppuRuutu() == laillinen.getLoppuRuutu()) {

                    //Tarkistetaan korotus
					if (laillinen.getKorotusNappula() != 0) {
						//Kysytään pelaajalta mihin nappulaan korotetaan
                        int korotusNappula = ui.kysyKorotusNappula();
                        siirto.setKorotusNappula(korotusNappula);
                    }

                    laillinenSiirto = true;
                    valittuSiirto = siirto;
                    break;
                }
            }

            if (!laillinenSiirto) {
                std::wcout << L"Laiton siirto! Yritä uudelleen." << std::endl;
            }
        }

        // Tee laillinen siirto
        asema.paivitaAsema(&valittuSiirto);
        std::wcout << L"\n----------------------------------------\n";
    }

    return 0;
}