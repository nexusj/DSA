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

#ifndef _IGRAPH_HEADER_
#define _IGRAPH_HEADER_

#include "ListP.h"

template <typename N, typename W>
struct IEdge
{
	private:
		N m_source;
		N m_destination;
		W m_weight;

	public:
		IEdge() {};
		IEdge(N from, N to, W weight) : m_source(from), m_destination(to), m_weight(weight) {}
		IEdge(N from, N to) : m_source(from), m_destination(to), m_weight(0) {}
		N Source() const { return m_source; }
		void Source(N val) { m_source = val; }
		N Destination() const { return m_destination; }
		void Destination(N val) { m_destination = val; }
		W Weight() const { return m_weight; }
		void Weight(W val) { m_weight = val; }

};

template <typename T, typename W, typename N>
class IGraph
{
	public:
		typedef IEdge<N,W> Edge;
		typedef N Node;
		typedef W Weight;
		

		virtual void create() = 0;
		virtual bool empty() const = 0;
		virtual void AddNode(Node) = 0;
		virtual void AddEdge(Node, Node, Weight) = 0;
		virtual void DeledeteNode(Node) = 0;
		virtual void DeleteEdge(Node, Node) = 0;
		virtual bool ExistNode(Node) const = 0;
		virtual bool ExistEdge(Node, Node) const = 0;
		virtual ListP <Node> Neighbours(Node) const = 0;
		virtual ListP <Node> Nodes() const = 0;
		virtual ListP <Edge*> Edges() const = 0;
		virtual T read(Node) const = 0;
		virtual void write(Node, T) const = 0;
		virtual Weight ReadWeight(Node, Node) const = 0;
		virtual void WriteWeight(Node, Node, Weight) = 0;
		virtual int NodesCount() const = 0;
		virtual int EdgesCount() const = 0;





};
#endif