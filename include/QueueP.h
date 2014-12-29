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

#ifndef _QUEUEP_HEADER_
#define _QUEUEP_HEADER_

template <typename T>
class QueueP
{
	struct ICell
	{
		T elem;
		ICell* next;
	};

	public:
		using iterator = ICell*;
		QueueP();
		~QueueP();
		bool IsEmpty() const;
		T& Head() const;
		T& Tail() const;
		T& Pop();
		void Push(T);
		void Print();

	private:
		iterator head, tail;
		int m_size;
};

template <typename T>
QueueP<T>::QueueP()
{
	head = new ICell;
	tail = new ICell;

	head->next = head;
	tail->next = head;

	m_size = 0;
}

template <typename T>
QueueP<T>::~QueueP()
{
	while (!this->IsEmpty())
	{
		this->Pop();
	}

	delete tail;
	delete head;
}

template <typename T>
bool QueueP<T>::IsEmpty() const
{
	return(m_size == 0);
}

template <typename T>
T& QueueP<T>::Head() const
{
	return head->next->elem;
}

template <typename T>
T& QueueP<T>::Tail() const
{
	return tail->next->elem;
}

template <typename T>
T& QueueP<T>::Pop()
{
	iterator temp;
	T e;

	if (!this->IsEmpty())
	{
		temp = head->next;
		e = temp->elem;
		head->next = temp->next;
		m_size--;
		m_size == 0 ? tail->next = head : tail->next = tail->next;
		delete temp;
	}

	return e;
}

template <typename T>
void QueueP<T>::Push(T e)
{
	iterator temp = new ICell;
	iterator next = tail->next;

	temp->elem = e;
	temp->next = head;
	tail->next = temp;
	next->next = temp;
	m_size++;
}

template <typename T>
void QueueP<T>::Print()
{
	QueueP<T> q;
	
	while(!this->IsEmpty())
	{
		if (m_size > 1)
		{
			std::cout << this->Head() << ",";
		}
		else
			std::cout << this->Head() << std::endl;

		q.Push(this->Pop());
	}

	while (!q.IsEmpty())
	{
		this->Push(q.Pop());
	}
}

#endif