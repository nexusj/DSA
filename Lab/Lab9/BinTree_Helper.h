template<class T>
void mutation(Bin_treec<T>& A, typename Bin_treec<T>::Nodo v,
	Bin_treec<T>& B, typename Bin_treec<T>::Nodo u){

	Bin_treec<T> swap;
	typename Bin_treec<T>::Nodo x = 0;

	if (!A.empty()){
		swap.AddRoot(x);
		copy(A, v, swap, x);
		//A.erase(v);
		swap.print();
		A.print();
		copy(B, u, A, v);
		//B.erase(u);
		copy(swap, x, B, u);
		
	}
}


template<class T>
void copy(Bin_treec<T>& A, typename Bin_treec<T>::Nodo v,
	Bin_treec<T>& B, typename Bin_treec<T>::Nodo x){

	B.write(x, A.read(v));

	if (!A.EmptyLeft(v)){

		if (B.EmptyLeft(x))
			B.AddLeft(x);

		copy(A, A.left(v), B, B.left(x));
	}
	if (!A.EmptyRight(v)){

		if (B.EmptyRight(x))
			B.AddRight(x);
		
		copy(A, A.right(v), B, B.right(x));
		
	}
}