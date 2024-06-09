#include <iostream>
#include <string>
#include <map>
#include "Vozilo.h"
#pragma once

using namespace std;

class Kamion : public Vozilo
{
private:
	int nosivost;
public:
	Kamion(const string& m, const string& mo, int g, int nosivost)
		: Vozilo(m, mo, g), nosivost(nosivost) {}

	/*virtual string informacijeVozila() const override {
		return Vozilo::informacijeVozila() + "//Nosivost: " + to_string(nosivost) + "kg";
	}*/

	string informacijeVozila() const override {
		return "Kamion: " + Vozilo::informacijeVozila() + "//Nosivost: " + to_string(nosivost) + "kg";
	}
	map<string, string> toMap() const override {
		return { {"marka", marka}, {"model", model}, {"godina", to_string(godinaProizvodnje)}, {"nosivost", to_string(nosivost)} };
	}
	//virtual ~Kamion() = default;
};

