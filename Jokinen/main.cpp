#include "kayttoliittyma.h"
#include "asema.h"
#include <iostream>
#include "siirto.h"

int main()
{
    Asema asema;
    Kayttoliittyma ui(&asema);

    while (true)
    {
        ui.piirraLauta();
        std::wcout << L"Vuoro: " << (asema.getSiirtovuoro() == 0 ? L"Valkea" : L"Musta") << std::endl;
        std::list<Siirto> laillisetSiirrot;
        asema.annaLaillisetSiirrot(laillisetSiirrot);
        Siirto s = ui.annaVastustajanSiirto();
        bool onLaillinen = false;
        for (auto& siirto : laillisetSiirrot) 
        {
            if (siirto.getAlkuruutu().getRivi() == s.getAlkuruutu().getRivi() &&
                siirto.getAlkuruutu().getpRivi() == s.getAlkuruutu().getpRivi() &&
                siirto.getLoppuruutu().getRivi() == s.getLoppuruutu().getRivi() &&
                siirto.getLoppuruutu().getpRivi() == s.getLoppuruutu().getpRivi())
            {
                onLaillinen = true;
                break;
            }
            if (s.LyhytLinna() && siirto.LyhytLinna()) {
                onLaillinen = true;
                break;
            }
            if (s.PitkaLinna() && siirto.PitkaLinna()) {
                onLaillinen = true;
                break;
            }
        }

        if (!onLaillinen) {
            std::wcout << L"Laiton siirto" << std::endl;
            std::wcin.clear();
            std::wcin.ignore();
            continue;
        }

        if (s.getKorotus() != ei_koro) {
            Korotus valinta = ui.kysyKorotus();
            s = Siirto(s.getAlkuruutu(), s.getLoppuruutu(), valinta);
        }
        asema.paivitaAsema(&s);

        if (s.LyhytLinna())
        {
            std::wcout << L"O-O" << std::endl;
        }
        else if (s.PitkaLinna())
        {
            std::wcout << L"O-O-O" << std::endl;
        }
        else
        {
            wchar_t alkupRivi = L'a' + s.getAlkuruutu().getpRivi();
            wchar_t loppupRivi = L'a' + s.getLoppuruutu().getpRivi();
            int alkuRivi = 8 - s.getAlkuruutu().getRivi();
            int loppuRivi = 8 - s.getLoppuruutu().getRivi();

            std::wcout << alkupRivi << alkuRivi << loppupRivi << loppuRivi << std::endl;
            }
    }

    return 0;
}