#include <iostream>
#include <string>
#include <map>
#pragma once

using namespace std;
class Vozilo
{
protected:
	static int brojProizvedenihVozila;
	string marka, model;
	int godinaProizvodnje;
public:
	Vozilo(const string& m, const string& mo, int g)
		: marka(m), model(mo), godinaProizvodnje(g) {
		brojProizvedenihVozila++;
	}
	virtual ~Vozilo() = default;

	virtual std::map<std::string, std::string> toMap() const = 0;

	virtual string informacijeVozila() const {
		return marka + "//Model: " + model + "//Godina: " + to_string(godinaProizvodnje);
	}

	friend std::ostream& operator<<(std::ostream& os, const Vozilo& vozilo) {
		os << vozilo.informacijeVozila();
		return os;
	}

	static int GetBrojProizvedenihVozila() { return brojProizvedenihVozila; }

	friend int porediVozila(const void*, const void*);
};

