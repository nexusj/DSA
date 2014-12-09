#ifndef _LISTVSTATIC_HEADER_
#define _LISTVSTATIC_HEADER_

#include <assert.h>
#include <exception>


const int BUFFER_SIZE = 100;



template<class T>
class ListS 
{

	struct ICell
	{
		T elem;
		int next;



	};

public:
	ListS();
	~ListS();
	using position = int;
	using iterator = ICell*;
	void Create();
	void Add(T e, position p);
	void Add(T e);
	void RemoveAt(position p);
	void Remove(T e);
	iterator begin() const;
	iterator end() const;
	bool IsEmpty() const;
	T& operator[](const int& v);
	const T& operator[](const int& v) const;
	void Sort();
	void Reverse();
	

private:
	static ICell m_buffer[BUFFER_SIZE];
	static iterator m_freeList;
	int m_size;
	int m_start;
	iterator GetFreeIndex(position&);
	iterator CheckPosition(position&);
	void Swap(T&, T&);
	iterator GetCellAt(position);
};


template<class T> typename ListS<T>::ICell ListS<T>::m_buffer[BUFFER_SIZE];
template<class T> typename ListS<T>::iterator ListS<T>::m_freeList;



template<class T>
ListS<T>::ListS()
{
	Create();
}


template<class T>
ListS<T>::~ListS()
{

}


template<class T>
void ListS<T>::Create()
{


	m_freeList = m_buffer;

	for (int i = 0; i < BUFFER_SIZE; i++)
		m_buffer[i].next = -1;

	m_buffer[BUFFER_SIZE - 1].next = -1;

	m_size = 0;
	
}


template<class T>
void ListS<T>::Add(T e, position p)
{
	if(p < 0 ||  p > BUFFER_SIZE)
		throw "Valore non ammesso !";

	static int index = 0;
	
	
	if (m_size == 0)
	{
		
		
		m_buffer[p-1].next = p ;
		m_buffer[p].next = -1;
		m_start = p-1;

	}
	else if (m_size < BUFFER_SIZE)
	{
		GetFreeIndex(index);

		iterator itnext = CheckPosition(p);
 		iterator iter = this->end();


		if (itnext != nullptr)
		{

			m_freeList->next = itnext->next;
			itnext->next = index;
			
		}
		else
		{
			iter->next = index;
			m_freeList->next = -1;
			
		}

	}

	m_freeList->elem = e;
	m_size++;

}

template<class T>
void ListS<T>::Add(T e)
{

	Add(e, m_size+1);
}

template<class T>
void ListS<T>::RemoveAt(position p)
{

	if (p < 0 || p > BUFFER_SIZE)
		throw "Valore non ammesso !";

	if (p == m_start)
	{
		m_start = m_buffer[m_start].next;
		m_buffer[p].next = -1;
		m_freeList = &m_buffer[p];
		

	}
	else
	{
		int _t, index = 1;
		
		ListS<T>::iterator iter = this->begin();
		iterator back = iter;

		for (; index < p && iter->next != -1; iter = &m_buffer[iter->next])
		{ 
			index++;
			back = iter;
		}

		if (index == p)
		{
			_t = iter->next;
			back->next = m_buffer[iter->next].next-1;
			iter->next = -1;
			m_freeList = &m_buffer[p];
			m_size--;
		}	
		
	}

	
	
}


template<class T>
void ListS<T>::Remove(T e)
{
	if (e == this->begin()->elem)
	{
		RemoveAt(m_start);
	}
	else
	{
		int _t;

		ListS<T>::iterator iter = this->begin();

		for (; m_buffer[iter->next].elem != e && iter->next != -1; iter = &m_buffer[iter->next])
		{
		}

		if (m_buffer[iter->next].elem == e)
		{
			_t = iter->next;
			iter->next = m_buffer[iter->next].next;
			m_buffer[_t].next = -1;
			m_freeList = &m_buffer[_t];
			m_size--;
		}
		
	}

	
}



template<class T>
typename ListS<T>::iterator ListS<T>::begin() const
{
	return &m_buffer[m_start];
}

template<class T>
typename ListS<T>::iterator ListS<T>::end() const
{
	iterator iter = this->begin();

	if (m_size > 1)
	{
		
		
		while (iter->next != -1)
		{
			
			iter = &m_buffer[iter->next];
			
		} 
		
			

	}
	
	return iter;
}

template<class T>
bool ListS<T>::IsEmpty() const
{
	return (m_size == 0);
}

template<class T>
T& ListS<T>::operator[](const int& v) 
{
	iterator it = this->begin();
	position index = m_start;

	for (; it->next != -1 && index <  v; it = &m_buffer[it->next])
	{
		index++;
	}
	return it->elem;
}

template <class T>
const T& ListS<T>::operator[](const int& v) const
{
	return const_cast<T&>(*this)[v];
}



template<class T>
void ListS<T>::Sort()
{
	iterator head = this->begin(),
		tend = this->end(),
		next = NULL,
		back = NULL;

	if (!this->IsEmpty() && m_size > 1)
	{
		for (; head != tend; head = &m_buffer[head->next])
		{
			next = &m_buffer[head->next];
			back = this->GetCellAt((next - m_buffer) - 1);

			while (next != this->begin() && back->elem > next->elem)
			{
				Swap(next->elem, back->elem);
				next = this->GetCellAt((next - m_buffer) - 1);
				back = this->GetCellAt((next - m_buffer) - 1);
			}
		}
	}
	
}



template<class T>
void ListS<T>::Reverse()
{
	iterator head = this->begin(),
		itend = this->end(),
		next = itend;
	T t;
	position i = m_size/2;

	if (!this->IsEmpty() && m_size > 1)
	{
		
		while (i > 0)
		{
			t = head->elem;
			head->elem = m_buffer[next - m_buffer].elem;
			next->elem = t;
			next = this->GetCellAt(next - m_buffer - 1);
			head = &m_buffer[head->next];
			i--;
		
		}
	}
	



}


template<class T>
typename ListS<T>::iterator ListS<T>::GetFreeIndex(position& v)
{
	iterator it = &m_buffer[v];
	iterator itend = this->end();

if (m_size > 1)
{
	if (it == itend || it->next != -1)
	{
		do
		{
			++it;

		} while (it->next != -1 && it != itend);

		v++;

		m_freeList = it;
	}
}
else
{
	v++;
	m_freeList += v;
}
	
	



		return m_freeList;

	
}


template<class T>
typename ListS<T>::iterator ListS<T>::CheckPosition(position& p)
{
	iterator iter = nullptr;
	iterator itend = this->end();
	position index = 1;

	if (m_size > 1 && p-1 < m_size)
	{
		iterator it = this->begin();
		iterator back = iter;

		while (index < p-1)
		{
			
			
			back = it;
			it = &m_buffer[it->next];
			++index;

		}

		
			iter = it;
		


	}
	else if (m_start == p)
			iter = itend;
	

	return iter;
}


template<class T>
void ListS<T>::Swap(T& a, T& b)
{
	T t = a;
	a = b;
	b = t;
}


template<class T>
typename ListS<T>::iterator ListS<T>::GetCellAt(position p)
{
	iterator it = this->begin();
	position i = m_start;

	for (; i++ < p; it = &m_buffer[it->next])
	{
	}

	return it;
}

#endif
