#include "FibonacciHeap.h"


int FibonacciHeap::compareText(const rat a, const rat b)
{

	if (a.ch * b.zn < b.ch * a.zn)
		return -1;
	else if (a.ch * b.zn > b.ch * a.zn)
		return 1;
	else return 0;
}

int FibonacciHeap::compareBooks(const shared_ptr<NodeRat> a, const shared_ptr<NodeRat> b)
{
	return compareText(a->getId(), b->getId());
}



void FibonacciHeap::showDfs(shared_ptr<TNode> v, int numberOfTabs)
{
	if (v->child) 
	{
		shared_ptr<TNode> child = v->child, prevChild = child->leftBrother;
		while (child != prevChild)
		{
			showDfs(child, numberOfTabs + 1);
			child = child->rightBrother;
		}
		showDfs(child, numberOfTabs + 1);
	}
	for (int j = 0; j < numberOfTabs; ++j)
		cout << "\t";
	cout << left << v->data.first << "\n";
}


shared_ptr<TNode> FibonacciHeap::merge(shared_ptr<TNode> firHeap, shared_ptr<TNode> secHeap)
{
	if (firHeap == nullptr)
		return secHeap;
	else if (secHeap == nullptr)
		return firHeap;

	shared_ptr<TNode> newHeap = firHeap;
	shared_ptr<TNode> helpLeft = secHeap->leftBrother;

	helpLeft->rightBrother = newHeap->rightBrother;
	helpLeft->rightBrother->leftBrother = helpLeft;
	secHeap->leftBrother = newHeap;
	newHeap->rightBrother = secHeap;

	if (firHeap->data.first < secHeap->data.first)
		newHeap = firHeap;
	else
		newHeap = secHeap;

	return newHeap;
}

void FibonacciHeap::consolidate()
{
	if (!root || root == root->leftBrother)
		return;

	vector<shared_ptr<TNode> > arrOfRoots(int(log(size) / log(2)) + 2, nullptr);
	shared_ptr<TNode> moveOnHeap = root; 
	while (moveOnHeap != arrOfRoots[moveOnHeap->degree])
	{
 		while (arrOfRoots[moveOnHeap->degree] != nullptr)
		{
			shared_ptr<TNode> inArrValue = arrOfRoots[moveOnHeap->degree];
			arrOfRoots[moveOnHeap->degree] = nullptr;
			inArrValue->rightBrother->leftBrother = inArrValue->leftBrother;
			inArrValue->leftBrother->rightBrother = inArrValue->rightBrother;
			if (moveOnHeap->data.first < inArrValue->data.first)
			{
				inArrValue->parent = moveOnHeap;
				inArrValue->leftBrother = inArrValue->rightBrother = inArrValue;
				shared_ptr<TNode> son = moveOnHeap->child;
				son = merge(son, inArrValue);
				moveOnHeap->child = son;
			}
			else
			{
				moveOnHeap->parent = inArrValue;
				inArrValue->leftBrother = moveOnHeap->leftBrother;
				inArrValue->leftBrother->rightBrother = inArrValue;
				inArrValue->rightBrother = moveOnHeap->rightBrother;
				inArrValue->rightBrother->leftBrother = inArrValue;
				moveOnHeap->rightBrother = moveOnHeap->leftBrother = moveOnHeap;
				shared_ptr<TNode> son = inArrValue->child;
				son = merge(son, moveOnHeap);
				inArrValue->child = son;
				moveOnHeap = inArrValue;
			}
			++moveOnHeap->degree;
		}
		arrOfRoots[moveOnHeap->degree] = moveOnHeap;
		moveOnHeap = moveOnHeap->rightBrother;
	} 
	shared_ptr<TNode> last;
	root = moveOnHeap; last = root;
	do 
	{
		if (moveOnHeap->data.first < root->data.first)
			root = moveOnHeap;
		moveOnHeap = moveOnHeap->rightBrother;
	} while (moveOnHeap != last);		
}

void FibonacciHeap::push(pair<int,int> curData)
{
	shared_ptr<TNode> newNode = make_shared<TNode>(curData);
	++size;
	newNode->leftBrother = newNode->rightBrother = newNode;
	root = merge(root, newNode);
}


FibonacciHeap::FibonacciHeap()
{
	size = 0;
	root = nullptr;
}

pair<int,int> FibonacciHeap::top()
{
	if (root)
		return root->data;
	else
		return {-1, -1};
}

void FibonacciHeap::pop()
{
	if (!root)
		return;

	shared_ptr<TNode> toExtract = root;
	if (root == root->leftBrother)
		root = nullptr;
	else 
		root = root->leftBrother;
	toExtract->leftBrother->rightBrother = toExtract->rightBrother;
	toExtract->rightBrother->leftBrother = toExtract->leftBrother;

	shared_ptr<TNode> newHeap = toExtract->child;
	if (newHeap) 
	{
		shared_ptr<TNode> moveOnHeap = toExtract->child, prevMove = moveOnHeap->leftBrother;
		while (moveOnHeap != prevMove)
		{
			moveOnHeap->parent = nullptr;
			if (moveOnHeap->data.first < newHeap->data.first)
				newHeap = moveOnHeap;
			moveOnHeap = moveOnHeap->rightBrother;
		}
		moveOnHeap->parent = nullptr;
		if (moveOnHeap->data.first < newHeap->data.first)
			newHeap = moveOnHeap;
	}
	root = merge(root, newHeap);
	consolidate();
}

void FibonacciHeap::show()
{
	if (!root)
	{
		cout << "TREE IS EMPTY!!!\n";
		return;
	}
	cout << "\n\n-------------------------------------TREE-------------------------------------\n\n";
	shared_ptr<TNode> temp = root, prevRoot = root->leftBrother;
	while (temp != prevRoot) 
	{
		showDfs(temp, 0);
		temp = temp->rightBrother;
	}
	showDfs(temp, 0);
	cout << '\n';
}

bool FibonacciHeap::empty()
{
	return (root == nullptr);
}


FibonacciHeap::~FibonacciHeap()
{
}
