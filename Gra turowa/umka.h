#ifndef UMKA_H
#define UMKA_H

#include "classes.h"
#include "base.h"

class umka
{
	private:
		string name;
		string koszt;
		bool(*um)(int, int, bool, vector<base*>*);
	public:
		umka(string name, string koszt, bool(*um)(int, int, bool, vector<base*>*)) : name(name), koszt(koszt), um(um) {};
		string get_name() { return name; };
		string get_koszt() { return koszt; };
		bool get_um(int n, int k, vector<base*>* part) { return um(n, k, 1, part); };
		bool check_um(int k, vector<base*>* part) { return um(k, k, 0, part); };
};


#endif
