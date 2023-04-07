#include "classes.h"
#include "functions.h"
#include "base.h"
#include "gracz.h"
#include "mob.h"
#include "walka.h"

using namespace std;

int main()
{
	srand(time(NULL));

	
	mob wilk_1(5, "Wilk");
	mob wilk_2(6, "Wilk");
	mob wilk_3(7, "Wilk");
	gracz player;

	vector<base*> part;
	part.push_back(&player);
	part.push_back(&wilk_1);
	part.push_back(&wilk_2);
	part.push_back(&wilk_3);
	walka w_1(part);
	w_1.fight();
	
	/*
	fstream save;
	save.open("pliki/save_backup.txt", ios::in);
	string temp;
	for (int i = 0; i < 27; i++)
	{
		getline(save, temp);
		cout << temp << endl;
	}
	save.close();
	system("pause");

	cout << endl << endl;

	save.open("pliki/save.txt", ios::in);
	for (int i = 0; i < 27; i++)
	{
		getline(save, temp);
		cout << temp << endl;
	}
	save.close();
	*/

	system("pause");
	return 0;

}
