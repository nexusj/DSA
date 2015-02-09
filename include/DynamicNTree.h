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

#ifndef _DYNAMICNTREE_HEADER_
#define _DYNAMICNTREE_HEADER_

#include "INTree.h"
#include "ListP.h"

template <typename T>
struct IDynamicNode
{
	T e;
	IDynamicNode* parent;
	ListP<ListP<IDynamicNode<T>*>*> *children;
};

template <typename T>
class DynamicNTree : public INTree < T, IDynamicNode<T>* >
{
	public:
		using Node = IDynamicNode<T>*;
		DynamicNTree();
		DynamicNTree(const DynamicNTree&);
		~DynamicNTree();
		void create();
		bool IsEmpty() const;
		void AddRoot();
		Node root() const ;
		Node parent(Node) const ;
		bool IsLeaf(Node) const;
		Node FirstChild(Node) const;
		bool LastSibling(Node) const;
		Node NextSibling(Node) const;
		void AddFirstSubTree(Node, INTree&);
		void AddSubTree(Node, INTree&);
		void RemoveSubTree(Node);
		void WriteNode(Node, T);
		T ReadNode(Node) const;

		void AddFirstChild(Node,T);
		void AddBrother(Node,T);
		

	private:
		Node m_root;
		int m_nodes;
		void SubPrint(const Node&) const;
		void m_AddFirstSubTree(Node, Node);
};

template <typename T>
DynamicNTree<T>::DynamicNTree()
{
	create();
}

template <typename T>
DynamicNTree<T>::DynamicNTree(const DynamicNTree&)
{

}

template <typename T>
DynamicNTree<T>::~DynamicNTree()
{
	RemoveSubTree(root());
	delete m_root;
}

template <typename T>
void DynamicNTree<T>::create()
{
	m_nodes = 0;
	m_root = new IDynamicNode <T>;
	m_root->parent = m_root;
	m_root->children = new ListP <ListP<IDynamicNode<T>*>*> ;
}

template <typename T>
bool DynamicNTree<T>::IsEmpty() const
{
	return(m_nodes == 0);
}

template <typename T>
void DynamicNTree<T>::AddRoot()
{
	if (m_root->children->IsEmpty())
	{
		DynamicNTree<T>::Node  n = new IDynamicNode <T>;
		ListP<IDynamicNode<T>*>* list = new ListP<IDynamicNode<T>*>;
		n->children = new ListP <ListP<IDynamicNode<T>*>*> ;
		n->parent = m_root;
		list->Add(n);
		m_root->children->Add(list);
		m_nodes++;

	}
}

template <typename T>
typename DynamicNTree<T>::Node DynamicNTree<T>::root() const
{
	auto it = m_root->children->begin();
	auto n = m_root->children->Read(it);
	return n->Read(n->begin());
}

template <typename T>
typename DynamicNTree<T>::Node DynamicNTree<T>::parent(Node n) const
{
	return n->parent;
}

template <typename T>
bool DynamicNTree<T>::IsLeaf(Node n) const
{
	return n->children->IsEmpty();
}

template <typename T>
typename DynamicNTree<T>::Node DynamicNTree<T>::FirstChild(Node n) const
{
	
	
	if (!IsLeaf(n))
	{
		auto it = n->children->begin();
		auto second = n->children->Read(it);
		return second->Read(second->begin());
	}
		
	return NULL;
		
}

template <typename T>
bool DynamicNTree<T>::LastSibling(Node n) const
{
	Node p = parent(n);
	auto it = p->children->begin();
	auto second = p->children->Read(it);
	auto itsecond = second->begin();

	while (!p->children->end(p->children->Next(it)))
		it = p->children->Next(it);

	second = p->children->Read(it);
	itsecond = second->begin();
	return (n == second->Read(itsecond));
}

template <typename T>
typename DynamicNTree<T>::Node DynamicNTree<T>::NextSibling(Node n) const
{
	
		if (!LastSibling(n))
		{
			Node p = parent(n);
			auto it = p->children->begin();
			auto second = p->children->Read(it);
			auto itsecond = second->begin();

			while (!p->children->end(it))
			{
				if (second->Read(itsecond) == n)
				{
					auto n = p->children->Read(p->children->Next(it));
					return n->Read(n->begin());
				}

				it = p->children->Next(it);
				second = p->children->Read(it);
				itsecond = second->begin();
				
			}
		}
	

	return NULL;
}

