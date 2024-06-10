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
	
	//virtual ~Automobil() = default;

	string informacijeVozila() const override {
		return "Automobil " + Vozilo::informacijeVozila() + " " + tipKaroserije + " " + pogon + " " + to_string(brojVrata);
	}
	
};

