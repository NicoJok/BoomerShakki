#pragma once
#include <string>
#include <vector>

//Forward declaration
class Ruutu;
class Asema;
class Siirto;


enum {
    VT, VR, VL, VD, VK, VS,
    MT, MR, ML, MD, MK, MS
};

class Nappula {
	//Vaihdetaan privatesta -> protected, jotta Asema-luokka p‰‰see k‰siksi n‰ihin tietoihin
protected:
    std::wstring unicode;
    int vari;
    int _koodi;

    //Tehd‰‰n pari apufunktiota, jotta voidaan k‰ytt‰‰ samaa liikkumislogiikkaa
	//Tornille, l‰hetille ja daamille
    static void lisaaSuoratSiirrot(std::vector<Siirto>& lista, Ruutu* ruutu, Asema* asema, int vari);
    static void lisaaVinotSiirrot(std::vector<Siirto>& lista, Ruutu* ruutu, Asema* asema, int vari);


public:
    Nappula(std::wstring u, int v, int k);
    Nappula() {};

    void setKoodi(int k);
    int getKoodi();
    void setUnicode(std::wstring u);
    std::wstring getUnicode();
    void setVari(int v);
    int getVari();

	//Tehd‰‰n puhdas virtuaalinen funktio, jotta voidaan toteuttaa erikoisliikkeet (esim. sotilaan tupla-askel, en passant, linnoitus)
    virtual void annaSiirrot(std::vector<Siirto>& lista, Ruutu* ruutu, Asema* asema, int vari) = 0;
    
	//Destruktori, jotta voidaan vapauttaa muisti
	virtual ~Nappula() {}
};

class Torni : public Nappula {
public:
	//Kutsutaan yliluokan konstruktoria
	Torni(std::wstring u, int v, int k) : Nappula(u, v, k) {}
	//Toteutetaan puhdas virtuaalinen funktio annaSiirrot
	void annaSiirrot(std::vector<Siirto>& lista, Ruutu* ruutu, Asema* asema, int vari) override;
};

class Ratsu : public Nappula {
public:
	//Kutsutaan yliluokan konstruktoria
	Ratsu(std::wstring u, int v, int k) : Nappula(u, v, k) {}
	//Toteutetaan puhdas virtuaalinen funktio annaSiirrot
	void annaSiirrot(std::vector<Siirto>& lista, Ruutu* ruutu, Asema* asema, int vari) override;
};

class Lahetti : public Nappula {
    public:
    //Kutsutaan yliluokan konstruktoria
    Lahetti(std::wstring u, int v, int k) : Nappula(u, v, k) {}
    //Toteutetaan puhdas virtuaalinen funktio annaSiirrot
	void annaSiirrot(std::vector<Siirto>& lista, Ruutu* ruutu, Asema* asema, int vari) override;
};

class Daami : public Nappula {
    public:
    //Kutsutaan yliluokan konstruktoria
    Daami(std::wstring u, int v, int k) : Nappula(u, v, k) {}
    //Toteutetaan puhdas virtuaalinen funktio annaSiirrot
    void annaSiirrot(std::vector<Siirto>& lista, Ruutu* ruutu, Asema* asema, int vari) override;
};

class Kuningas : public Nappula {
    public:
    //Kutsutaan yliluokan konstruktoria
    Kuningas(std::wstring u, int v, int k) : Nappula(u, v, k) {}
    //Toteutetaan puhdas virtuaalinen funktio annaSiirrot
    void annaSiirrot(std::vector<Siirto>& lista, Ruutu* ruutu, Asema* asema, int vari) override;
};

class Sotilas : public Nappula {
    public:
    //Kutsutaan yliluokan konstruktoria
    Sotilas(std::wstring u, int v, int k) : Nappula(u, v, k) {}
    //Toteutetaan puhdas virtuaalinen funktio annaSiirrot
    void annaSiirrot(std::vector<Siirto>& lista, Ruutu* ruutu, Asema* asema, int vari) override;
};

