#pragma once
#include <fstream>
#include <vector>
#include <string>
#include <iostream>

using namespace std;

struct rat {
	int ch; // числитель 
	int zn; // знаменатель 
};
class NodeRat
{
	rat id; //чисельник/знаменник
public:

	NodeRat(ifstream &fin);

	rat getId();
	void show();
	~NodeRat();
};
