#include <iostream>
#include "ListS.h"
#include "ListP.h"


int main(int argc, char** argv)
{
	

	ListS<int> t;
	ListP<int> l;
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