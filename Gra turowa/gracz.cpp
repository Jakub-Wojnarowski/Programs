#include "gracz.h"
#include "functions.h"
#include "umki_gracz.h"
#include "classes.h"
#include "umka.h"
#include "item.h"
#include "helm.h"
#include "zbroja.h"

using namespace std;

gracz::gracz()
{
	fstream save;
	string temp;
	int check = 0;

	save.open("pliki/save_backup.txt", ios::in);
	getline(save, temp);
	while (temp != "\0")
	{
		if (temp == "end")
			check = 1;
		getline(save, temp);
	}
	save.close();

	if(check == 1)
		save.open("pliki/save_backup.txt", ios::in);
	else
		save.open("pliki/save.txt", ios::in);

	getline(save, temp);
	getline(save, temp);
	name = temp;

	getline(save, temp);
	getline(save, temp);
	lv = str_to_int(temp);

	getline(save, temp);
	getline(save, temp);
	base_hp = str_to_int(temp);
	maxhp = base_hp;
	hp = base_hp;

	getline(save, temp);
	getline(save, temp);
	base_stamina = str_to_int(temp);
	maxstamina = base_stamina;
	stamina = base_stamina;

	getline(save, temp);
	getline(save, temp);
	base_mana = str_to_int(temp);
	maxmana = base_mana;
	mana = base_mana;

	getline(save, temp);
	getline(save, temp);
	base_dmg = str_to_int(temp);
	dmg = base_dmg;

	getline(save, temp);
	getline(save, temp);
	base_speed = str_to_int(temp);
	speed = base_speed;

	getline(save, temp);
	getline(save, temp);
	base_armor = str_to_int(temp);
	armor = base_armor;

	getline(save, temp);
	getline(save, temp);
	hp_regen = str_to_int(temp);

	getline(save, temp);
	getline(save, temp);
	stamina_regen = str_to_int(temp);

	getline(save, temp);
	getline(save, temp);
	mana_regen = str_to_int(temp);

	getline(save, temp);
	getline(save, temp);
	ilosc_umek = str_to_int(temp);

	getline(save, temp);
	for (int i = 0; i < ilosc_umek; i++)
	{
		getline(save, temp);
		umki_create(temp);
	}

	getline(save, temp);

	getline(save, temp);
	items_create("Bron", temp);
	getline(save, temp);
	items_create("Pomocnicze", temp);
	getline(save, temp);
	items_create("Helm", temp);
	getline(save, temp);
	items_create("Zbroja", temp);
	getline(save, temp);
	items_create("Rekawice", temp);
	getline(save, temp);
	items_create("Spodnie", temp);
	getline(save, temp);
	items_create("Buty", temp);
	getline(save, temp);
	items_create("Naszyjnik", temp);
	getline(save, temp);
	items_create("Pierscien", temp);
	getline(save, temp);
	items_create("Pierscien", temp);

	getline(save, temp);
	getline(save, temp);

	while (temp != "end" && plecak.size() < size)
	{
		plecak_create(temp);
		getline(save, temp);
	}


	save.close();

	for (int i = 0; i < 10; i++)
		items[i]->activate(1, this);

	/*
	base_hp = 150;
	base_stamina = 50;
	base_mana = 40;
	maxhp = base_hp;
	maxstamina = base_stamina;
	maxmana = base_mana;
	hp = base_hp;
	stamina = base_stamina;
	mana = base_mana;
	base_dmg = 20;
	base_speed = 30;
	dmg = base_dmg;
	speed = base_speed;
	hp_regen = 0;
	stamina_regen = 5;
	mana_regen = 0;
	*/
}

void gracz::umki_create(string nazwa)
{
	if (nazwa == "Zwykly atak") umki.push_back(new umka("Zwykly atak", "0", zwykly_atak));
	else if (nazwa == "Silny atak") umki.push_back(new umka("Silny atak", "15 staminy", silny_atak));
	else if (nazwa == "Leczenie") umki.push_back(new umka("Leczenie", "30 many", leczenie));
}

void gracz::items_create(string typ, string nazwa)
{
	if (typ == "Bron")
	{
		items.push_back(new item("brak"));
	}
	else if (typ == "Pomocnicze")
	{
		items.push_back(new item("brak"));
	}
	else if (typ == "Helm")
	{
		if (nazwa == "Helm1") items.push_back(new item("Helm1", this, helm1));
		else items.push_back(new item("brak"));
	}
	else if (typ == "Zbroja")
	{
		if (nazwa == "Futro wilka") items.push_back(new item("Futro wilka", this, futro_wilka));
		else items.push_back(new item("brak"));
	}
	else if (typ == "Rekawice")
	{
		items.push_back(new item("brak"));
	}
	else if (typ == "Spodnie")
	{
		items.push_back(new item("brak"));
	}
	else if (typ == "Buty")
	{
		items.push_back(new item("brak"));
	}
	else if (typ == "Naszyjnik")
	{
		items.push_back(new item("brak"));
	}
	else if (typ == "Pierscien")
	{
		items.push_back(new item("brak"));
	}
}

void gracz::plecak_create(string nazwa)
{
	if (nazwa == "Helm1") plecak.push_back(new item("Helm1", this, helm1));
	else if (nazwa == "Futro wilka") plecak.push_back(new item("Futro wilka", this, futro_wilka));
}

