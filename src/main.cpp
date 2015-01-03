#include <iostream>
#include "ListS.h"
#include "ListP.h"
#include "StackP.h"
#include "QueueP.h"
#include "PointerBinTree.h"



int main(int argc, char** argv)
{
	

	ListS<int> t;
	ListP<int> l;
	StackP<int> s;
	QueueP<int> q;
	PointerBinTree<int> B;

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