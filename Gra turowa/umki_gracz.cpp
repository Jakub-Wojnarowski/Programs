#include "umki_gracz.h"
#include "item.h"
#include <cmath>

bool zwykly_atak(int n, int k, bool tryb, vector<base*>* part)
{
	if (n >= 1)
	{
		static int koszt = 0;
		static double um = 1;
		int damage = calculate_damage(n, k, um, part);

		(*part)[n]->set_hp((*part)[n]->get_hp() - damage);
		for (int i = 0; i < (*(*part)[k]->get_items()).size(); i++)
			if ((*(*part)[k]->get_items())[i]->get_is_eff()) (*(*part)[k]->get_items())[i]->get_eff(n, k, part);
		return 1;
	}
	else
	{
		cout << "Nie mozna uzyc na sobie" << endl;
		return 0;
	}
}

bool silny_atak(int n, int k, bool tryb, vector<base*>* part)
{
	static int koszt = 15;
	if (tryb == 0)
	{
		if ((*part)[0]->get_stamina() < koszt)
		{
			cout << "Za malo staminy" << endl;
			return 0;
		}
		else
			return 1;
	}
	else
	{
		if (n >= 1)
		{
			static double um = 1.35;
			int damage = calculate_damage(n, k, um, part);
			(*part)[k]->set_stamina((*part)[k]->get_stamina() - koszt);
			(*part)[n]->set_hp((*part)[n]->get_hp() - damage);
			for (int i = 0; i < (*(*part)[0]->get_items()).size(); i++)
				if ((*(*part)[k]->get_items())[i]->get_is_eff()) (*(*part)[k]->get_items())[i]->get_eff(n, k, part);
			return 1;
		}
		else
		{
			cout << "Nie mozna uzyc na sobie" << endl;
			return 0;
		}
	}
}

bool leczenie(int n, int k, bool tryb, vector<base*>* part)
{	
	static int koszt = 30;
	if (tryb == 0)
	{
		if ((*part)[0]->get_mana() < koszt)
		{
			cout << "Za malo many" << endl;
			return 0;
		}
		else
			return 1;
	}
	else
	{
		if (n == 0)
		{
			int heal = static_cast<int>(0.35 * (*part)[n]->get_maxhp() * (static_cast<double>(rand() % 200 + 301) / 400));
			(*part)[k]->set_mana((*part)[k]->get_mana() - koszt);
			(*part)[n]->set_hp((*part)[n]->get_hp() + heal);
			equalize((*part)[n]);
			return 1;
		}
		else
		{
			cout << "Nie mozna uzyc na przeciwniku" << endl;
			return 0;
		}
	}
}