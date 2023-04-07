#include "functions.h"
#include <cmath>

void equalize(base* object)
{
	if (object->get_hp() > object->get_maxhp()) object->set_hp(object->get_maxhp());
	if (object->get_stamina() > object->get_maxstamina()) object->set_stamina(object->get_maxstamina());
	if (object->get_mana() > object->get_maxmana()) object->set_mana(object->get_maxmana());
}

int str_to_int(string line)
{
	int number = 0;
	for (int i = 0; i < line.length(); i++)
		number += convert(line[i]) * pow(10, (line.length() - 1 - i));

	return number;
}


int convert(char c)
{
	int x = 0;
	if (c == '1') x = 1;
	else if (c == '2') x = 2;
	else if (c == '3') x = 3;
	else if (c == '4') x = 4;
	else if (c == '5') x = 5;
	else if (c == '6') x = 6;
	else if (c == '7') x = 7;
	else if (c == '8') x = 8;
	else if (c == '9') x = 9;

	return x;
}

int calculate_damage(int n, int k, double um, vector<base*>* part)   //n - atakowany    k - atakuj¹cy
{
	int reg = (*part)[k]->get_dmg();
	double los = static_cast<double>(rand() % 200 + 301) / 400;
	double armor;                                                            //exp(0.5 - 1.6)
	double lv;

	if ((*part)[n]->get_lv() < 20) 
		armor = exp(-1 / (sqrt(20) * pow((*part)[n]->get_lv(), 3.0 / 2)) * (*part)[n]->get_armor());
	else if ((*part)[n]->get_lv() < 40)
		armor = exp(-1 / pow((*part)[n]->get_lv(), 2) * (*part)[n]->get_armor());
	else if ((*part)[n]->get_lv() < 60)
		armor = exp(-40 / pow((*part)[n]->get_lv(), 3) * (*part)[n]->get_armor());
	else if ((*part)[n]->get_lv() < 80)
		armor = exp(-40*60 / pow((*part)[n]->get_lv(), 4) * (*part)[n]->get_armor());
	else
		armor = exp(-40*60*80 / pow((*part)[n]->get_lv(), 5) * (*part)[n]->get_armor());

	if ((*part)[k]->get_lv() > (*part)[n]->get_lv())
		lv = pow((*part)[k]->get_lv() - (*part)[n]->get_lv() + 1, 1.0 / 4);
	else if ((*part)[k]->get_lv() < (*part)[n]->get_lv())
		lv = 1 / pow((*part)[n]->get_lv() - (*part)[k]->get_lv() + 1, 1.0 / 3);
	else
		lv = 1;

	return static_cast<int>(um * reg * los * armor * lv);
}