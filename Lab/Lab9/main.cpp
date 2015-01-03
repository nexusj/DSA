#include "Bin_treec.h"
#include "BinTree_Helper.h"
#include <iostream>

using namespace std;


int main(){
	Bin_treec<int> T;
	Bin_treec<int> Z;
	Bin_treec<int>::Nodo n1 = 0;
	Bin_treec<int>::Nodo n2 = 0;
	Bin_treec<int>::Nodo n3 = 0;
	Bin_treec<int>::Nodo n4 = 0;

	//Creazione primo albero 
	T.AddRoot();
	T.write(n1, 1);
	n1 = T.root();
	T.AddLeft(n1);
	T.AddRight(n1);
	T.write(T.left(n1), 2);
	n1 = T.right(n1);
	n3 = n1;
	T.write(n1, 3);
	T.AddRight(n1);
	T.write(T.right(n1), 4);
	T.print();
	//Creazione secondo albero
	Z.AddRoot(n2);
	Z.write(n2, 1);
	n2 = Z.root();
	Z.AddLeft(n2);
	Z.AddRight(n2);
	Z.write(Z.left(n2), 2);
	n2 = Z.right(n2);
	n4 = n2;
	Z.write(n2, 4);
	Z.AddRight(n2);
	Z.write(Z.right(n2), 3);
	Z.print();
	//Mutation tra i due alberi 
	mutation(T, n3, Z, n4);

	T.print();
	Z.print();


	//T.PreVisit(T.root());
	//cout << T; //equivale T.print(); grazie all'overloading dell'operatore
	system("pause");
	return 0;
}