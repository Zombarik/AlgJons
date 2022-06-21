#include "NodeRat.h"


NodeRat::NodeRat(ifstream &fin)
{
	string s = "";
	while (s == "")
		getline(fin, s);
	int i = 1;

	id.ch = 0;		//чисельник
	for (; s[i] != '|'; ++i)
	{
		id.ch = id.ch * 10 + s[i] - '0';
	}
	while (s[i] != '|') ++i;
	++i;

	id.zn = 0;		//знаменник
	for (; s[i] != '|'; ++i)
	{
		id.zn = id.zn * 10 + s[i] - '0';
	}
	while (s[i] != '|') ++i;
	++i;


}


rat NodeRat::getId()
{
	return id;
}


void NodeRat::show()
{

	cout << "Rat: " << id.ch / id.zn << '\n';
}

NodeRat::~NodeRat()
{
}
