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
	virtual ~Vozilo() {
		brojProizvedenihVozila--;
	}

	virtual string informacijeVozila() const {
		return marka + " " + model + " " + to_string(godinaProizvodnje);
	}

	friend ostream& operator<<(ostream& out, const Vozilo& vozilo) {
		out << vozilo.informacijeVozila();
		return out;
	}

	static int GetBrojProizvedenihVozila() { return brojProizvedenihVozila; }

	void setGodinaProizvodnje(int godinaProizvodnje) { this->godinaProizvodnje = godinaProizvodnje; }

	friend int porediVozila(const void*, const void*);
};

