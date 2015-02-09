#include <iostream>
#include "ListS.h"
#include "ListP.h"
#include "StackP.h"
#include "QueueP.h"
#include "PointerBinTree.h"
#include "ListNTree.h"
#include "DynamicNTree.h"
#include "ListPriorityQueue.h"
#include "TreePriorityQueue.h"
#include "ListGraph.h"
//#include "MatrixGraph.h"



int main(int argc, char** argv)
{
	using namespace std;
// 	MatrixGraph<int, double> mgraph(10);
// 	MatrixGraph<int, double>::NodePosition mn1(new IGraphNode<int, double>(2)), mn2(new IGraphNode<int, double>(3));
// 	mgraph.AddNode(mn1);
// 	mgraph.AddNode(mn2);
// 	mgraph.AddEdge(mn1, mn2, 1.2);
// 	mgraph.write(mn1, 55);
// 	auto mlist = mgraph.read(mn1);
	ListGraph<int, double> lgraph;
	ListGraph<int, double>::Node ln1(new IGraphNode<int, double>(2)), ln2(new IGraphNode<int, double>(3));
	lgraph.AddNode(ln1);
	lgraph.AddNode(ln2);
	lgraph.AddEdge(ln1, ln2, 2.3);
	auto rweight = lgraph.Neighbours(ln1);


	TreePriorityQueue<int, int> treeQueue(PriorityOrder::ASCENDING);

	treeQueue.Add(new IQueueNode<int, int>(0, 5));
	treeQueue.Add(new IQueueNode<int, int>(1, 10));
	treeQueue.Add(new IQueueNode<int, int>(2, 4));
	treeQueue.Add(new IQueueNode<int, int>(3, 8));
	treeQueue.Add(new IQueueNode<int, int>(4, 7));
	treeQueue.Add(new IQueueNode<int, int>(10, 10));
	treeQueue.Add(new IQueueNode<int, int>(20, 6));
	treeQueue.RemoveHighest();
	auto hgh = treeQueue.PullHighest();

	treeQueue.Print();
	std::cout << std::endl;

	DynamicNTree<int> dT;
	dT.AddRoot();
	dT.AddRoot();
	auto rt = dT.root();
	dT.WriteNode(rt, 1);
	dT.AddFirstChild(rt, 2);
	rt = dT.FirstChild(rt);
	dT.AddBrother(rt, 3);
	rt = dT.root();
	rt = dT.FirstChild(rt);
	dT.AddFirstChild(rt, 4);
	dT.AddFirstChild(rt, 5);
	dT.Print();


	DynamicNTree<int> tempDT;
	tempDT.AddRoot();
	auto temproot = tempDT.root();
	tempDT.WriteNode(temproot, 10);
	tempDT.AddFirstChild(temproot, 20);
	temproot = tempDT.FirstChild(temproot);
	tempDT.AddBrother(temproot, 30);

	tempDT.Print();

	
	dT.AddSubTree(rt, tempDT);
	dT.Print();
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

	nTree.AddSubTree(m, _tmp);
	nTree.Print();
	auto depth = nTree.Depth(nTree.root());
	PointerBinTree<int>::Node n;
	B.AddRoot();
	n = B.root();
	B.write(n, 1);
	B.AddLeft(n);
	B.AddRight(n);
	B.write(B.left(n), 2);
	B.AddLeft(B.left(n));
	B.write(B.left(B.left(n)), 4);
	B.AddRight(B.left(n));
	B.write(B.right(B.left(n)), 5);

	B.AddLeft(B.left(B.left(n)));
	B.write(B.left(B.left(B.left(n))),8);
	B.AddRight(B.left(B.left(n)));
	B.write(B.right(B.left(B.left(n))), 9);
	B.AddLeft(B.right(B.left(n)));
	B.write(B.left(B.right(B.left(n))), 10);
	B.AddRight(B.right(B.left(n)));
	B.write(B.right(B.right(B.left(n))), 11);

	B.write(B.right(n), 3);
	B.AddLeft(B.right(n));
	B.write(B.left(B.right(n)), 6);
	B.AddRight(B.right(n));
	B.write(B.right(B.right(n)), 7);

	B.AddLeft(B.left(B.right(n)));
	B.write(B.left(B.left(B.right(n))), 12);
	B.AddRight(B.left(B.right(n)));
	B.write(B.right(B.left(B.right(n))), 13);
	B.AddLeft(B.right(B.right(n)));
	B.write(B.left(B.right(B.right(n))), 14);
	B.AddRight(B.right(B.right(n)));
	B.write(B.right(B.right(B.right(n))), 15);


	std::cout << B;
	auto depthbin = B.Depth(B.root());
	auto breadth = B.Breadth(B.root());
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
	t.Add(1);
	t.Add(2);
	auto firstS = t.begin();
	firstS = t.Next(firstS);
	/*t.Add(2);
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