#include "efekt.h"
#include "functions.h"
#include "base.h"

void efekt::efekt_print()
{
	cout << "name: " << name << "hp: " << hp << "   stamina: " << stamina << "   mana: " << mana << "   dmg: " << dmg << "   cooldown: " << cooldown << endl;
}

void efekt::include_effects(base* object)
{
	object->set_maxhp(object->get_maxhp() + hp);
	object->set_maxstamina(object->get_maxstamina() + stamina);
	object->set_maxmana(object->get_maxmana() + mana);
	object->set_dmg(object->get_dmg() + dmg);
}

void efekt::delete_effect(base* object)
{
	object->set_maxhp(object->get_maxhp() - hp);
	object->set_maxstamina(object->get_maxstamina() - stamina);
	object->set_maxmana(object->get_maxmana() - mana);
	object->set_dmg(object->get_dmg() - dmg);
	equalize(object);
}
