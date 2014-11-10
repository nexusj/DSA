#ifndef _LISTS_HEADER_
#define _LISTS_HEADER_

#include <assert.h>
#include <exception>


const int BUFFER_SIZE = 100;



template<class T>
class ListS 
{

	struct IBufferStack
	{
		T elem;
		int succ;



	};

public:
	ListS();
	ListS(const ListS& l);
	~ListS();
	typedef T ldata;
	using position = int;
	using iterator = IBufferStack*;
	void Create();
	void Add(ldata e, position p);
	void Add(ldata e);
	void RemoveAt(position p);
	void Remove(T e);
	IBufferStack* GetStruct() const;
	iterator begin() const;
	iterator end() const;
	bool IsEmpty() const;
	T& operator[](const int& v);
	const T& operator[](const int& v) const;
	
	

private:
	static IBufferStack s_stack[100];
	static IBufferStack* m_freeList;
	int m_size;
	int m_start;
	iterator GetFreeIndex(position&);
	iterator CheckPosition(position&);
};



template<class T> typename ListS<T>::IBufferStack ListS<T>::s_stack[100];
template<class T> typename ListS<T>::IBufferStack* ListS<T>::m_freeList;

template<class T>
typename ListS<T>::IBufferStack* ListS<T>::GetStruct() const
{
	return s_stack;
}







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
ListS<T>::ListS(const ListS& l)
{
	




}

template<class T>
void ListS<T>::Create()
{


	m_freeList = s_stack;

	for (int i = 0; i < BUFFER_SIZE; i++)
		s_stack[i].succ = -1;

	s_stack[BUFFER_SIZE - 1].succ = -1;

	m_size = 0;
	
}


template<class T>
void ListS<T>::Add(ldata e, position p)
{
	if(p < 0 ||  p > BUFFER_SIZE)
		throw "Valore non ammesso !";

	static int index = 0;
	
	
	if (m_size == 0)
	{
		
		
		s_stack[p-1].succ = p ;
		s_stack[p].succ = -1;
		m_start = p-1;

	}
	else if (m_size < BUFFER_SIZE)
	{
		GetFreeIndex(index);

		iterator next = CheckPosition(p);
 		iterator iter = this->end();


		if (next != nullptr)
		{

			m_freeList->succ = next->succ;
			next->succ = index;
			
			/*
			if (p >= iter->succ)
			{

			s_stack[iter->succ].succ = p;

			s_stack[p].succ = -1;


			}
			else
			{

			//next->succ = -1;
			s_stack[p].succ = iter->succ;
			iter->succ = p;

			}

			s_stack[p].elem = e;
			}
			else
			{
			m_freeList->succ = next->succ;
			next->succ = index;

			//m_freeList->elem = e;

			}*/


		}
		else
		{
			iter->succ = index;
			m_freeList->succ = -1;
			
		}

	}

	m_freeList->elem = e;
	m_size++;

}

template<class T>
void ListS<T>::Add(ldata e)
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
		m_start = s_stack[m_start].succ;
		s_stack[p].succ = -1;
		m_freeList = &s_stack[p];
		

	}
	else
	{
		int _t, index = 1;
		
		ListS<T>::iterator iter = this->begin();
		iterator back = iter;

		for (; index < p && iter->succ != -1; iter = &s_stack[iter->succ])
		{ 
			index++;
			back = iter;
		}

		if (index == p)
		{
			_t = iter->succ;
			back->succ = s_stack[iter->succ].succ-1;
			iter->succ = -1;

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

		for (; s_stack[iter->succ].elem != e && iter->succ != -1; iter = &s_stack[iter->succ])
		{
		}

		if (s_stack[iter->succ].elem == e)
		{
			_t = iter->succ;
			iter->succ = iter[iter->succ].succ;
			iter[_t].succ = -1;

			m_size--;
		}
		
	}

	
}



template<class T>
typename ListS<T>::iterator ListS<T>::begin() const
{
	return &s_stack[m_start];
}

template<class T>
typename ListS<T>::iterator ListS<T>::end() const
{
	iterator iter = this->begin();

	if (m_size > 1)
	{
		
		
		while (iter->succ != -1)
		{
			
			iter = &s_stack[iter->succ];
			
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
	int index = m_start;

	for (; it->succ != -1 && index <= v-1; it = &s_stack[it->succ])
	{
		index = it->succ;
	}
	return s_stack[index].elem;
}

template <class T>
const T& ListS<T>::operator[](const int& v) const
{
	return const_cast<T&>(*this)[v];
}

template<class T>
typename ListS<T>::iterator ListS<T>::GetFreeIndex(position& v)
{
	iterator it = &s_stack[v];
	iterator itend = this->end();

if (m_size > 1)
{
	if (it == itend || it->succ != -1)
	{
		do
		{
			++it;

		} while (it->succ != -1 && it != itend);

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
	int index = 1;

	if (m_size > 1 && p-1 < m_size)
	{
		iterator it = this->begin();
		iterator back = iter;

		while (index < p-1)
		{
			
			
			back = it;
			it = &s_stack[it->succ];
			++index;

		}

		
			iter = it;
		


	}
	else if (m_start == p)
			iter = itend;
	

	return iter;
}

#endif
