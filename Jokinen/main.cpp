#include "kayttoliittyma.h"
#include "asema.h"
#include <iostream>

int main()
{
    Asema asema;
    Kayttoliittyma ui(&asema);

    ui.piirraLauta();
    std::wcout << L"Siirtovuoro: " << (asema.getSiirtovuoro() == 0 ? L"Valkea" : L"Musta") << std::endl;
    Siirto s = ui.annaVastustajanSiirto();
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
        wchar_t alkuSarake = L'a' + s.getAlkuruutu().getpRivi();
        wchar_t loppuSarake = L'a' + s.getLoppuruutu().getpRivi();
        int alkuRivi = s.getAlkuruutu().getRivi() + 1;
        int loppuRivi = s.getLoppuruutu().getRivi() + 1;

        std::wcout << L"Siirto: " << alkuSarake << alkuRivi << L" -> " << loppuSarake << loppuRivi << std::endl;
    }

    if (asema.getVKLiikkunut())
    {
        std::wcout << L"VK liikkunut" << std::endl;
    }

    std::wcout << std::endl;
    ui.piirraLauta();
    std::wcout << L"Vuoro: " << (asema.getSiirtovuoro() == 0 ? L"Valkea" : L"Musta") << std::endl;

    return 0;
}