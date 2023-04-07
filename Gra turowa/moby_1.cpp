#include "mob.h"
#include "classes.h"
#include "umka.h"
#include "umki_moby_1.h"
#include "drop_1.h"

using namespace std;

void mob::wilk()
{
	minlv = 5;
	if (lv < minlv) lv = minlv;
	maxlv = 8;
	if (lv > maxlv) lv = maxlv;
	base_hp = 2.5 * sqrt(20) * pow(lv, 3.0 / 2);
	base_stamina = 50 + (lv - minlv) * 5;
	base_mana = 0;
	maxhp = base_hp;
	maxstamina = base_stamina;
	maxmana = base_mana;
	hp = base_hp;
	stamina = base_stamina;
	mana = base_mana;
	base_dmg = sqrt(20) * pow(lv, 3.0 / 2);
	base_speed = 20 + (lv - minlv) * 3;
	base_armor = 0.66 * sqrt(20) * pow(lv, 3.0 / 2);
	armor = base_armor;
	dmg = base_dmg;
	speed = base_speed;
	hp_regen = 0;
	stamina_regen = 5;
	mana_regen = 0;
	umki.push_back(new umka("Zwykly atak", "0", zwykly_atak_wilk));
	umki.push_back(new umka("Rozszarpanie", "20 staminy", rozszarpanie_wilk));
	drop = wilk_drop;
}



//void mob::umki_create(string nazwa)
//{
	//umki.push_back(new umka("Zwykly atak", zwykly_atak_wilk));
	//umki.push_back(new umka("Rozszarpanie", rozszarpanie_wilk));

	/*
	n = rand() % 2;
	bool k = 0;
	static int szansa;
	szansa = static_cast<int>(static_cast<double>(rand() % 100 + 1));
flaga:
	if (k == 1)
		n = rand() % 2;

	switch (n)
	{
	case 0:
		cout << "wilk wykonal zwykly atak" << endl << endl;
		return static_cast<int>(dmg * (static_cast<double>(rand() % 201 + 300) / 400));
	case 1:
		if (stamina < 20) { k = 1; goto flaga; }
		cout << "wilk wykonal rozszarpanie" << endl << endl;
		set_stamina(stamina - 20);
		if (szansa >= 65)
		{
			player->add_effect(new efekt("krwawienie", 0, 0, 0, 0, 0, static_cast<int>(- (4 + (lv - minlv) * 0.7)), 0, 0, 2));
			cout << "*krwawienie (2 tury)*" << endl << endl;
		}
		return static_cast<int>(1.3 * dmg * (static_cast<double>(rand() % 201 + 300) / 400));
	}
	*/
//}
/*
int goblin::umki(int* n, base* player)
{
	*n = rand() % 3;
	bool k = 0;
flaga:
	if (k == 1)
		*n = rand() % 3;

	switch (*n)
	{
	case 0:
		cout << "goblin wykonal zwykly atak" << endl << endl;
		return static_cast<int>(dmg * (static_cast<double>(rand() % 200 + 301) / 400));
	case 1:
		if (stamina < 20) { k = 1; goto flaga; }
		cout << "goblin wykonal silny atak" << endl << endl;
		set_stamina(stamina - 20);
		return static_cast<int>(1.5 * dmg * (static_cast<double>(rand() % 200 + 301) / 400));
	case 2:
		if (mana < 25) { k = 1; goto flaga; }
		cout << "goblin wpadl w furie" << endl << endl;;
		set_mana(mana - 25);
		add_effect(new efekt("furia", 0, 0, 0, static_cast<int>(dmg * 1.1), 0, 0, 0, 5));
		return 0;
	default:
		return 0;
	}
}
*/ /*
int paj¹k::umki(int* n, base* player)
{
	*n = rand() % 4;
	bool k = 0;
	static int buff = 0;
	static int szansa;
	szansa = static_cast<int>(static_cast<double>(rand() % 100 + 1)) + buff;
flaga:
	if (k == 1)
		*n = rand() % 4;

	switch (*n)
	{
	case 0:
		cout << "pajak wykonal zwykly atak" << endl << endl;
		return static_cast<int>(dmg * (static_cast<double>(rand() % 200 + 301) / 400));
	case 1:
		if (stamina < 25) { k = 1; goto flaga; }
		cout << "pajak wykonal zatruty atak" << endl << endl;
		set_stamina(stamina - 25);
		if (szansa >= 65)
		{
			player->add_effect(new efekt("zatrucie", 0, 0, 0, 0, -8, 0, 0, 3));
			cout << "*zatrucie (3 tury)*" << endl << endl;
		}
		return static_cast<int>(1.33 * dmg * (static_cast<double>(rand() % 200 + 301) / 400));
	case 2:
		if (stamina < 10) { k = 1; goto flaga; }
		cout << "pajak pluje pajeczyna" << endl << endl;
		set_stamina(stamina - 10);
		if (szansa >= 65) { player->set_ban(2); cout << "*obezwladnienie (2 tury)*" << endl << endl; };
		return 0;
	case 3:
		if (mana < 15) { k = 1; goto flaga; }
		cout << "pajak wyostrza zmysly" << endl << endl;
		set_mana(mana - 15);
		buff += 5;
		return 0;
	default:
		return 0;
	}

}
*/