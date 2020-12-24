#pragma once
#include "duaList.h"
#include <string>
#include <math.h>

class calculator {

	duaList calculate;
	duaList temp;

	void get_normal();
	void component(string);
	void get_prefix();
	friend string make_res(string input);
	void clone();
	void clear();

public:
	void make_prefix(string input);
	string print_prefix();
	string get_result();

};





#define pi 3.1415926535897932384626433832795
#define e 2.7182818284
using namespace std;

string make_res(string);
string make_operator(string, string, string);
