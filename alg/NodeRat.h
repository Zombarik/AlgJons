#pragma once
#include <fstream>
#include <vector>
#include <string>
#include <iostream>

using namespace std;

struct rat {
	int ch; // ��������� 
	int zn; // ����������� 
};
class NodeRat
{
	rat id; //���������/���������
public:

	NodeRat(ifstream &fin);

	rat getId();
	void show();
	~NodeRat();
};
