#pragma once
#include "NodeRat.h"
#include "FibonacciHeap.h"

struct TVertex
{
	int id;
	shared_ptr<NodeRat> noderat;
	vector<pair<shared_ptr<TVertex>, int> > neighbours;

	TVertex(shared_ptr<NodeRat> curBook)
	{
		noderat = curBook;
		neighbours.clear();
	}
};

struct TEdge
{
	shared_ptr<TVertex> from, to;
	int  pos;
	double value;
	TEdge(shared_ptr<TVertex> from, shared_ptr<TVertex> to, int value, int pos) :from(from), to(to), value(value), pos(pos)
	{}
};

class Graph
{

	const int inf = 1e+9 + 7;
	vector<shared_ptr<TVertex> > vertexes;
	vector<shared_ptr<TEdge> > edges;
	vector<vector<int> > distance;
	double createValueOfEdge(shared_ptr<TVertex> &a, shared_ptr<TVertex> &b);
public:
	void removeLast();
	bool algoBellmanFord(vector<int> &h);
	void algoDijkstra(int start);
public:
	Graph();
	void build(vector<shared_ptr<NodeRat> > &library);
	bool johnsonAlgo();
	void show();
	void showEdges();
	void showVertexes();
	void showDistances();
	void outputFile(string s);
	~Graph();
};

