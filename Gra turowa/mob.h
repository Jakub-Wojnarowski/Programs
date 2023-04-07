#ifndef MOBY1_H
#define MOBY1_H

#include "efekt.h"
#include "base.h"

class mob : public base
{
	public:
		mob(int lv, string name) : base(lv, name)
		{ 
			if (name == "Wilk") wilk();
		};
		~mob() { efekty.clear(); umki.clear(); };
		void umki_create(string){};
		void wilk();
};
/*
class goblin : public base
{
	public:
		goblin(int lv) : base(lv) {};
		//goblin(int maxhp, int maxstamina, int maxmana, int dmg) : base(maxhp, maxstamina, maxmana, dmg) {};
		int umki(int*, base*);
};
*/ /*
class paj¹k : public base
{
	public:
		paj¹k(int lv) : base(lv) {};
		//paj¹k(int maxhp, int maxstamina, int maxmana, int dmg) : base(maxhp, maxstamina, maxmana, dmg) {};
		int umki(int*, base*);
};
*/
#endif
