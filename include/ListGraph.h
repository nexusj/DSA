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

#ifndef _LISTGRAPH_HEADER_
#define _LISTGRAPH_HEADER_

#include "IGraph.h"


template <typename T, typename W>
struct IGraphNode
{
	private:
		T m_value;
		ListP<IEdge<IGraphNode<T,W>*,W>*>* m_neighbours;

	public:
		IGraphNode() : m_neighbours(new ListP<IEdge<IGraphNode<T,W>*, W>*>){}
		IGraphNode(T value) : m_value(value), m_neighbours(new ListP<IEdge<IGraphNode<T, W>*, W>*>) {}
		~IGraphNode()
		{
			for (auto& it = m_neighbours->begin(); !m_neighbours->end(it); it = m_neighbours->Next(it))
			{
				m_neighbours->RemoveAt(it);
			}

			delete m_neighbours;
		}

		T Value() const { return m_value; }
		void Value(T val) { m_value = val; }
		ListP<IEdge<IGraphNode<T,W>*, W>*> * Neighbours() const { return m_neighbours; }

		void AddNeighbour(IEdge<IGraphNode<T,W>*,W>* n)
		{
			m_neighbours->Add(n);
		}

		void RemoveNeighbour(IEdge<IGraphNode<T,W>*,W>* n)
		{
			m_neighbours->Remove(n);
		}
};


template <typename T, typename W>
class ListGraph : public IGraph < T, W, IGraphNode<T, W>* >
{
	public:
		using Node = IGraphNode<T, W>*;
		typedef typename IGraph::Weight Weight;
		typedef typename IGraph<T,W,Node>::Edge Edge;
		typedef ListP < Node>  ListNode;
		typedef ListP <Edge*> ListEdge;

		ListGraph();
		ListGraph(const ListGraph&);
		~ListGraph();
		void create();
		bool empty() const;
		void AddNode(Node);
		void AddEdge(Node, Node, Weight);
		void DeledeteNode(Node);
		void DeleteEdge(Node, Node);
		bool ExistNode(Node) const;
		bool ExistEdge(Node, Node) const;
		ListNode Neighbours(Node) const;
		ListNode Nodes() const;
		ListEdge Edges() const;
		T read(Node) const;
		void write(Node, T) const;
		Weight ReadWeight(Node, Node) const;
		void WriteWeight(Node, Node, Weight);
		int NodesCount() const;
		int EdgesCount() const;

	private:
		ListP <Node>* m_nodes;
		ListP <Edge*>* m_edges;
};

template <typename T, typename W>
ListGraph<T, W>::ListGraph()
{
	create();
}

template <typename T, typename W>
ListGraph<T, W>::~ListGraph()
{

	for (auto it = m_edges->begin(); !m_edges->end(it); it = m_edges->Next(it))
	{
		m_edges->RemoveAt(it);
	}

	for (auto it = m_nodes->begin(); !m_nodes->end(it); it = m_nodes->Next(it))
	{
		m_nodes->RemoveAt(it);
	}

	delete m_edges;
	delete m_nodes;
}

template <typename T, typename W>
void ListGraph<T, W>::create()
{
	m_nodes = new ListNode;
	m_edges = new ListEdge;
}

template <typename T, typename W>
bool ListGraph<T, W>::empty() const
{
	return m_nodes->IsEmpty();
}

template <typename T, typename W>
void ListGraph<T, W>::AddNode(Node n)
{
	if (!ExistNode(n))
		m_nodes->Add(n);
}

template <typename T, typename W>
void ListGraph<T, W>::AddEdge(Node a, Node b, Weight w)
{
	if (!ExistEdge(a,b))
	{
		Edge*  e = new Edge(a,b,w);
		m_nodes->Read(m_nodes->begin())->AddNeighbour(e);
		m_edges->Add(e);
	}
}

template <typename T, typename W>
void ListGraph<T, W>::DeledeteNode(Node n)
{
	
	if (ExistNode(n))
	{
		bool found = false;
		for (auto it = m_nodes->begin(); !m_nodes->end(it) && !found; it = m_nodes->Next(it))
		{
			if (m_nodes->Read(it) == n)
			{
				if (!m_nodes->Read(it)->Neighbours()->IsEmpty())
				{
					while (!m_nodes->Read(it)->Neighbours()->IsEmpty())
						m_nodes->Read(it)->Neighbours()->RemoveAt(m_nodes->Read(it)->Neighbours()->begin());
				}

				found = true;
			}
		}

		for (auto it = m_edges->begin(); !m_edges->end(it); it = m_edges->Next(it))
		{
			if (m_edges->Read(it)->Source() == n || m_edges->Read(it)->Destination() == n)
				m_edges->RemoveAt(it);
		}
		m_nodes->Remove(n);
	}
	
	
	

	
}

