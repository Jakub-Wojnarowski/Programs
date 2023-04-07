#include "drop_1.h"
#include "item.h"
#include "zbroja.h"

using namespace std;

void wilk_drop(base* obj)
{
	int los = rand() % 100 + 1;
	if (los <= 5)
	{
		cout << "Zdobyto : Futro wilka" << endl << endl;
		if (obj->get_plecak()->size() < obj->get_size())
			obj->get_plecak()->push_back(new item("Futro wilka", obj, futro_wilka));
	}
}