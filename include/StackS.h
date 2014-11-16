/***************************************************************************
*   Copyright (C) 2005 by Nicola Di Mauro                                 *
*   ndm@ndm                                                               *
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
#ifndef StackS_H
#define StackS_H

#include <iostream>

using namespace std;


template <class Elemento>
class StackS
{
public:
	typedef Elemento tipoelem;
	StackS();
	StackS(int);
	~StackS();
	void creaStackS();
	bool IsEmpty() const;
	tipoelem& read() const;
	Elemento& Pop();
	void Push(tipoelem);
	void Print();

private:
	tipoelem *elementi;
	int MAXLUNGH;
	int testa;
};



template <class Elemento>
StackS<Elemento>::StackS()
{
	elementi = new tipoelem[100]; // dimensione standard della StackS
	MAXLUNGH = 100;
	creaStackS();
}

template <class Elemento>
StackS<Elemento>::StackS(int N)
{
	elementi = new tipoelem[N]; // dimensione N della StackS
	MAXLUNGH = N;
	creaStackS();
}

template <class Elemento>
StackS<Elemento>::~StackS()
{
	delete[] elementi;
}

template <class Elemento>
void StackS<Elemento>::creaStackS()
{
	testa = 0;
}

template <class Elemento>
bool StackS<Elemento>::IsEmpty() const
{
	return testa == 0;
}

template <class Elemento>
typename StackS<Elemento>::tipoelem& StackS<Elemento>::read() const
{
	return elementi[testa - 1];
}

template <class Elemento>
Elemento& StackS<Elemento>::Pop()
{
	int _t = testa;
	if (!IsEmpty())
	{
		
		testa -= 1;
		
	}
	else
	{
		cout << "nessun elemento nella StackS" << endl;
	}

	return elementi[_t - 1];
}

template <class Elemento>
void StackS<Elemento>::Push(tipoelem el)
{
	if (testa == MAXLUNGH)
	{
		cout << "raggiunta capacitÃ  massima della StackS" << endl;
	}
	else
	{
		elementi[testa] = el;
		testa++;
	}
}


template <class Elemento>
void StackS<Elemento>::Print()
{
	std::cout << elementi[testa - 1];
}

#endif // _StackSVT_H