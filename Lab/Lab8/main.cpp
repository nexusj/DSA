#include <iostream>
#include "ChainedHashTable.h"


int main(int argc, char* argv[])
{
	ChainedHashTable<string, int> h(10);
	

	mypair<string, int> pairs;

	pairs.first = "a";
	pairs.second = 12;

	h.Add(pairs);
	

	pairs.first = "b";
	pairs.second = 20;

	h.Add(pairs);

	h.Remove("a");
	h.Modify("b", 12);

	pairs.first = "c";
	pairs.second = 23;

	h.Add(pairs);
	h.Contains(2);
	
	auto i = h.Keys();
	auto e = h.Values();
	
	std::cout << i[0] << std::endl;

	return 0;

}