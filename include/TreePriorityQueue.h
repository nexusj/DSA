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

#ifndef _TREEPRIORITYQUEUE_HEADER_
#define  _TREEPRIORITYQUEUE_HEADER_


#include "IPriorityQueue.h"
#include "PointerBinTree.h"


template <typename T,typename P>
class TreePriorityQueue : public IPriorityQueue <T,P>
{
	public:
		using NodeQ = IQueueNode<T, P>*;
		TreePriorityQueue(PriorityOrder);
		TreePriorityQueue(const TreePriorityQueue&);
		~TreePriorityQueue();
		void create(PriorityOrder);
		void Add(NodeQ);
		NodeQ PullHighest() const;
		void RemoveHighest();
		bool IsEmpty() const;

	private:
		PointerBinTree<NodeQ> *m_tree;
		typename PointerBinTree<NodeQ>::Node m_last;
		PriorityOrder m_order;
		void Swap(NodeQ, NodeQ);
		void Copy(NodeQ, NodeQ);
		
			
};

template <typename T, typename P>
TreePriorityQueue<T, P>::TreePriorityQueue(PriorityOrder order)
{
	create(order);
}

template <typename T, typename P>
TreePriorityQueue<T, P>::~TreePriorityQueue()
{
	while (!this->IsEmpty())
		this->RemoveHighest();

	delete m_tree;
}

template <typename T, typename P>
void TreePriorityQueue<T, P>::create(PriorityOrder order)
{
	m_order = order;
	m_tree = new PointerBinTree<IQueueNode<T, P>*>;
	
}

template <typename T, typename P>
void TreePriorityQueue<T, P>::Add(NodeQ q)
{
	PointerBinTree<IQueueNode<T, P>*>::Node n;
	PointerBinTree<IQueueNode<T, P>*>::Node p;

	if (m_tree->empty())
	{	
		m_tree->AddRoot();
		n = m_tree->root();
		m_tree->write(n, q);
		m_last = m_tree->root();
	}
	else if (m_last == m_tree->root())
	{
		m_tree->AddLeft(m_last);
		n = m_tree->left(m_last);
		m_tree->write(n, q);
		
	}
	else if (m_last == m_tree->left(m_tree->parent(m_last)))
	{
		m_tree->AddRight(m_tree->parent(m_last));
		n = m_tree->right(m_tree->parent(m_last));
		m_tree->write(n, q);
	}
	else
	{
	    n = m_last;
		p = m_tree->parent(n);

		while (m_tree->right(p) == n && n != m_tree->root())
		{
			n = p;
			p = m_tree->parent(n);	
		}

		if (n != m_tree->root())
			n = m_tree->right(p);

		while (!m_tree->EmptyLeft(n))
		{
			n = m_tree->left(n);
		}

		m_tree->AddLeft(n);
		n = m_tree->left(n);
		m_tree->write(n, q);
		
	}

	m_last = n;
	p = m_tree->parent(n);

	while (n != m_tree->root() && (m_order == PriorityOrder::ASCENDING ? *m_tree->read(n) < *m_tree->read(p) : 
		   *m_tree->read(n) > *m_tree->read(p)))
	{
		
		
		Swap(m_tree->read(n), m_tree->read(p));
		n = p;
		p = m_tree->parent(n);
	}
}

template <typename T, typename P>
typename TreePriorityQueue<T,P>::NodeQ TreePriorityQueue<T, P>::PullHighest() const
{
	return m_tree->read(m_tree->root());
}

template <typename T, typename P>
void TreePriorityQueue<T, P>::RemoveHighest()
{
	PointerBinTree<IQueueNode<T, P>*>::Node n;
	PointerBinTree<IQueueNode<T, P>*>::Node p;
	auto temp = m_tree->parent(m_last);

	if (!m_tree->empty())
	{
		if (m_last == m_tree->root())
			m_tree->erase(m_tree->root());
		else
		{
			n = m_tree->root();
			Copy(m_tree->read(n), m_tree->read(m_last));
			
			if (m_last == m_tree->right(temp))
			{
				m_tree->erase(m_last);
				m_last = m_tree->left(temp);
			}

			else
			{
				n = m_last;
				p = m_tree->parent(n);

				while (m_tree->left(p) == n)
				{
					n = p;
					p = m_tree->parent(n);
				}

				if (n != m_tree->root())
					n = m_tree->left(p);

				while (!m_tree->EmptyRight(n))
				{
					n = m_tree->right(n);
				}

				m_tree->erase(m_last);
				m_last = n;
			}

			n = m_tree->root();

			while (!m_tree->EmptyLeft(n) && !m_tree->EmptyRight(n) && (m_order == PriorityOrder::ASCENDING ? !(*m_tree->read(n) < *m_tree->read(m_tree->left(n)) && *m_tree->read(n) < *m_tree->read(m_tree->right(n))) :
				(*m_tree->read(n) > *m_tree->read(m_tree->left(n)) || *m_tree->read(n) > *m_tree->read(m_tree->right(n)))))
			{
				if (!m_tree->EmptyLeft(n) && !m_tree->EmptyRight(n))
				{

					switch (m_order)
					{
					case PriorityOrder::ASCENDING:
						n = *m_tree->read(m_tree->left(n)) < *m_tree->read(m_tree->right(n)) ? m_tree->left(n) : m_tree->right(n);
						break;
					case PriorityOrder::DESCENDING:
						n = *m_tree->read(m_tree->left(n)) > *m_tree->read(m_tree->right(n)) ? m_tree->left(n) : m_tree->right(n);
						break;
					default:
						break;
					}
				}
				else
					n = m_tree->left(n);

				Swap(m_tree->read(n), m_tree->read(m_tree->parent(n)));

			}
		}

		
	}


}

template <typename T, typename P>
bool TreePriorityQueue<T, P>::IsEmpty() const
{
	return m_tree->empty();
}


template <typename T, typename P>
void TreePriorityQueue<T, P>::Swap(NodeQ a, NodeQ b)
{
	a->swap(*b);
}


template <typename T, typename P>
void TreePriorityQueue<T, P>::Copy(NodeQ a, NodeQ b)
{
	a->copy(*b);
}

#endif