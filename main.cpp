#include "ConfigLoader.h"

#include <iostream>
#include <cstdlib>
#include <vector>

using namespace std;

int main()
{
	ConfigLoader cfg("config.txt");
	// Let's try to screw up by commenting this
	// cfg.parse();
	cout << "VarA = " << cfg.getVal<int>("VarA") << endl;
	cout << "VarB = " << cfg.getVal<double>("VarB") << endl;
	cout << "VarC = " << cfg.getVal<int>(999, "VarC") << endl;	
	cout << "Last = " << cfg.getVal<string>("VarLast") << endl;
	cout << "Name = " << cfg.getString("Name") << endl;
	vector<double> v = cfg.getVector<double>("Sequence");
	cout<< "Sequence = ";
	for(unsigned int i  = 0; i < v.size(); i++){
		cout << v[i] << " ";
	}cout<<endl;
};
