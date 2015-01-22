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

#ifndef _STACKP_HEADER_
#define _STACKP_HEADER_

template <typename T> //Forward declaration
class StackP;

template <typename T>
std::ostream& operator<<(std::ostream&, StackP<T>&);

template <typename T>
class StackP
{
	struct ICell
	{
		T elem;
		ICell* next;
	};

	public:
		using iterator = ICell*;
		StackP();
		~StackP();
		bool IsEmpty() const;
		T& read() const;
		T& Pop();
		void Push(T);
		void Print();

	private:
		iterator head;
		int m_size;
		friend std::ostream& operator<< <>(std::ostream&,  StackP<T>&);


};

template <typename T>
StackP<T>::StackP()
{
	head = new ICell;
	head->next = head;
	m_size = 0;
}

template <typename T>
StackP<T>::~StackP()
{
	while (!this->IsEmpty())
	{
		this->Pop();
	}

	delete head;
}

template <typename T>
bool StackP<T>::IsEmpty() const
{
	return (m_size == 0);
}

template <typename T>
T& StackP<T>::read() const
{
	return head->next->elem;
}

template <typename T>
T& StackP<T>::Pop()
{
	iterator temp;
	T e;
	if (!this->IsEmpty())
	{
		temp = head->next;
		e = temp->elem;
		head->next = temp->next;
		m_size--;
		delete temp;
	}

	return e;
}

template <typename T>
void StackP<T>::Push(T e)
{
	iterator temp = new ICell;
	
	temp->elem = e;
	temp->next = head->next;
	head->next = temp;
	m_size++;
}

template <typename T>
void StackP<T>::Print()
{
	T e;

	if(!this->IsEmpty())
	{
		
		e = this->Pop();
		
		if (m_size >= 1)
		{
			std::cout << e << ",";
		}
		else
			std::cout << e << std::endl;

		this->Print();
		this->Push(e);
		
	}
	
}

template <typename T>
std::ostream& operator<<(std::ostream& os, StackP<T>& s)
{	
	s.Print();
	return os;
}

#endif