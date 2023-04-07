#include "helm.h"
#include "efekt.h"
#include "item.h"

item_dane futro_wilka(int tryb, base* obj)
{
	int lv = 6;

	int hp = 30;
	int stamina = 10;
	int mana = 0;
	int hp_regen = 0;
	int stamina_regen = 3;
	int mana_regen = 0;
	int dmg = 0;
	int speed = 0;
	int armor = 5;

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
	dane.typ = "Zbroja";
	dane.lv = lv;
	dane.is_eff = 0;
	dane.eff = NULL;

	return dane;
}