#ifndef WALKA_H
#define WALKA_H

#include "base.h"
#include "gracz.h"
#include "mob.h"

using namespace std;

class walka 
{
	private:
		vector<base*>& part;
		vector<int> speed_temp;
	public:
		walka(vector<base*>& part) : part(part){};
		int tura();
		void fight();
		void print_stats_all();
		void print_stats(int);
		void player_tura();
		void enemy_tura(int);
		void setup();
		void effects(int);
};


#endif