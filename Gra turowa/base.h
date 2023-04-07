#ifndef BASE_H
#define BASE_H

#include "classes.h"
#include <iostream>
#include <string>
#include <cstdio>
#include <cstdlib>
#include <vector>
#include <ctime>
#include <fstream>

class base
{
	protected:
		string name;
		int lv, minlv, maxlv;
		int hp, maxhp, base_hp;
		int stamina, maxstamina, base_stamina;
		int mana, maxmana, base_mana;
		int hp_regen, stamina_regen, mana_regen;
		int dmg, base_dmg;
		int speed, base_speed;
		int armor, base_armor;
		int ban;
		vector<efekt*> efekty;
		//vector<efekt*> efekty_atk;
		//vector<efekt*> efekty_def;
		//vector<int> los_temp;
		vector<umka*> umki;
		vector<item*> items;
		vector<item*> plecak;
		int size = 30;
		void(*drop)(base*);
	public:
		base() {};
		base(int lv, string name) : lv(lv), name(name), ban(0) {};
		base(int base_hp, int base_stamina, int base_mana, int base_dmg, double base_speed, int base_armor) :
			hp(base_hp),
			maxhp(base_hp),
			base_hp(base_hp),
			stamina(base_stamina),
			maxstamina(base_stamina),
			base_stamina(base_stamina),
			mana(base_mana),
			maxmana(base_mana),
			base_mana(base_mana),
			base_dmg(base_dmg),
			dmg(base_dmg), 
			ban(0), 
			speed(base_speed),
			base_speed(base_speed),
			base_armor(base_armor),
			armor(base_armor) {};
		virtual ~base(){};
		virtual void umki_create(string) = 0;
		void set_hp(int hp){this->hp = hp;};
		void set_maxhp(int maxhp){this->maxhp = maxhp;};
		void set_base_hp(int base_hp) { this->base_hp = base_hp; };
		void set_stamina(int stamina){this->stamina = stamina;};
		void set_maxstamina(int maxstamina){this->maxstamina = maxstamina;};
		void set_base_stamina(int base_stamina) { this->base_stamina = base_stamina; };
		void set_mana(int mana){this->mana = mana;};
		void set_maxmana(int maxmana){this->maxmana = maxmana;};
		void set_base_mana(int base_mana) { this->base_mana = base_mana; };
		void set_dmg(int dmg){this->dmg = dmg;};
		void set_base_dmg(int base_dmg) { this->base_dmg = base_dmg; };
		void set_speed(int speed) {this->speed = speed;};
		void set_base_speed(int base_speed) { this->base_speed = base_speed; };
		void set_armor(int armor) { this->armor = armor; };
		void set_base_armor(int base_armor) { this->base_armor = base_armor; };
		void set_ban(int ban) { this->ban += ban; };
		void set_hp_regen(int hp_regen) { this->hp_regen = hp_regen; };
		void set_stamina_regen(int stamina_regen) { this->stamina_regen = stamina_regen; };
		void set_mana_regen(int mana_regen) { this->mana_regen = mana_regen; };
		int get_lv() { return lv; };
		int get_minlv() { return minlv; };
		int get_maxlv() { return maxlv; };
		int get_dmg(){return dmg;};
		int get_base_dmg() { return base_dmg; };
		int get_speed() { return speed; };
		int get_base_speed() { return base_speed; };
		int get_armor() { return armor; };
		int get_base_armor() { return base_armor; };
		int get_stamina(){return stamina;};
		int get_mana(){return mana;};
		int get_hp(){return hp;};
		int get_maxstamina(){return maxstamina;};
		int get_maxmana(){return maxmana;};
		int get_maxhp(){return maxhp;};
		int get_base_stamina() { return base_stamina; };
		int get_base_mana() { return base_mana; };
		int get_base_hp() { return base_hp; };
		int get_ban() { return ban; };
		int get_hp_regen(){ return hp_regen; };
		int get_stamina_regen() { return stamina_regen; };
		int get_mana_regen() { return mana_regen; };
		string get_name() { return name; };
		int get_size() { return size; };
		void add_effect(efekt* eff) { efekty.push_back(eff); };
		void add_plecak(item* it) { plecak.push_back(it); }
		//void add_effect_atk(efekt* eff) { efekty_atk.push_back(eff); };
		//void add_effect_def(efekt* eff) { efekty_def.push_back(eff); };
		//void add_los_temp(int los) { los_temp.push_back(los); };
		vector <efekt*>* get_effects() { return &efekty; };
		//vector <efekt*>* get_effects_atk() { return &efekty_atk; };
		//vector <efekt*>* get_effects_def() { return &efekty_def; };
		vector <item*>* get_items() { return &items; };
		vector <item*>* get_plecak() { return &plecak; };
		//vector <int>* get_los_temp() { return &los_temp; };
		vector <umka*>* get_umki() { return &umki; };
		//void erase_effects() { efekty.clear(); };
		void loot(base* obj) { drop(obj); };
};


#endif