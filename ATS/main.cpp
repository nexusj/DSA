#include <iostream>
#include "N-Queens.h"
#include "StringMatching.h"

int main(int _Argc, char ** _Argv)
{
	NQueens queen(10);

	std::string pattern, text;

	std::cout << "Inserire stringa testo: ";
	std::cin >> text;

	std::cout << "Inserire stringa pattern: ";
	std::cin >> pattern;

	

	std::cout << "Occorrenza trovata in posizione : " << CompareStrings(pattern, text) << std::endl;
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