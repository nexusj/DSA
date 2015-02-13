#include <iostream>
#include "N-Queens.h"
#include "StringMatching.h"
#include "Knapsack.h"

int main(int _Argc, char ** _Argv)
{
	

	Knapsack knsack(3);
	NQueens queen(10);
	std::string pattern, text;


	knsack.AddItem(*(new IData(6, 2)));
	knsack.AddItem(*(new IData(4, 1)));
	knsack.AddItem(*(new IData(7, 3)));

	knsack.KnapsackGreedy(5);

	
	std::cout << "//STRING MATCHING//" << std::endl << std::endl;
	

	std::cout << "Inserire stringa testo: ";
	std::cin >> text;

	std::cout << "Inserire stringa pattern: ";
	std::cin >> pattern;

	

	std::cout << "Occorrenza trovata in posizione : " << CompareStrings(pattern, text) << std::endl << std::endl;

	std::cout << "//N-QUEEN RESOLVER//" << std::endl << std::endl;

	if (queen.Start())
		queen.Print();
	else
		std::cout << "Configurazione non valida ";

	std::cout << std::endl;
	std::cout << "Premere un tasto per continuare ";

	std::cin.sync();
	std::cin.ignore();
	
	
	return 0;
}