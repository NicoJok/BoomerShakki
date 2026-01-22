#include "kayttoliittyma.h"
#include "asema.h"
#include <iostream>

int main()
{
    Asema asema;
    Kayttoliittyma ui(&asema);

    ui.piirraLauta();
    std::wcout << L"Vuoro: " << (asema.getSiirtovuoro() == 0 ? L"Valkea" : L"Musta") << std::endl;
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
        wchar_t alkupRivi = L'a' + s.getAlkuruutu().getpRivi();
        wchar_t loppupRivi = L'a' + s.getLoppuruutu().getpRivi();
        int alkuRivi = 8 - s.getAlkuruutu().getRivi();
        int loppuRivi = 8 - s.getLoppuruutu().getRivi();
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