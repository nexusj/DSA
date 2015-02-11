/***************************************************************************
*   Copyright (C) 2005 by Nicola Di Mauro                                 *
*   ndm@di.uniba.it                                                       *
*                                                                         *
*   This program is free software; you can redistribute it and/or modify  *
*   it under the terms of the GNU General Public License as published by  *
*   the Free Software Foundation; either version 2 of the License, or     *
*   (at your option) any later version.                                   *
*                                                                         *
*   This program is distributed in the hope that it will be useful,       *
*   but WITHOUT ANY WARRANTY; without even the implied warranty of        *
*   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the         *
*   GNU General Public License for more details.                          *
*                                                                         *
*   You should have received a copy of the GNU General Public License     *
*   along with this program; if not, write to the                         *
*   Free Software Foundation, Inc.,                                       *
*   59 Temple Place - Suite 330, Boston, MA  02111-1307, USA.             *
***************************************************************************/

#ifndef _BINTREE_H_
#define _BINTREE_H_
#include <iostream>

template <class T, class N>
class Bin_tree {
	

public:

	// tipi
	typedef T value_type;
	typedef N Nodo;

	// operatori
	virtual void create() = 0;
	virtual bool empty() const = 0;

	virtual Nodo root() const = 0;
	virtual Nodo parent(Nodo) const = 0;
	virtual Nodo left(Nodo) const = 0;
	virtual Nodo right(Nodo) const = 0;
	virtual bool EmptyLeft(Nodo) const = 0;
	virtual bool EmptyRight(Nodo) const = 0;

	virtual Bin_tree<T,N>& AddSubTree(Bin_tree<T,N>&,Bin_tree<T,N>&);
	virtual void erase(Nodo) = 0;

	virtual T read(Nodo) const = 0;
	virtual void write(Nodo, value_type) = 0;

	virtual void AddRoot() = 0;
	virtual void AddLeft(Nodo) = 0;
	virtual void AddRight(Nodo) = 0;

	// funzioni di servizio da implementare qui
	//virtual void previsit(Nodo);
	//virtual void invisita(Nodo);
	//virtual void postvisit(Nodo);

	virtual void print() const;

private:
	virtual void printSubTree(const Nodo) const;
	virtual void m_AddSubTree(Nodo,Nodo,Bin_tree<T,N>&);


};

template <class T, class N>
Bin_tree<T,N>& Bin_tree<T, N>::AddSubTree(Bin_tree<T, N>& t1, Bin_tree<T, N>& t2)
{
	
	Nodo n1 = t1.root(), n2 = t2.root();
	this->AddRoot();

	if (!t1.empty())
	{
		AddLeft(this->root());
		if (!t1.EmptyLeft(n1) || !t1.EmptyRight(n1))
			m_AddSubTree(n1, left(this->root()), t1);
	}
		

	if (!t2.empty())
	{
		AddRight(this->root());
		if (!t2.EmptyLeft(n2) || !t2.EmptyRight(n2))
			m_AddSubTree(n2, right(this->root()), t2);
	}
		

	return *this;
}



template <class T, class N>
void Bin_tree<T, N>::m_AddSubTree(Nodo u, Nodo v, Bin_tree<T, N>& t)
{


	if (!t.EmptyLeft(u))
	{
		this->AddLeft(v);
		m_AddSubTree(left(u), left(v), t);
	}


	if (!t.EmptyRight(u))
	{
		this->AddRight(v);
		m_AddSubTree(right(u), right(v), t);
	}
	

	this->write(v, t.read(u));

}


template <class T, class N>
void Bin_tree<T, N>::print() const{
	if (!empty())
		printSubTree(root());
	else
		std::cout << "[]" << std::endl;
	std::cout << std::endl;
}

template <class T, class N>
void Bin_tree<T, N>::printSubTree(const Nodo n) const{
	std::cout << "[" << read(n) << ", ";
	if (!EmptyLeft(n))
		printSubTree(left(n));
	else std::cout << "NIL";
	std::cout << ", ";
	if (!EmptyRight(n))
		printSubTree(right(n));
	else std::cout << "NIL";
	std::cout << " ]";
}

template<class T, class N>
std::ostream& operator<<(std::ostream& out, const Bin_tree<T, N>& t) {
	t.print();
	return out;
}





#endif /* _BINALBEROC_H_ */