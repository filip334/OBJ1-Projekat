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

	//virtual ~Kamion() = default;

	string informacijeVozila() const override {
		return "Kamion: " + Vozilo::informacijeVozila() + "//Nosivost: " + to_string(nosivost) + "kg";
	}
	
	
};

