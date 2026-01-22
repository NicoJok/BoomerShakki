#include <iostream>
#ifdef _WIN32
#include <windows.h>
#include <io.h>
#include <fcntl.h>
#endif
#include "asema.h"
#include "Kayttoliittyma.h"

int main() {

	Asema asema;
	Kayttoliittyma kayttoliittyma(&asema);
	kayttoliittyma.piirraLauta();

	return 0;
}