#include "MultipleStack.h"

int main()
{
	MultipleStack<int> m(4);
	
	m.Push(4, 1);
	m.Push(6, 2);
	m.Print(2);
auto i =	m.Pop(1);
	std::cin.sync();
	std::cin.ignore();
	return 0;
}