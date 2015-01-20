#include <iostream>
#include "ListS.h"
#include "ListP.h"
#include "StackP.h"
#include "QueueP.h"
#include "PointerBinTree.h"
#include "ListNTree.h"
#include "DynamicNTree.h"
#include "ListPriorityQueue.h"
#include "GrafoList.h"



int main(int argc, char** argv)
{
	using namespace std;

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

	

	GrafoList<string, double> G(10);

	NodoG n1, n2, n3, n4, n5, n6;

	G.insNodo(n1);
	G.scriviEtichetta(n1, "a");
	G.insNodo(n2);
	G.scriviEtichetta(n2, "b");
	G.insNodo(n3);
	G.scriviEtichetta(n3, "c");
	G.insNodo(n4);
	G.scriviEtichetta(n4, "d");
	G.insNodo(n5);
	G.scriviEtichetta(n5, "e");
	G.insNodo(n6);
	G.scriviEtichetta(n6, "f");



	G.insArco(n1, n2, 1.0);
	G.insArco(n1, n3, 0.9);
	G.insArco(n1, n5, 0.3);
	G.insArco(n2, n4, 0.1);
	G.insArco(n2, n6, 0.2);
	G.insArco(n3, n4, 1.0);
	G.insArco(n3, n6, 0.7);
	G.insArco(n4, n1, 0.5);
	G.insArco(n5, n2, 0.4);
	G.insArco(n5, n3, 0.2);
	G.insArco(n6, n4, 0.1);

	cout << "\nNumNodi " << G.numNodi();
	cout << "\nNumArchi " << G.numArchi();

	G.cancNodo(n6);

	cout << "\nNumNodi " << G.numNodi() << endl;

	GrafoList<string, double>::ListaNodi L = G.Adiacenti(n1);

	GrafoList<string, double>::ListaNodiPos p;
	GrafoList<string, double>::Arco a;

	a.nodo1 = n1;
	a.nodo2 = n4;

	cout << "Adiacenti di " << G.leggiEtichetta(n1).c_str() << "--> ";
	p = L.begin();
	while (!L.end(p)){
		cout << G.leggiEtichetta(*(L.read(p))).c_str() << " ";
		p = L.next(p);
	}
	cout << endl;
	auto arc = G.esisteArco(a);
	auto existnode = G.esisteNodo(*(new NodoG(5)));
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

	//pQ.Print();
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