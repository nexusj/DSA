#include "ListS.h"

int main(int argc, char** argv)
{
	

	ListS<int> t;

	t.Add(1);
	t.Add(2);
	t.Add(3);
	t.Add(4);
	t.Add(5);
	t.Add(6);
	t.RemoveAt(4);
	t.Add(10, 5);
	t.Add(3, 7);
	t[5] = 200;
	auto i = t[5];

	return 0;
}