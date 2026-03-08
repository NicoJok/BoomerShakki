#include <iostream>
#include <io.h>
#include <fcntl.h>
#include "asema.h"
#include "kayttoliittyma.h"
#include "minimax.h"
#include <vector>

int main() {
    _setmode(_fileno(stdout), _O_U16TEXT);
    _setmode(_fileno(stdin), _O_U16TEXT);

    Asema asema;
    Kayttoliittyma ui(&asema);

    double valkeanAika = 900.0;
    double mustanAika = 900.0;
    auto edellinenAika = std::chrono::steady_clock::now();
    std::wcout << L"=== SHAKKI ===" << std::endl;

    while (true) {
        // fyysinen kello ruudulla
        auto nyt = std::chrono::steady_clock::now();
        std::chrono::duration<double> kesto = nyt - edellinenAika;
        edellinenAika = nyt;

        if (asema.getSiirtoVuoro() == 0) valkeanAika -= kesto.count();
        else mustanAika -= kesto.count();
        std::wcout << L"\n Aika: Musta " << (int)valkeanAika/60 << L":" << (int)valkeanAika%60 << L" Valkea | " << (int)mustanAika/60 << L":" << (int)mustanAika%60 << std::endl;
        if (valkeanAika <= 0 || mustanAika <= 0) {
            std::wcout << L"Aika loppui" << std::endl;
            break;
        }
        ui.piirraLauta();

        std::wcout << L"\nVuoro: "
            << (asema.getSiirtoVuoro() == 0 ? L"Valkea" : L"Musta")
            << std::endl;

        // Muodosta lailliset siirrot
        std::vector<Siirto> laillisetSiirrot;
        asema.annaLaillisetSiirrot(laillisetSiirrot);

		//Debuggausta varten tulostetaan laillisten siirtojen m��r�
        std::wcout << L"Laillisia siirtoja: " << laillisetSiirrot.size() << std::endl;

        // Tarkistetaan onko matti tai patti
        if (laillisetSiirrot.size() == 0) {
            // Tarkista onko kuningas shakissa
            int kuningasKoodi = (asema.getSiirtoVuoro() == 0) ? VK : MK;
			int kuningasRivi = -1; // Alustetaan kuninkaan sijainti -1 joka tarkoittaa, ett� sit� ei ole l�ydetty
            int kuningasSarake = -1; //Jos alustusta ei tehd�, saattaa olla ett� sijainti on virheellinen

            for (int r = 0; r < 8; r++) {
                for (int s = 0; s < 8; s++) {
                    if (asema.lauta[r][s] != nullptr &&
                        asema.lauta[r][s]->getKoodi() == kuningasKoodi) {
						kuningasRivi = r; //Asetetaan kuninkaan sijainti
                        kuningasSarake = s;
                        break;
                    }
                }
				if (kuningasRivi != -1) break; //Tarkistetaan onko kuningas l�ytynyt, jos l�ytyy ei tarvitse jatkaa
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

        if (asema.getSiirtoVuoro() == 0) {
            // Valkean vuoro: ihminen pelaa
            bool laillinenSiirto = false;
            Siirto valittuSiirto(Ruutu(0, 0), Ruutu(0, 0));

            while (!laillinenSiirto) {
                Siirto siirto = ui.annaVastustajanSiirto();

                //Tarkistetaan onko siirto laillisten listalla?
                for (const auto& laillinen : laillisetSiirrot) {
                    if (siirto.getAlkuRuutu() == laillinen.getAlkuRuutu() &&
                        siirto.getLoppuRuutu() == laillinen.getLoppuRuutu()) {

                        //Tarkistetaan korotus
                        if (laillinen.getKorotusNappula() != 0) {
                            int korotusNappula = ui.kysyKorotusNappula();
                            siirto.setKorotusNappula(korotusNappula);
                        }

                        laillinenSiirto = true;
                        valittuSiirto = siirto;
                        break;
                    }
                }

                if (!laillinenSiirto) {
                    std::wcout << L"Laiton siirto! Yrita uudelleen." << std::endl;
                }
            }

            //Tee laillinen siirto
            asema.paivitaAsema(&valittuSiirto);

        }
        else {
            // Mustan vuoro: teko�ly pelaa
            std::wcout << L"Tekoaly miettii..." << std::endl;

            Minimax moottori;
            Siirto parasSiirto = moottori.etsiParasSiirto(asema, 5000);
            asema.paivitaAsema(&parasSiirto);

            std::wcout << L"Tekoaly siirsi: "
                << (wchar_t)(L'a' + parasSiirto.getAlkuRuutu().getSarake())
                << (wchar_t)(L'1' + parasSiirto.getAlkuRuutu().getRivi())
                << L" -> "
                << (wchar_t)(L'a' + parasSiirto.getLoppuRuutu().getSarake())
                << (wchar_t)(L'1' + parasSiirto.getLoppuRuutu().getRivi())
                << std::endl;
        }

        std::wcout << L"\n----------------------------------------\n";
    }

    return 0;
}