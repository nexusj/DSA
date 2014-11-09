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
#ifndef PILAVT_H
#define PILAVT_H

#include <iostream>

using namespace std;


template <class Elemento>
class Pila
{
public:
	typedef Elemento tipoelem;
	Pila();
	Pila(int);
	~Pila();
	void creaPila();
	bool pilaVuota() const;
	tipoelem& leggiPila() const;
	Elemento& fuoriPila();
	void inPila(tipoelem);
	void Print();

private:
	tipoelem *elementi;
	int MAXLUNGH;
	int testa;
};



template <class Elemento>
Pila<Elemento>::Pila()
{
	elementi = new tipoelem[100]; // dimensione standard della pila
	MAXLUNGH = 100;
	creaPila();
}

template <class Elemento>
Pila<Elemento>::Pila(int N)
{
	elementi = new tipoelem[N]; // dimensione N della pila
	MAXLUNGH = N;
	creaPila();
}

template <class Elemento>
Pila<Elemento>::~Pila()
{
	delete[] elementi;
}

template <class Elemento>
void Pila<Elemento>::creaPila()
{
	testa = 0;
}

template <class Elemento>
bool Pila<Elemento>::pilaVuota() const
{
	return testa == 0;
}

template <class Elemento>
typename Pila<Elemento>::tipoelem& Pila<Elemento>::leggiPila() const
{
	return elementi[testa - 1];
}

template <class Elemento>
Elemento& Pila<Elemento>::fuoriPila()
{
	int _t = testa;
	if (!pilaVuota())
	{
		
		testa -= 1;
		
	}
	else
	{
		cout << "nessun elemento nella pila" << endl;
	}

	return elementi[_t - 1];
}

template <class Elemento>
void Pila<Elemento>::inPila(tipoelem el)
{
	if (testa == MAXLUNGH)
	{
		cout << "raggiunta capacit�  massima della pila" << endl;
	}
	else
	{
		elementi[testa] = el;
		testa++;
	}
}


template <class Elemento>
void Pila<Elemento>::Print()
{
	std::cout << elementi[testa - 1];
}

#endif // _PILAVT_H