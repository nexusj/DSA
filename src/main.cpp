#include "ListS.h"
#include <cstdlib>
#include <ctime>

int main(int argc, char** argv)
{
	std::srand(std::time(0));

	ListS<int> t;

	/*t.Add(1);
	t.Add(2);
	t.Add(3);
	t.Add(4);
	t.Add(5);
	t.Add(6);
	t.Add(7);
	t.Reverse();*/
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
	auto i = t[5];

	return 0;
}