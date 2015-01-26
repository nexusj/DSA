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

#ifndef _MATRIXGRAPH_HEADER_
#define _MATRIXGRAPH_HEADER_

#include "IGraph.h"

template<typename N, typename W>
struct IMEdge : public IEdge < N, W >
{
	private:
		bool m_empty;
		
	public:
		IMEdge() : m_empty(true){}
		IMEdge(N source, N destination, W weight) : IEdge(source, destination, weight), m_empty(false) {}
		IMEdge<N, W>& operator=(const IMEdge<N, W>& rhs)
		{
			if (this != &rhs)
			{
				this->Source(rhs.Source());
				this->Destination(rhs.Destination());
				this->Empty(rhs.Empty());
				this->Weight(rhs.Weight()) ;
			}

			return *this;
		}
		bool Empty() const { return m_empty; }
		void Empty(bool val) { m_empty = val; }
};
template <typename T, typename W>
struct IGraphNode
{
	private:
		T m_value;
		bool m_empty;
		int m_id;
		
		
		

	public:
		IMEdge<IGraphNode<T, W>*, W>* m_neighbours;
		IGraphNode() : m_empty(true), m_id(0XFF) {}
		IGraphNode(T value) : m_value(value), m_empty(true){}
		~IGraphNode() { delete[] m_neighbours; }
		IGraphNode<T,W>& operator=(const IGraphNode<T, W>& other)
		{
			if (this != &other)
			{
				this->m_value = other.m_value;
				this->m_id = other.m_id;
				this->m_empty = other.m_empty;
				
			}

			return *this;
		}
		bool operator==(const IGraphNode<T, W>& rhs)
		{
			return (this->m_id == rhs.m_id);
		}

// 		bool operator!=(const IGraphNode<T, W>& rhs)
// 		{
// 			return !(this == rhs);
// 		}
		T Value() const { return m_value; }
		void Value(T val) { m_value = val; }
		int Id() const { return m_id; }
		void Id(int val) { m_id = val; }
		bool Empty() const { return m_empty; }
		void Empty(bool val) { m_empty = val; }
		

		IMEdge<IGraphNode<T, W>*, W> * Neighbours() const { return m_neighbours; }
		void Neighbours(IMEdge<IGraphNode<T, W>*, W>* val) { m_neighbours = val; }
		void AddNeighbour(IMEdge<IGraphNode<T, W>*, W>* n)
		{
			m_neighbours[n->Destination()->Id()].Empty(false);
			m_neighbours[n->Destination()->Id()] = *n;
			
		}

		void RemoveNeighbour(IMEdge<IGraphNode<T, W>*, W>* n)
		{
			m_neighbours[n->Destination()->Id()].Destination()->Empty(false);

		}
};

template <typename T, typename W>
class MatrixGraph : public IGraph < T, W, IGraphNode<T, W>* >
{
public:
	using NodePosition = IGraphNode<T, W>*;
	using Node = IGraphNode < T, W > ;
	typedef typename IGraph::Weight Weight;
	typedef typename IGraph<T, W, NodePosition>::Edge Edge;
	typedef ListP < NodePosition>  ListNode;
	typedef ListP <Edge*> ListEdge;

	MatrixGraph(int _size);
	MatrixGraph(const MatrixGraph&);
	~MatrixGraph();
	void create() {};
	bool empty() const;
	void AddNode(NodePosition);
	void AddEdge(NodePosition, NodePosition, Weight);
	void DeledeteNode(NodePosition);
	void DeleteEdge(NodePosition, NodePosition);
	bool ExistNode(NodePosition) const;
	bool ExistEdge(NodePosition, NodePosition) const;
	ListNode Neighbours(NodePosition) const;
	ListNode Nodes() const;
	ListEdge Edges() const;
	T read(NodePosition) const;
	void write(NodePosition, T) const;
	Weight ReadWeight(NodePosition, NodePosition) const;
	void WriteWeight(NodePosition, NodePosition, Weight);
	int NodesCount() const;
	int EdgesCount() const;

	private:
		IGraphNode<T, W>* m_matrix;
		int m_size;
		int m_nodes;
		int m_edges;
};

template <typename T, typename W>
MatrixGraph<T, W>::MatrixGraph(int _size)
{
	m_size = _size;
	m_matrix = new IGraphNode<T, W>[m_size];

	m_nodes = 0;
	m_edges = 0;

	for (int i = 0; i < m_size; i++)
		m_matrix[i].Neighbours(new IMEdge<IGraphNode<T, W>*, W>[m_size]);


}

template <typename T, typename W>
MatrixGraph<T, W>::~MatrixGraph()
{
	for (int i = 0; i < m_size; i++)
		delete[] m_matrix[i].Neighbours();

	delete[] m_matrix;
}

template <typename T, typename W>
bool MatrixGraph<T, W>::empty() const
{
	return m_nodes == 0;
}

