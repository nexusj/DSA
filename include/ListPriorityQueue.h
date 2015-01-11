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

#ifndef _LISTPRIORITYQUEUE_HEADER_
#define _LISTPRIORITYQUEUE_HEADER_

#include "IPriorityQueue.h"
#include "ListP.h"


template <typename T,typename P>
class ListPriorityQueue : public IPriorityQueue <T,P>
{

	public:
		using NodeQ = IQueueNode<T,P>*;
		ListPriorityQueue(PriorityOrder);
		ListPriorityQueue(const ListPriorityQueue&);
		~ListPriorityQueue();
		void create(PriorityOrder);
		void Add(NodeQ);
		NodeQ PullHighest() const;
		void RemoveHighest();
		bool IsEmpty() const;

	private:
		ListP<NodeQ>* m_list;
		PriorityOrder m_order;
};

template <typename T, typename P>
ListPriorityQueue<T, P>::ListPriorityQueue(PriorityOrder order)
{
	create(order);
}

template <typename T, typename P>
ListPriorityQueue<T, P>::~ListPriorityQueue()
{

}

template <typename T, typename P>
void ListPriorityQueue<T, P>::create(PriorityOrder order)
{
	m_list = new ListP<IQueueNode<T,P>*>;
	m_order = order;
}

template <typename T, typename P>
void ListPriorityQueue<T, P>::Add(NodeQ q)
{
	ListP<ListPriorityQueue<T,P>::NodeQ>::iterator it = m_list->begin();
	 
	if (m_order == PriorityOrder::ASCENDING)
		while (!m_list->end(it) &&  *m_list->Read(it) < *q)
			it = m_list->Next(it);
	
	else if (m_order == PriorityOrder::DESCENDING)
		while (!m_list->end(it) && *m_list->Read(it) > *q)
			it = m_list->Next(it);
	
	
	
	m_list->Add(q, it);
}

template <typename T, typename P>
typename ListPriorityQueue<T,P>::NodeQ ListPriorityQueue<T, P>::PullHighest() const
{
	return m_list->Read(m_list->begin());
}

template <typename T, typename P>
void ListPriorityQueue<T, P>::RemoveHighest()
{
	return m_list->RemoveAt(m_list->begin());
}


template <typename T, typename P>
bool ListPriorityQueue<T, P>::IsEmpty() const
{
	return(m_list->IsEmpty());
}

#endif