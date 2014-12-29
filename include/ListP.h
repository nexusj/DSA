// The MIT License(MIT)
// 
// Copyright(c) 2014 Vito Palumbo
// 
// Permission is hereby granted, free of charge, to any person obtaining a copy
// of this software and associated documentation files(the "Software"), to deal
// in the Software without restriction, including without limitation the rights
// to use, copy, modify, merge, publish, distribute, sublicense, and / or sell
// copies of the Software, and to permit persons to whom the Software is
// furnished to do so, subject to the following conditions :
// 
// The above copyright notice and this permission notice shall be included in all
// copies or substantial portions of the Software.
// 
// THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
// IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
// FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT.IN NO EVENT SHALL THE
// AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
// LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
// OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
// SOFTWARE.

#ifndef _LISTP_HEADER_
#define _LISTP_HEADER_


#include <iostream>

template <typename T>
class ListP;

template <typename T>
std::ostream& operator<<(std::ostream&, const ListP<T>&);

template <typename T>
class ListP
{
	struct ICell
	{
		T elem;
		ICell* next;
	};

	public:
		using iterator = ICell*;
		ListP();
		ListP(const ListP<T>&);
		~ListP();
		void Add(T, iterator&);
		void Add(T);
		void RemoveAt(iterator&);
		void Remove(const T&);
		iterator begin() const;
		bool end(iterator&) const;
		bool IsEmpty() const;
		iterator Next(iterator&) const;
		T& Read(iterator&) const;
		T& operator[](const int& v);
		const T& operator[](const int& v) const;
		



	private:
		iterator list;
		int m_size;
		friend std::ostream& operator<< <>(std::ostream&, const ListP<T>&);


};




template <typename T>
ListP<T>::ListP()
{
	list = new ICell;
	list->next = list;
	m_size = 0;

}

template <typename T>
ListP<T>::ListP(const ListP<T>& l)
{
	list = new ICell;
	list->next = list;

	m_size = l.m_size;

	iterator it = l.begin();

	while (!l.end(it))
	{
		this->Add(l.Read(it));
		it = l.Next(it);
	}
}

template <typename T>
ListP<T>::~ListP()
{
	delete list;
}


template <typename T>
void ListP<T>::Add(T e , iterator& it)
{
	iterator temp = new ICell;

	temp->elem = e;

	temp->next = it->next;
	it->next = temp;
	//it = temp;  possibile pila se abilitato.
	m_size++;

}


template <typename T>
void ListP<T>::Add(T e)
{
	iterator it = this->begin();
	iterator temp = it;

	for (; !this->end(it); it = this->Next(it))
	{
		temp = it;
	}

	this->Add(e, temp);
}


template <typename T>
void ListP<T>::RemoveAt(iterator& it)
{
	iterator temp;
	iterator target = this->begin();

	for (; target->next != it; target = this->Next(target))
	{
	}

	temp = target->next;
	target->next = it->next;
	it = target->next;
	delete temp;

	m_size--;


}


template <typename T>
void ListP<T>::Remove(const T& e)
{
	iterator it = this->begin();
	iterator temp = it;

	for (; !this->end(it); temp = this->Next(temp))
	{
		
		if (it->elem == e)
		{
			this->RemoveAt(it);
		}
		it = temp;
	}
}



template <typename T>
typename ListP<T>::iterator ListP<T>::begin() const
{
	return list->next;
}


template <typename T>
bool ListP<T>::end(iterator& it) const
{
	return (it == list);
}



template <typename T>
bool ListP<T>::IsEmpty() const
{
	return (m_size == 0);
}



template <typename T>
typename ListP<T>::iterator ListP<T>::Next(iterator& it) const
{
	return it->next;
}



template <typename T>
T& ListP<T>::Read(iterator& it) const
{
	return it->elem;
}



template <typename T>
T& ListP<T>::operator[](const int& v)
{
	iterator it = this->begin();
	int i = 0;

	for (; i < v; it = this->Next(it))
	{
		i++;
	}

	return it->elem;
}


template <typename T>
const T& ListP<T>::operator[](const int& v) const
{
	return const_cast<T&>(*this)[v];
}

template <typename T>
std::ostream& operator<<(std::ostream& os, const ListP<T>& l)
{
	ListP<T>::iterator it = l.begin();
	std::cout << "[ ";

	while (!l.end(it))
	{
		if (it != l.begin())
		{
			std::cout << ", " << it->elem;
		}
		else
			std::cout << it->elem;


		it = l.Next(it);
	}

	std::cout << " ]" << std::endl;

	return os;
}

#endif