#include <iostream>
#include "hashtable.h"


int main(int argc, char* argv[])
{
	hash_table<std::string, int> h(10);

	mypair<std::string, int> pairs;

	pairs.first = "a";
	pairs.second = 12;

	h.insert(pairs);

	pairs.first = "b";
	pairs.second = 20;

	h.insert(pairs);


	pairs.first = "c";
	pairs.second = 23;

	h.insert(pairs);
	h.Contains(20);
	
	auto i = h.Keys();
	std::cout << i[0] << std::endl;

	return 0;

}