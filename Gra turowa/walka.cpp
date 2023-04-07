#include "walka.h"
#include "functions.h"
#include "umka.h"

int walka::tura()
{
	static int tura = 0;
	static int speed_min = 1000000;
	static int speed_max = 0;
	static int number_max;
	static int number_min;
	tura++;

	for (int i = 0; i < part.size(); i++)
	{
		speed_temp[i] += part[i]->get_speed();
		if (speed_temp[i] <= speed_min) { speed_min = speed_temp[i]; number_min = i; }
	}

	cout << "Tura " << tura << endl << endl;;
	print_stats_all();


	for (int i = 0; i < 1000; i++)
	{
		for (int j = 0; j < part.size(); j++)
			if (speed_temp[j] > speed_max) { speed_max = speed_temp[j]; number_max = j; }

		if (number_max == 0)
		{
			speed_temp[0] -= speed_min;
			if (part[0]->get_ban() == 0) 
			{ 
				static int count = 0;
				for (int k = 1; k < part.size(); k++)
					if (part[k]->get_hp() > 0) count++;
				if (count && part[0]->get_hp() > 0) player_tura();
				count = 0;
				if (speed_temp[number_min] == 0) break;
			}
			else part[0]->set_ban(-1);
		}
		else
		{
			speed_temp[number_max] -= speed_min;
			if (part[number_max]->get_ban() == 0) 
			{ 
				if (part[number_max]->get_hp() > 0 && part[0]->get_hp() > 0)enemy_tura(number_max);
				if (speed_temp[number_min] == 0) break; 
			}
			else part[number_max]->set_ban(-1);
		}
		speed_max = 0;
	}

	speed_min = 1000000;

	for (int i = 0; i < part.size(); i++)
		if (part[i]->get_hp() > 0) effects(i);

	for (int i = 1; i < part.size(); i++)
		if (part[i]->get_hp() <= 0) { part[i]->loot(part[0]); part.erase(part.begin() + i); speed_temp.erase(speed_temp.begin() + i); }
	cout << endl;

	return tura;
}

void walka::fight()
{
	static int t = 0;;
	setup();
	while (part[0]->get_hp() > 0 && part.size() > 1 && t < 100)
		t = tura();
	if (t >= 100) {print_stats_all(); cout << "Draw!" << endl; }
	if (part[0]->get_hp() <= 0) { print_stats_all(); cout << "You lose!" << endl; }
	else if (part.size() == 1) cout << "You win!" << endl;
}

void walka::print_stats_all()
{

	for (int i = 0; i < part.size(); i++)
	{
		cout << part[i]->get_name() << ":   ";
		cout << "dmg: " << part[i]->get_dmg() << "  ";
		cout << "hp: " << part[i]->get_hp() << "/" << part[i]->get_maxhp() << "  ";
		cout << "stamina: " << part[i]->get_stamina() << "/" << part[i]->get_maxstamina() << "  ";
		cout << "mana: " << part[i]->get_mana() << "/" << part[i]->get_maxmana() << "     " << speed_temp[i] << endl;
	}
	cout << endl;
}

void walka::print_stats(int i)
{
	cout << part[i]->get_name() << ":   ";
	cout << "dmg: " << part[i]->get_dmg() << "  ";
	cout << "hp: " << part[i]->get_hp() << "/" << part[i]->get_maxhp() << "  ";
	cout << "stamina: " << part[i]->get_stamina() << "/" << part[i]->get_maxstamina() << "  ";
	cout << "mana: " << part[i]->get_mana() << "/" << part[i]->get_maxmana() << "     " << speed_temp[i] << endl;
}

void walka::player_tura()
{	
	static int enemy;
	static int n;
	static int k;

	wybór:
	
	do
	{
		cout << "Wyberz akcje :" << endl;
		for (int i = 0; i < (*part[0]->get_umki()).size(); i++)
			cout << i + 1 << ") " << (*part[0]->get_umki())[i]->get_name() << " (" << (*part[0]->get_umki())[i]->get_koszt() << ")" << endl;
		//cout << "Wybierz akcje:\n1) zwykly atak\n2) silny atak (stamina: 15)\n3) leczenie (mana: 30)\n"; //tutaj
		cin >> n;
		cout << endl;
		k = (*part[0]->get_umki())[n - 1]->check_um(0, &part);
	} while (!k);

	do
	{
		cout << "Wybierz cel :" << endl;
		for (int i = 0; i < part.size(); i++)
			if (part[i]->get_hp() > 0) { cout << i << ") "; print_stats(i); }
			else cout << i << ") dead" << endl;
		cin >> enemy;
		cout << endl;
	} while (part[enemy]->get_hp() <= 0);
	
	if (!(*part[0]->get_umki())[n - 1]->get_um(enemy, 0, &part)) goto wybór;

	if (enemy == 0)
		print_stats(0);
	else
	{
		print_stats(0);
		print_stats(enemy);
	}
	cout << endl;
}

void walka::enemy_tura(int i)
{	
	static int k;
	int n = rand() % (*part[i]->get_umki()).size();
	do
		k = (*part[i]->get_umki())[n]->get_um(0, i, &part);
	while (!k);
	//part[0]->set_hp(part[0]->get_hp() - part[i]->umki_create(n, part[0]));
	print_stats(i);
	print_stats(0);
	cout << endl;
}

void walka::setup()
{
	for (int i = 0; i < part.size(); i++)
		part[i]->add_effect(new efekt("regen", 0, 0, 0, 0, 0, 0, part[i]->get_hp_regen(), part[i]->get_stamina_regen(), part[i]->get_mana_regen(), 100));
	for (int i = 0; i < part.size(); i++)
		speed_temp.push_back(0);
}

void walka::effects(int j)
{
	for (int i = 0; i < (*part[j]->get_effects()).size(); i++)
	{
		part[j]->set_hp(part[j]->get_hp() + (*part[j]->get_effects())[i]->get_roundhp());
		part[j]->set_stamina(part[j]->get_stamina() + (*part[j]->get_effects())[i]->get_roundstamina());
		part[j]->set_mana(part[j]->get_mana() + (*part[j]->get_effects())[i]->get_roundmana());
		(*part[j]->get_effects())[i]->move_cooldown();
		if ((*part[j]->get_effects())[i]->get_cooldown() == 0)
		{
			(*part[j]->get_effects())[i]->delete_effect(part[j]);
			(*part[j]->get_effects()).erase((*part[j]->get_effects()).begin() + i);
			i--;
		}
	}

	equalize(part[j]);
}
