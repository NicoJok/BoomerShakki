#include "ruutu.h"

Ruutu::Ruutu(int r, int s) : rivi(r), sarake(s) {}

int Ruutu::getRivi() const {
	return rivi;
}
int Ruutu::getSarake() const {
	return sarake;
}