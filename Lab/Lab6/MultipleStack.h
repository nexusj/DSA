#ifndef _H_MULTIPLESTACK_
#define  _H_MULTIPLESTACK_

#include "list_vector.h"
#include "Pilavt.h"

template <typename T>
class MultipleStack
{

public:
	MultipleStack(unsigned int);
	~MultipleStack();
	void Push(const T& , unsigned int);
	T& Pop(unsigned int);
	void Print(unsigned int);
private:
	List_vector<StackS<T>*> *m_stack;

};


template <typename T>
MultipleStack<T>::MultipleStack(unsigned int n)
{
	m_stack = new List_vector<StackS<T>*>(n);

	for (int i = 0; i < n; i++)
	{
		m_stack->insert(new StackS<T>, i);
	}
	

}



template <typename T>
MultipleStack<T>::~MultipleStack()
{
	
		delete m_stack;
	
}



template <typename T>
void MultipleStack<T>::Push(const T& e, unsigned int n)
{
	
	m_stack->read(n)->Push(e);
	
}



template <typename T>
T& MultipleStack<T>::Pop(unsigned int n)
{
	return m_stack->read(n)->Pop();
	
}



template <typename T>
void MultipleStack<T>::Print(unsigned int n)
{
	m_stack->read(n)->Print();
	
}

#endif // !_H_MULTIPLESTACK_
