#include "ConfigLoader.h"

#include <iostream>
#include <cstdlib>

using namespace std;

int main()
{
	ConfigLoader cfg("config.txt");
	cfg.parse();
	cout << "VarA = " << cfg.getVal<int>("VarA") << endl;
	cout << "VarB = " << cfg.getVal<double>("VarB") << endl;
	cout << "VarC = " << cfg.getVal<int>(999, "VarC") << endl;	
	cout << "Last = " << cfg.getVal<string>("VarLast") << endl;
};
