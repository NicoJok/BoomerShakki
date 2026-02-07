#pragma once
class Ruutu {
private:
	int rivi;
	int sarake;
public:
	Ruutu(int rivi, int sarake);
	Ruutu() {};
	int getRivi() const;
	int getSarake() const;

	//Vertailu operaattori aseman päivittämistä varten
	bool operator==(const Ruutu& toinen) const {
		return (rivi == toinen.rivi && sarake == toinen.sarake);
	}
};