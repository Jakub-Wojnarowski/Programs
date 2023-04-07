#ifndef ITEM_H
#define ITEM_H

#include "classes.h"
#include "functions.h"

struct item_dane
{
	string typ;
	int lv;
	bool is_eff;
	void(*eff)(int, int, vector<base*>*);
};

class item
{
private:
	string name;
	string typ;
	int lv;
	item_dane(*it)(int, base*);
	bool is_eff;
	void(*eff)(int, int, vector<base*>*);
public:
	item(string name, base* obj = NULL, item_dane(*it)(int, base*) = NULL) : name(name), it(it), eff(eff)
	{ 
		if (it != NULL)
		{
			typ = it(2, obj).typ;
			lv = it(2, obj).lv;
			is_eff = it(2, obj).is_eff;
			eff = it(2, obj).eff;
		}
		else
		{
			typ = "brak";
			lv = 0;
			is_eff = 0;
			eff = NULL;
		}

	};
	void get_eff(int n, int k, vector<base*>* part) { eff(n, k, part); };
	bool get_is_eff() { return is_eff; };
	string get_name() { return name; };
	void activate(int n, base* obj) { if (it != NULL) it(n, obj); };
};



#endif


/*
class item
{
private:
	string nazwa;
	string typ;
	int lv, armor;
	int hp, stamina, mana;
	int hp_regen, stamina_regen, mana_regen;
	int dmg, speed;
	vector<efekt*> efekty;
public:
	int get_lv() { return lv; };
	int get_armor() { return armor; };
	int get_hp() { return hp; };
	int get_stamina() { return stamina; };
	int get_mana() { return mana; };
	int get_hp_regen() { return hp_regen; };
	int get_stamina_regen() { return stamina_regen; };
	int get_mana_regen() { return mana_regen; };
	int get_dmg() { return dmg; };
	int get_speed() { return speed; };
};
*/