void gracz::save()
{
	fstream save;
	fstream save_backup;
	string temp;

	for (int i = 0; i < 10; i++)
		items[i]->activate(0, this);

	int count = 0;
	do
	{
		save.open("pliki/save.txt", ios::out);
		save << "Name :\n";
		save << name << "\n";
		save << "Level :\n";
		save << lv << "\n";
		save << "Base hp :\n";
		save << base_hp << "\n";
		save << "Base stamina :\n";
		save << base_stamina << "\n";
		save << "Base mana :\n";
		save << base_mana << "\n";
		save << "Base damage :\n";
		save << base_dmg << "\n";
		save << "Base speed :\n";
		save << base_speed << "\n";
		save << "Base armor :\n";
		save << base_armor << "\n";
		save << "Hp regen :\n";
		save << hp_regen << "\n";
		save << "Stamina regen :\n";
		save << stamina_regen << "\n";
		save << "Mana regen :\n";
		save << mana_regen << "\n";
		save << "Ilosc umek :\n";
		save << ilosc_umek << "\n";
		save << "Umki :\n";
		for (int i = 0; i < ilosc_umek; i++)
			save << umki[i]->get_name() << "\n";
		save << "Ekwipunek :\n";
		for (int i = 0; i < 10; i++)
			save << items[i]->get_name() << "\n";
		save << "Plecak :\n";
		for (int i = 0; i < plecak.size(); i++)
			save << plecak[i]->get_name() << "\n";

		save << "end\n";
		save.close();
		count++;
		if (count >= 10)
		{
			cout << "save error" << endl;
			system("pause");
			exit(0);
		}
	} while (!check_save());

	save.open("pliki/save.txt", ios::in);
	
	count = 0;
	getline(save, temp);
	while (temp != "\0")
	{
		count++;
		getline(save, temp);
	}
	save.close();
	
	save.open("pliki/save.txt", ios::in);
	save_backup.open("pliki/save_backup.txt", ios::out);
	
	for (int i = 0; i < count; i++)
	{
		getline(save, temp);
		save_backup << temp << "\n";
	}
	save.close();
	save_backup.close();

	for (int i = 0; i < 10; i++)
		items[i]->activate(1, this);

}

bool gracz::check_save()
{
	fstream save;
	string temp;
	bool check = 1;
	save.open("pliki/save.txt", ios::in);

	getline(save, temp);
	if (temp != "Name :")
		check = 0;
	getline(save, temp);
	if (temp != name)
		check = 0;

	getline(save, temp);
	if (temp != "Level :")
		check = 0;
	getline(save, temp);
	if (str_to_int(temp) != lv)
		check = 0;

	getline(save, temp);
	if (temp != "Base hp :")
		check = 0;
	getline(save, temp);
	if (str_to_int(temp) != base_hp)
		check = 0;

	getline(save, temp);
	if (temp != "Base stamina :")
		check = 0;
	getline(save, temp);
	if (str_to_int(temp) != base_stamina)
		check = 0;

	getline(save, temp);
	if (temp != "Base mana :")
		check = 0;
	getline(save, temp);
	if (str_to_int(temp) != base_mana)
		check = 0;

	getline(save, temp);
	if (temp != "Base damage :")
		check = 0;
	getline(save, temp);
	if (str_to_int(temp) != base_dmg)
		check = 0;

	getline(save, temp);
	if (temp != "Base speed :")
		check = 0;
	getline(save, temp);
	if (str_to_int(temp) != base_speed)
		check = 0;

	getline(save, temp);
	if (temp != "Base armor :")
		check = 0;
	getline(save, temp);
	if (str_to_int(temp) != base_armor)
		check = 0;

	getline(save, temp);
	if (temp != "Hp regen :")
		check = 0;
	getline(save, temp);
	if (str_to_int(temp) != hp_regen)
		check = 0;

	getline(save, temp);
	if (temp != "Stamina regen :")
		check = 0;
	getline(save, temp);
	if (str_to_int(temp) != stamina_regen)
		check = 0;
		 
	getline(save, temp);
	if (temp != "Mana regen :")
		check = 0;
	getline(save, temp);
	if (str_to_int(temp) != mana_regen)
		check = 0;

	getline(save, temp);
	if (temp != "Ilosc umek :")
		check = 0;
	getline(save, temp);
	if (str_to_int(temp) != ilosc_umek)
		check = 0;

	getline(save, temp);
	if (temp != "Umki :")
		check = 0;

	for (int i = 0; i < ilosc_umek; i++)
	{
		getline(save,temp);
		if (temp != umki[i]->get_name())
			check = 0;
	}
	
	getline(save, temp);
	if (temp != "Ekwipunek :")
		check = 0;

	for (int i = 0; i < 10; i++)
	{
		getline(save, temp);
		if (temp != items[i]->get_name())
			check = 0;
	}

	getline(save, temp);
	if (temp != "Plecak :")
		check = 0;

	for (int i = 0; i < plecak.size(); i++)
	{
		getline(save, temp);
		if (temp != plecak[i]->get_name())
			check = 0;
	}

	getline(save, temp);
	if (temp != "end")
		check = 0;

	return check;
	
}

