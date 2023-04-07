#include "helm.h"
#include "efekt.h"
#include "item.h"

item_dane helm1(int tryb, base* obj)
{
	int lv = 10;

	int hp = 15;
	int stamina = 0;
	int mana = 0;
	int hp_regen = 0;
	int stamina_regen = 0;
	int mana_regen = 0;
	int dmg = 0;
	int speed = 0;
	int armor = 10;

	if (tryb == 1)
	{
		obj->set_base_hp(obj->get_base_hp() + hp);
		obj->set_base_stamina(obj->get_base_stamina() + stamina);
		obj->set_base_mana(obj->get_base_mana() + mana);
		obj->set_hp_regen(obj->get_hp_regen() + hp_regen);
		obj->set_stamina_regen(obj->get_stamina_regen() + stamina_regen);
		obj->set_mana_regen(obj->get_mana_regen() + mana_regen);
		obj->set_base_dmg(obj->get_base_dmg() + dmg);
		obj->set_base_speed(obj->get_base_speed() + speed);
		obj->set_base_armor(obj->get_base_armor() + armor);
	}
	else if (tryb == 0)
	{
		obj->set_base_hp(obj->get_base_hp() - hp);
		obj->set_base_stamina(obj->get_base_stamina() - stamina);
		obj->set_base_mana(obj->get_base_mana() - mana);
		obj->set_hp_regen(obj->get_hp_regen() - hp_regen);
		obj->set_stamina_regen(obj->get_stamina_regen() - stamina_regen);
		obj->set_mana_regen(obj->get_mana_regen() - mana_regen);
		obj->set_base_dmg(obj->get_base_dmg() - dmg);
		obj->set_base_speed(obj->get_base_speed() - speed);
		obj->set_base_armor(obj->get_base_armor() - armor);
	}

	item_dane dane;
	dane.typ = "Helm";
	dane.lv = lv;
	dane.is_eff = 1;
	dane.eff = helm1_effect;

	return dane;
}
void helm1_effect(int n, int k, vector<base*>* part)
{
	static int los = rand() % 100 + 1;
	if(k != 0)
		if(los <= 20) { (*part)[k]->add_effect(new efekt("exhaust", 0, 0, 0, 0, 0, 0, 0, -5, 0, 3)); cout << (*part)[k]->get_name() << " - *Wyczerpanie (3 tury)*" << endl << endl; }
	else if(k == 0)
		if (los <= 15) { (*part)[n]->add_effect(new efekt("poison", 0, 0, 0, 0, 0, 0, -5, 0, 0, 3)); cout << (*part)[n]->get_name() << " - *Trucizna (3 tury)*" << endl << endl; }
}

