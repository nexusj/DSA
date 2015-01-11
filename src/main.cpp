#include <iostream>
#include "ListS.h"
#include "ListP.h"
#include "StackP.h"
#include "QueueP.h"
#include "PointerBinTree.h"
#include "ListNTree.h"
#include "ListPriorityQueue.h"



int main(int argc, char** argv)
{
	

	ListS<int> t;
	ListP<int> l;
	StackP<int> s;
	QueueP<int> q;
	PointerBinTree<int> B;
	ListNTree<int> nTree;
	ListNTree<int> _tmp;
	ListNTree<int>::Node m, _t;
	ListPriorityQueue<int, int> pQ(PriorityOrder::ASCENDING);
	IQueueNode<int, int> qn1(0, 10);
	IQueueNode<int, int> qn2(0, 4);

	
	pQ.Add(new IQueueNode<int, int>(0, 5));
	pQ.Add(new IQueueNode<int, int>(1, 10));
	pQ.Add(new IQueueNode<int, int>(2, 4));
	pQ.Add(new IQueueNode<int, int>(3, 8));
	pQ.Add(new IQueueNode<int, int>(4, 7));
	pQ.Add(new IQueueNode<int, int>(10, 10));
	pQ.Add(new IQueueNode<int, int>(20, 6));

	pQ.Print();
	_tmp.AddRoot();
	_t = _tmp.root();
	_tmp.WriteNode(_t, 10);
	_tmp.AddFirstChild(_t, 20);
	_t = _tmp.FirstChild(_t);
	_tmp.AddBrother(_t, 30);

	_tmp.Print();

	nTree.AddRoot();
	m = nTree.root();
	nTree.WriteNode(m, 1);
	nTree.AddFirstChild(m, 2);
	m = nTree.FirstChild(m);
	nTree.AddBrother(m, 3);
	m = nTree.root();
	m = nTree.FirstChild(m);
	nTree.AddFirstChild(m, 4);
	nTree.AddFirstChild(m, 5);
	nTree.Print();

	nTree.AddFirstSubTree(m, _tmp);
	nTree.Print();
	PointerBinTree<int>::Node n;
	B.AddRoot();
	n = B.root();
	B.write(n, 1);
	B.AddLeft(n);
	B.AddRight(n);
	B.write(B.left(n), 2);
	B.write(B.right(n), 3);

	std::cout << B;

	
	q.Push(1);
	q.Push(2);
	q.Push(3);
	q.Print();
	q.Print();

	s.Push(1);
	s.Push(2);
	s.Push(3);
	s.Print();
	std::cout << s;
	ListP<int>::iterator first = l.begin();
	l.Add(3, first);
	first = l.Next(first);
	l.Add(4, first);
	first = l.Next(first);
	l.Add(6, first);
	
	std::cout << l;
	
	l.Remove(4);
	std::cout << l;
	first = l.Next(first);
	l.Add(12);
	std::cout << l;
	/*t.Add(1);
	t.Add(2);
	t.Add(3);
	t.Add(4);
	t.Add(5);
	t.Add(6);
	t.Add(7);
	t.Reverse();
	t.Add(12);
	t.Add(2);
	t.Add(18);
	t.Add(14);
	t.Add(1);
	t.Add(23);
	t.Add(3);
	t.Sort();
	t.Remove(23);
	t.Add(10, 5);
	t.Add(3, 7);
	t[5] = 200;
	auto i = t[5];*/

	return 0;
}