#include <iostream>
#include <string>
#include <map>
#include "Vozilo.h"
#pragma once
using namespace std;
class Automobil : public Vozilo
{
private:
	string tipKaroserije;
	string pogon;
	int brojVrata;
public:
	Automobil(const string& m, const string& mo, int g,const string& tipKaroserije, const string& pogon, int b)
		: Vozilo(m, mo, g), tipKaroserije(tipKaroserije), pogon(pogon), brojVrata(b) {}


	string informacijeVozila() const override {
		return "Automobil: " + Vozilo::informacijeVozila() + "//Tip: " + tipKaroserije + "//Pogon: " + pogon + "//Vrata: " + to_string(brojVrata);
	}

	map<string, string> toMap() const override {
		return { {"marka", marka}, {"model", model}, {"godina", to_string(godinaProizvodnje)}, {"karoserija", tipKaroserije} , {"pogon", pogon} , {"vrata", to_string(brojVrata)}};
	}
	//virtual ~Automobil() = default;
};