template <typename T, typename W>
void ListGraph<T, W>::DeleteEdge(Node a, Node b)
{
	bool found = false;
	
	if (ExistEdge(a,b))
	{

		for (auto it = m_edges->begin(); !m_edges->end(it) && !found; it = m_edges->Next(it))
		{
			if (m_edges->Read(it)->Source() == a &&  m_edges->Read(it)->Destination() == b)
			{
				found = true;
				m_edges->RemoveAt(it);
			}
				
		}
// 			for (auto it = a->Neighbours()->begin(); !a->Neighbours()->end(it) && !found ; it = a->Neighbours()->Next(it))
// 				{
// 					if (a->Neighbours()->Read(it)->Destination() == b)
// 					{
// 						found = true;
// 						m_edges->Remove(m_edges->Read(it));
// 						a->Neighbours()->RemoveAt(it);
// 						
// 					}
// 					
// 				}
			
	}

	
}


template <typename T, typename W>
bool ListGraph<T, W>::ExistNode(Node n) const 
{
	for (auto it = m_nodes->begin(); !m_nodes->end(it); it = m_nodes->Next(it))
		if (n == m_nodes->Read(it))
			return true;

	return false;
}


template <typename T, typename W>
bool ListGraph<T, W>::ExistEdge(Node a, Node b) const
{
	for (auto it = m_edges->begin(); !m_edges->end(it); it = m_edges->Next(it))
		if (a == m_edges->Read(it)->Source() && b == m_edges->Read(it)->Destination())
			return true;

	return false;
}


template <typename T, typename W>
typename ListGraph<T, W>::ListNode ListGraph<T, W>::Neighbours(Node n) const
{
	ListNode list;
	if (ExistNode(n))
	{
		bool found = false;
		for (auto it = m_nodes->begin(); !m_nodes->end(it) && !found; it = m_nodes->Next(it))
		{
			if (m_nodes->Read(it) == n)
			{
				if (!m_nodes->Read(it)->Neighbours()->IsEmpty())
				{
					auto head = m_nodes->Read(it)->Neighbours()->begin();
					while (!m_nodes->Read(it)->Neighbours()->end(head))
					{
						list.Add(m_nodes->Read(it)->Neighbours()->Read(head)->Destination());
						head = m_nodes->Read(it)->Neighbours()->Next(head);
					}

					found = true;	
				}
			}
		}
// 		for (auto& it = n->Neighbours()->begin(); !n->Neighbours()->end(it); it = n->Neighbours()->Next(it))
// 		{
// 			list.Add(n->Neighbours()->Read(it)->Destination());
// 		}
	}
	
	return list;
}

template <typename T, typename W>
typename ListGraph<T, W>::ListNode ListGraph<T, W>::Nodes() const
{
	return *m_nodes;
}

template <typename T, typename W>
typename ListGraph<T, W>::ListEdge ListGraph<T, W>::Edges() const
{
	return *m_edges;
}

template <typename T, typename W>
T ListGraph<T, W>::read(Node n) const
{
	if (ExistNode(n))
		for (auto it = m_nodes->begin(); !m_nodes->end(it); it = m_nodes->Next(it))
			if (m_nodes->Read(it) == n)
				return m_nodes->Read(it)->Value();
				
}

template <typename T, typename W>
void ListGraph<T, W>::write(Node n, T e) const
{
	if (ExistNode(n))
	{
		bool found = false;
		for (auto it = m_nodes->begin(); !m_nodes->end(it) && !found; it = m_nodes->Next(it))
		{
			if (m_nodes->Read(it) == n)
			{
				m_nodes->Read(it)->Value(e);
				found = true;
			}
				
		}
	}
}
	

template <typename T, typename W>
typename ListGraph<T, W>::Weight ListGraph<T, W>::ReadWeight(Node a, Node b) const
{
	
	
	if (ExistEdge(a,b))
	{
		for (auto it = m_edges->begin(); !m_edges->end(it); it = m_edges->Next(it))
			if (m_edges->Read(it)->Source() == a &&  m_edges->Read(it)->Destination() == b)
				return m_edges->Read(it)->Weight();
			
// 		for (; !a->Neighbours()->end(it); it = a->Neighbours()->Next(it))
// 			if (b == a->Neighbours()->Read(it)->Destination())
// 				return a->Neighbours()->Read(it)->Weight();
	}

	return 0xFF;
}

template <typename T, typename W>
void ListGraph<T, W>::WriteWeight(Node a, Node b, Weight w)
{
	bool found = false;
	if (ExistEdge(a, b))
	{

		for (auto it = m_edges->begin(); !m_edges->end(it); it = m_edges->Next(it))
			if (m_edges->Read(it)->Source() == a &&  m_edges->Read(it)->Destination() == b)
			{
				m_edges->Read(it)->Weight(w);
				found = true;
			}
				 
// 		for (auto it = a->Neighbours()->begin(); !a->Neighbours()->end(it) && !found; it = a->Neighbours()->Next(it))
// 			if (b == a->Neighbours()->Read(it)->Destination())
// 			{
// 				a->Neighbours()->Read(it)->Weight(w);
// 				found = true;
// 			}
	}
}

template <typename T, typename W>
int ListGraph<T, W>::NodesCount() const
{
	return m_nodes->Length();
}

template <typename T, typename W>
int ListGraph<T, W>::EdgesCount() const
{
	return m_edges->Length();
}

#endif