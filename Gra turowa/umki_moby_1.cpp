#include "umki_moby_1.h"
#include "item.h"

// wilk
// {

bool zwykly_atak_wilk(int n, int k, bool tryb, vector<base*>* part)
{
	static int koszt = 0;
	static double um = 1;
	int damage = calculate_damage(n, k, um, part);
	cout << "Wilk wykonal zwykly atak" << endl << endl;
	(*part)[n]->set_hp((*part)[n]->get_hp() - damage);
	for (int i = 0; i < (*(*part)[n]->get_items()).size(); i++)
		if ((*(*part)[n]->get_items())[i]->get_is_eff()) (*(*part)[n]->get_items())[i]->get_eff(n, k, part);
	return 1;
}

bool rozszarpanie_wilk(int n, int k, bool tryb, vector<base*>* part)
{
	static int koszt = 20;
	if ((*part)[k]->get_stamina() < koszt)
		return 0;
	else
	{
		static double um = 1.3;
		int damage = calculate_damage(n, k, um, part);
		int szansa = static_cast<int>(static_cast<double>(rand() % 100 + 1));
		cout << "Wilk wykonal rozszarpanie" << endl << endl;
		(*part)[k]->set_stamina((*part)[k]->get_stamina() - koszt);
		(*part)[n]->set_hp((*part)[n]->get_hp() - damage);
		if (szansa <= 35)
		{
			(*part)[n]->add_effect(new efekt("Krwawienie", 0, 0, 0, 0, 0, 0, static_cast<int>(-(4 + ((*part)[n]->get_lv() - (*part)[n]->get_minlv()) * 0.7)), 0, 0, 2));
			cout << (*part)[n]->get_name() << " - *Krwawienie (2 tury)*" << endl << endl;
		}
		for (int i = 0; i < (*(*part)[n]->get_items()).size(); i++)
			if ((*(*part)[n]->get_items())[i]->get_is_eff()) (*(*part)[n]->get_items())[i]->get_eff(n, k, part);
		return 1;
	}
}

// }