template <typename T, typename W>
void MatrixGraph<T, W>::AddNode(NodePosition n)
{

	if (!ExistNode(n))
	{
		int id = 0;
			if (m_nodes < m_size)
			{
				while (!m_matrix[id].Empty())
					id++;
		
				m_nodes++;
				n->Id(id);
				n->Empty(false);
				m_matrix[id] = *n;	
			}
	}
}

template <typename T, typename W>
void MatrixGraph<T, W>::AddEdge(NodePosition a, NodePosition b, Weight w)
{
	if (!ExistEdge(a, b))
	{
		IMEdge<NodePosition, W>*  e = new IMEdge<NodePosition, W>(a, b, w);
		m_matrix[a->Id()].AddNeighbour(e);
		auto i = m_matrix[0].m_neighbours[1];
		m_edges++;
	}
}

template <typename T, typename W>
void MatrixGraph<T, W>::DeledeteNode(NodePosition n)
{
	if (ExistNode(n))
	{
		for (int i = 0; i < m_size; i++)
		{
			if (!m_matrix[n->Id()].Neighbours()[i].Empty())
				DeleteEdge(m_matrix[n->Id()].Neighbours()[i].Source(), m_matrix[n->Id()].Neighbours()[i].Destination());
		}

		delete[] m_matrix[n->Id()].Neighbours();
		m_matrix[n->Id()].Empty(true);
		m_nodes--;
	}
}

template <typename T, typename W>
void MatrixGraph<T, W>::DeleteEdge(NodePosition a, NodePosition b)
{
	if (ExistEdge(a, b))
	{
		m_matrix[a->Id()].Neighbours()[b->Id()].Empty(true);
		m_edges--;
	}
}

template <typename T, typename W>
bool MatrixGraph<T, W>::ExistNode(NodePosition n) const
{
	for (int i = 0; i < m_size; i++)
		if (m_matrix[i] == *n)
			return true;
	
	return false;
	
}

template <typename T, typename W>
bool MatrixGraph<T, W>::ExistEdge(NodePosition a, NodePosition b) const
{
	for (int i = 0; i < m_size; i++)
		for (int j = 0; j < m_size; j++)
			if (!m_matrix[i].Neighbours()[j].Empty())
				if (m_matrix[i].Neighbours()[j].Source() == a && m_matrix[i].Neighbours()[j].Destination() == b)
					return true;
	
	return false;
	
}

template <typename T, typename W>
typename MatrixGraph<T,W>::ListNode MatrixGraph<T, W>::Neighbours(NodePosition n) const
{
	ListNode list;
	if (ExistNode(n))
	{
		for (int i = 0; i < m_size; i++)
		{
			if (!m_matrix[n->Id()].m_neighbours[i].Empty())
			{
				list.Add(m_matrix[n->Id()].Neighbours()[i].Destination(), list.begin());
			}
		}
	}
	return list;
}

template <typename T, typename W>
typename MatrixGraph<T, W>::ListNode MatrixGraph<T, W>::Nodes() const
{
	ListNode list;
	for (int i = 0; i < m_size; i++)
	{
		if (!m_matrix[i].Empty())
		{
			list.Add(new Node(m_matrix[i]), list.begin());
		}
	}
	return list;
}

template <typename T, typename W>
typename MatrixGraph<T, W>::ListEdge MatrixGraph<T, W>::Edges() const
{
	ListEdge list;
	for (int i = 0; i < m_size; i++)
	{
		if (!m_matrix[i].Empty())
		{
			for (int j = 0; j < m_size; j++)
			{
				if (!m_matrix[i].Neighbours()[j].Empty())
				{

					list.Add(new Edge(m_matrix[i].Neighbours()[j].Source(), m_matrix[i].Neighbours()[j].Destination(), m_matrix[i].Neighbours()[j].Weight()), list.begin());
				}
			}
		}
	}
	return list;
}

template <typename T, typename W>
T MatrixGraph<T, W>::read(NodePosition n) const
{
	if (ExistNode(n))
	{
		for (int i = 0; i < m_size; i++)
			if (m_matrix[i] == *n)
				return m_matrix[i].Value();
	}
	
}

template <typename T, typename W>
void MatrixGraph<T, W>::write(NodePosition n, T e) const
{
	if (ExistNode(n))
	{
		bool found = false;
		for (int i = 0; i < m_size && !found; i++)
			if (m_matrix[i] == *n)
			{
				m_matrix[i].Value(e);
				found = true;
			}
				
	}
}

template <typename T, typename W>
typename MatrixGraph<T,W>::Weight MatrixGraph<T, W>::ReadWeight(NodePosition a, NodePosition b) const
{
	return m_matrix[a->Id()].Neighbours()[b->Id()].Weight();
}

template <typename T, typename W>
void MatrixGraph<T, W>::WriteWeight(NodePosition a, NodePosition b, Weight w)
{
	m_matrix[a->Id()].Neighbours()[b->Id()].Weight(w);
}

template <typename T, typename W>
int MatrixGraph<T, W>::NodesCount() const
{
	return m_nodes;
}

template <typename T, typename W>
int MatrixGraph<T, W>::EdgesCount() const
{
	return m_edges;
}

#endif