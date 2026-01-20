#pragma once
#include "asema.h"
#include "nappula.h"

class Kayttoliittyma {
public:
    Kayttoliittyma(Asema* asema);
    void piirraLauta();
private:
    Asema* _asema;
};
