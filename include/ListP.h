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
		T& Read(iterator&);
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
ListP<T>::ListP(const ListP<T>&)
{

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
T& ListP<T>::Read(iterator& it)
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