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
	T.ins_root(n1);
	T.write(n1, 1);
	n1 = T.root();
	T.ins_sx(n1);
	T.ins_dx(n1);
	T.write(T.sx(n1), 2);
	n1 = T.dx(n1);
	n3 = n1;
	T.write(n1, 3);
	T.ins_dx(n1);
	T.write(T.dx(n1), 4);
	T.print();
	//Creazione secondo albero
	Z.ins_root(n2);
	Z.write(n2, 1);
	n2 = Z.root();
	Z.ins_sx(n2);
	Z.ins_dx(n2);
	Z.write(Z.sx(n2), 2);
	n2 = Z.dx(n2);
	n4 = n2;
	Z.write(n2, 4);
	Z.ins_dx(n2);
	Z.write(Z.dx(n2), 3);
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