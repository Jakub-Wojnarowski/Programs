#ifndef EFEKT_H
#define EFEKT_H

#include "classes.h"
#include <iostream>
#include "base.h"
#include "gracz.h"

using namespace std;

class efekt
{
	private:
		string name;
		int hp;
		int stamina;
		int mana;
		int dmg;
		int speed;
		int armor;
		int roundhp;
		int roundstamina;
		int roundmana;
		int cooldown;
	public:
		efekt(string name, int hp, int stamina, int mana, int dmg, int speed, int armor, int roundhp, int roundstamina, int roundmana, int cooldown) : 
			name(name), 
			hp(hp), 
			stamina(stamina), 
			mana(mana), 
			dmg(dmg), 
			speed(speed), 
			armor(armor),
			roundhp(roundhp), 
			roundstamina(roundstamina), 
			roundmana(roundmana), 
			cooldown(cooldown) {};
		void efekt_print();
		int get_hp() { return hp; };
		int get_stamina() { return stamina; };
		int get_mana() { return mana; };
		int get_dmg() { return dmg; };
		int get_speed(){ return speed; };
		int get_armor() { return armor; };
		int get_roundhp() { return roundhp; };
		int get_roundstamina() { return roundstamina; };
		int get_roundmana() { return roundmana; };
		int get_cooldown() { return cooldown; };
		void move_cooldown() { cooldown -= 1; };
		void include_effects(base*);
		void delete_effect(base*);
		efekt operator=(efekt object) { return object; };
};



#endif