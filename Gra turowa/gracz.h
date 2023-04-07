#ifndef GRACZ_H
#define GRACZ_H

#include "classes.h"
#include "functions.h"
#include "umki_gracz.h"
#include "base.h"
#include "efekt.h"
#include "umka.h"

class gracz : public base
{
private:
	int ilosc_umek;
public:
	gracz();
	~gracz() { save(); efekty.clear(); umki.clear(); items.clear(); plecak.clear(); };
	void umki_create(string);
	void items_create(string, string);
	void plecak_create(string);
	void save();
	bool check_save();
};

#endif