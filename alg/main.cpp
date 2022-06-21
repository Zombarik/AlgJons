#include "NodeRat.h"
#include "Graph.h"
#include <string>
#include <fstream>
#include <iostream>
#include <time.h>
int main()
{
	ifstream fin("data.txt");
	int n;
	vector<shared_ptr<NodeRat> > library;
	fin >> n;
	n = 7;
	for (int i = 0; i < n; ++i)
		library.push_back(make_shared<NodeRat>(fin));
	fin.close();

	shared_ptr<Graph> graph = make_shared<Graph>();
	graph->build(library);
	graph->show();
	if (!graph->johnsonAlgo())
		cout << "The input graph has a negative weight cycle\n";
	else
		graph->showDistances();

	graph->outputFile("output.txt");
	system("pause");


}