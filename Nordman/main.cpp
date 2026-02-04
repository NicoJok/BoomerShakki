#include <iostream>
#include <Windows.h>
#include <io.h>
#include <fcntl.h>
#include <iostream>
#include <string>
#include "kayttoliittyma.h"
#include "siirto.h"
#include "asema.h"

using namespace std;

int main()
{
	wcout << L"HeippariShakki\n";
	wcout << L"Tervetuloa pelaamaan!\n";
	
	Asema asema;
	Kayttoliittyma::getInstance()->aseta_asema(&asema);
	
	// Testataan siirtojen lukemista ja aseman päivitystä
	while (true) {
		Kayttoliittyma::getInstance()->piirraLauta();
		
		wcout << L"\nSiirtovuoro: " << (asema.getSiirtovuoro() == 0 ? L"Valkea" : L"Musta") << L"\n";
		
		Siirto siirto = Kayttoliittyma::getInstance()->annaVastustajanSiirto();
		
		if (!asema.onkoSiirtoLaillinen(siirto)) {
			wcout << L"Virhe: Siirto ei ole laillinen. Yritä uudelleen.\n\n";
			continue;
		}
		
		if (siirto.onkoLyhytLinna()) {
			wcout << L"Tehty lyhyt linna (O-O)\n";
		}
		else if (siirto.onkoPitkalinna()) {
			wcout << L"Tehty pitkä linna (O-O-O)\n";
		}
		else {
			Ruutu alku = siirto.getAlkuruutu();
			Ruutu loppu = siirto.getLoppuruutu();
			wcout << L"Siirto: (" << alku.getRivi() << L"," << alku.getSarake() 
				  << L") -> (" << loppu.getRivi() << L"," << loppu.getSarake() << L")\n";
		}
		
		asema.paivitaAsema(&siirto);
		wcout << L"\n";
	}

	return 0;
}
