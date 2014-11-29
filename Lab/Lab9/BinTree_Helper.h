template<class T>
void mutation(Bin_treec<T>& A, typename Bin_treec<T>::Nodo v,
	Bin_treec<T>& B, typename Bin_treec<T>::Nodo u){

	Bin_treec<T> swap;
	typename Bin_treec<T>::Nodo x = 0;

	if (!A.empty()){
		swap.ins_root(x);
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

	if (!A.sx_empty(v)){

		if (B.sx_empty(x))
			B.ins_sx(x);

		copy(A, A.sx(v), B, B.sx(x));
	}
	if (!A.dx_empty(v)){

		if (B.dx_empty(x))
			B.ins_dx(x);
		
		copy(A, A.dx(v), B, B.dx(x));
		
	}
}