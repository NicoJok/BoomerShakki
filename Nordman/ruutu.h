#pragma once


// Shakkilaudan ruutu tietyssä (rivi, sarake) -koordinaatissa.
class Ruutu {
public:
	Ruutu(int sarake, int rivi) : _sarake(sarake), _rivi(rivi) {}
	Ruutu() : _sarake(0), _rivi(0) {}
	int getRivi();
	int getSarake();
	void setRivi(int);
	void setSarake(int);

private:
	int _sarake;
	int _rivi;
};
