#include "ListS.h"

int main(int argc, char** argv)
{
	

	ListS<int> t;

	t.Add(5, 0);
	t.Add(2, 1);
	t.Add(6, 4);
	
	t.Add(8, 7);
	t.RemoveAt(4);
	t.Add(10, 5);
	auto i = t[1];

	return 0;
}