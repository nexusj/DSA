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
// 

#ifndef _IPRIORITYQUEUE_HEADER_
#define  _IPRIORITYQUEUE_HEADER_



enum class PriorityOrder
{
	ASCENDING,
	DESCENDING
};

template <typename T, typename P>
class IQueueNode
{
	private:
		T m_value;
		P m_priority;
		
	public:
		IQueueNode();
		IQueueNode(T _value, P _priority) : m_value(_value), m_priority(_priority) {}
		T Value() const { return m_value; }
		void Value(T val) { m_value = val; }
		P Priority() const { return m_priority; }
		void Priority(P val) { m_priority = val; }

		IQueueNode& operator=(const IQueueNode& other)
		{
			if (this != &other)
			{
				m_value = other.m_value;
				m_priority = other.m_priority;
			}
			return *this;
		}
		IQueueNode& operator=(IQueueNode&& other)
		{
			if (this != &other)
			{
				m_value = other.m_value;
				m_priority = other.m_priority;
			}
			return *this;
		}
		bool operator==( const IQueueNode& rhs)
		{
			return (m_value == rhs.m_value && m_priority == rhs.m_value);
		}

		bool operator!=(const IQueueNode& rhs)
		{
			return !(this== rhs);
		}

		bool operator<(IQueueNode<T,P>& other) const
		{
			return (m_priority < other.m_priority);
		}

		bool operator>(IQueueNode<T,P>& other)
		{
			return (other.m_priority < m_priority);
		}

	
		bool operator<=( const IQueueNode& rhs)
		{
			return !(this->m_priority > rhs.m_priority);
		}

		bool operator>=( const IQueueNode& rhs)
		{
			return !(this->m_priority < rhs.m_priority);
		}

	    void swap(IQueueNode<T,P>& b)
		{
			using std::swap;
			swap(this->m_priority, b.m_priority);
			swap(this->m_value, b.m_value);
		}

		void copy(IQueueNode<T, P>& b)
		{
			*this = b;
		}
};

template <typename T, typename P>
class IPriorityQueue
{
	public:
		using NodeQ = IQueueNode<T, P>*;
		virtual void create(PriorityOrder) = 0;
		virtual void Add(NodeQ) = 0;
		virtual NodeQ PullHighest() const = 0;
		virtual void RemoveHighest() = 0;
		virtual bool IsEmpty() const = 0;
		virtual void Print() ;
};

template <typename T, typename P>
void IPriorityQueue<T, P>::Print() 
{
	if (!this->IsEmpty())
	{
		auto e = *this->PullHighest();
		RemoveHighest();
		std::cout << e.Value() << " ";
		Print();
		this->Add(new IQueueNode<T,P>(e));
	}
}


#endif