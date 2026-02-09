#include <iostream>
#include <io.h>
#include <fcntl.h>
#include "asema.h"
#include "kayttoliittyma.h"

int main() {
    _setmode(_fileno(stdout), _O_U16TEXT);
    _setmode(_fileno(stdin), _O_U16TEXT);

    Asema asema;
    Kayttoliittyma ui(&asema);

    // Pelaa loputtomasti
    while (true) {
        ui.piirraLauta();

        // Näytä siirtovuoro
        std::wcout << L"\nVuoro: "
            << (asema.getSiirtoVuoro() == 0 ? L"Valkea" : L"Musta")
            << std::endl;

        // Näytä lailliset siirrot
        std::vector<Siirto> laillisetSiirrot;
        asema.annaLaillisetSiirrot(laillisetSiirrot);
        std::wcout << L"Laillisia siirtoja: " << laillisetSiirrot.size() << std::endl;

        // Pyydä siirtoa
        Siirto siirto = ui.annaVastustajanSiirto();

        // Päivitä asema
        asema.paivitaAsema(&siirto);

        std::wcout << L"\n";
    }

    return 0;
}