template <typename T>
void DynamicNTree<T>::AddFirstSubTree(Node u, INTree& t)
{
	if (!this->IsEmpty() && !t.IsEmpty())
	{

		Node v = t.root();
		Node m;
		AddFirstChild(u, v->e);
		m = FirstChild(u);
		
		m_AddFirstSubTree(m, v);
	}

}

template <typename T>
void DynamicNTree<T>::AddSubTree(Node u, INTree& t)
{
	if (!this->IsEmpty() && !t.IsEmpty())
	{

		Node v = t.root();
		Node m;

		AddBrother(u, v->e);
		m = NextSibling(u);
		
		m_AddFirstSubTree(m, v);
	}
}

template <typename T>
void DynamicNTree<T>::RemoveSubTree(Node n)
{
	
	Node p = parent(n);
	auto it = p->children->begin();
	auto second = p->children->Read(it);
	auto itsecond = second->begin();

	if (!IsLeaf(n))
	{
		

		while (!n->children->IsEmpty())
		{
			RemoveSubTree(FirstChild(n));
			
		}
			
	}

	while (second->Read(itsecond) != n)
	{

		it = p->children->Next(it);
		second = p->children->Read(it);
		itsecond = second->begin();
	}

	p->children->RemoveAt(it);
	m_nodes--;
}

template <typename T>
void DynamicNTree<T>::WriteNode(Node n, T e)
{
	n->e = e;
}

template <typename T>
T DynamicNTree<T>::ReadNode(Node n) const
{
	return n->e;
}

template <typename T>
void DynamicNTree<T>::AddFirstChild(Node n, T e)
{
	Node c = new IDynamicNode<T> ;
	ListP<IDynamicNode<T>*>* list = new ListP<IDynamicNode<T>*>;
	c->e = e;
	c->children = new ListP <ListP<IDynamicNode<T>*>*>;
	c->parent = n;
	list->Add(c);
	n->children->Add(list, n->children->begin());
	m_nodes++;
}

template <typename T>
void DynamicNTree<T>::AddBrother(Node n, T e)
{
	Node p = parent(n);
	Node c = new IDynamicNode<T>;
	ListP<IDynamicNode<T>*>* list = new ListP<IDynamicNode<T>*>;
	c->e = e;
	c->children = new ListP <ListP<IDynamicNode<T>*>*>;
	c->parent = p;
	list->Add(c);

	auto it = p->children->begin();
	auto second = p->children->Read(it);
	auto itsecond = second->begin();

	while (!p->children->end(it) && second->Read(itsecond) != n)
	{
		it = p->children->Next(it);
		itsecond = second->Next(itsecond);

	}


	p->children->Add(list, p->children->Next(it));

	m_nodes++;
}



template <typename T>
void DynamicNTree<T>::SubPrint(const Node& n) const
{
	
	if (!IsLeaf(n))
	{

		std::cout << "[ " << ReadNode(n) << " : ";
		auto it = n->children->begin();
		auto second = n->children->Read(it);
		auto itsecond = second->begin();
		auto _node = second->Read(itsecond);

		while (!n->children->end(it))
		{
			

			if (!IsLeaf(_node))
			{

				SubPrint(_node);
// 				Node u = FirstChild(n);
// 				auto brother = u->children->begin();
// 				auto nbrother = u->children->Read(brother);
// 				auto itnbrother = nbrother->begin();
// 				auto _m = nbrother->Read(itnbrother);
// 
// 				std::cout << "[ ";
// 				while (!u->children->end(brother))
// 				{
// 
// 					if (!IsLeaf(_m))
// 						SubPrint(_m);
// 					else
// 						std::cout << ReadNode(_m) << " ";
// 
// 					brother = u->children->Next(brother);
// 					_m = NextSibling(_m);
// 				}
// 				std::cout << "] ";
 			}
			else
				std::cout << ReadNode(_node) << " ";


			it = n->children->Next(it);
			_node = NextSibling(_node);
			
		}
	}
	else
		std::cout << ReadNode(n) << " ";

	std::cout << "] ";
}


template <typename T>
void DynamicNTree<T>::m_AddFirstSubTree(Node u, Node v)
{
	Node n;
	if (!IsLeaf(v))
	{
		this->AddFirstChild(u, ReadNode(FirstChild(v)));
		u = this->FirstChild(u);

		do
		{
			n = this->FirstChild(v);
			if (!IsLeaf(n))
			{
				m_AddFirstSubTree(u, n);
			}

			this->AddBrother(u, ReadNode(NextSibling(n)));
			u = NextSibling(u);
			
		}while (!LastSibling(u));


	}
}


#endif