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

#ifndef _LISTNTREE_HEADER_
#define _LISTNTREE_HEADER_

#include "INTree.h"
#include "ListP.h"

template <typename T>
struct INodes
{
	T e;
	INodes* parent;
	ListP<INodes<T>*>* children;
};


template<typename T>
class ListNTree : public INTree < T, INodes<T>* >
{
	public:
		using Node = INodes<T>*;
		ListNTree();
		ListNTree(const ListNTree&);
		~ListNTree();
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
		void m_AddFirstSubTree(Node,Node,typename ListP<Node>::iterator);
		void m_AddSubTree(Node,Node );
		void SubPrint(const Node&) const;
};

template<typename T>
ListNTree<T>::ListNTree()
{
	create();
}

template<typename T>
ListNTree<T>::ListNTree(const ListNTree&)
{

}

template<typename T>
ListNTree<T>::~ListNTree()
{
	RemoveSubTree(root());
	delete m_root;
}

template<typename T>
void ListNTree<T>::create()
{
	m_nodes = 0;
	m_root = new INodes <T> ;
	m_root->parent = m_root;
	m_root->children = new ListP <INodes<T>*> ;

}

template<typename T>
bool ListNTree<T>::IsEmpty() const
{
	return (m_nodes == 0);
}

template<typename T>
void ListNTree<T>::AddRoot()
{
	if (m_root->children->IsEmpty())
	{
		ListNTree<T>::Node  n = new INodes<T>;
		n->children = new ListP<INodes<T>*> ;
		n->parent = m_root;
		m_root->children->Add(n);
		m_nodes++;

	}
}

template<typename T>
typename ListNTree<T>::Node ListNTree<T>::root() const
{
	return m_root->children->Read(m_root->children->begin());
}

template<typename T>
typename ListNTree<T>::Node  ListNTree<T>::parent(Node n) const
{
	return n->parent;
}

template<typename T>
bool ListNTree<T>::IsLeaf(Node n) const
{
	return n->children != NULL? n->children->IsEmpty() : false;
}

template<typename T>
typename ListNTree<T>::Node  ListNTree<T>::FirstChild(Node n) const
{
	if (!IsLeaf(n))
		return n->children->Read(n->children->begin());
}

template<typename T>
bool ListNTree<T>::LastSibling(Node n) const
{
	Node p = parent(n);
	ListP<Node>::iterator it = p->children->begin();

	while (!p->children->end(p->children->Next(it)))
		it = p->children->Next(it);

	return (n == p->children->Read(it));
}

template<typename T>
typename ListNTree<T>::Node  ListNTree<T>::NextSibling(Node n) const
{
	if (!LastSibling(n))
	{
		Node p = parent(n);
		ListP<Node>::iterator it = p->children->begin();

		while (!p->children->end(it))
		{
			if (p->children->Read(it) == n)
				return p->children->Read(p->children->Next(it));

				it = p->children->Next(it);
		}
	}

	return NULL;
	

}

template<typename T>
void ListNTree<T>::AddFirstSubTree(Node u, INTree<T,Node>& t)
{
	if (!this->IsEmpty() && !t.IsEmpty())
	{
		
		Node v = t.root();
		Node m;
		ListP<Node>::iterator it = v->children->begin();

	
		AddFirstChild(u, v->e);
		m = FirstChild(u);
		it = v->children->Next(it);
		m_AddFirstSubTree(m, v, it);


	}
}

template<typename T>
void ListNTree<T>::AddSubTree(Node, INTree&)
{

}

template<typename T>
void ListNTree<T>::RemoveSubTree(Node n)
{
	ListP<Node>::iterator it;
	Node p = parent(n);
	it = p->children->begin();

	if (!IsLeaf(n))
		while (!n->children->IsEmpty())
			RemoveSubTree(n->children->Read(n->children->begin()));

	while (p->children->Read(it) != n)
		it = p->children->Next(it);

	p->children->RemoveAt(it);
	m_nodes--;

}

template<typename T>
void ListNTree<T>::WriteNode(Node n , T e)
{
	n->e = e;
}

template<typename T>
T ListNTree<T>::ReadNode(Node n) const
{
	return n->e;
}



template<typename T>
void ListNTree<T>::AddFirstChild(Node n, T e)
{
	Node c = new INodes <T> ;
	c->e = e;
	c->children = new ListP<INodes<T>*> ;
	c->parent = n;
	n->children->Add(c, n->children->begin());
	m_nodes++;
}


template<typename T>
void ListNTree<T>::AddBrother(Node n, T e)
{
	Node p = parent(n);
	Node c = new INodes<T>;
	c->e = e;
	c->children = new ListP<INodes<T>*>;
	c->parent = p;
	ListP<Node>::iterator it = p->children->begin();

	while (!p->children->end(it) && p->children->Read(it) != n)
		it = p->children->Next(it);


	p->children->Add(c, p->children->Next(it));

	m_nodes++;
}


template<typename T>
void ListNTree<T>::m_AddFirstSubTree(Node u, Node v,typename ListP<Node>::iterator it)
{
	Node n;
	if (!IsLeaf(v))
	{
		this->AddFirstChild(u, ReadNode(FirstChild(v)));
		u = this->FirstChild(u);

		while (!v->children->end(it))
		{
			n = this->FirstChild(v);
			if (!IsLeaf(n))
			{
				m_AddFirstSubTree(u, n, it);
			}
			
			this->AddBrother(u, ReadNode(NextSibling(n)));
			u = NextSibling(u);
			it = v->children->Next(it);
		}


	}
}



template <typename T>
void ListNTree<T>::SubPrint(const Node& n) const
{
	std::cout << "[ ";
	if (!IsLeaf(n))
	{
		std::cout << ReadNode(n) << " : ";
		ListP<Node>::iterator it = n->children->begin();

		while (!n->children->end(it))
		{
			std::cout << ReadNode(n->children->Read(it)) << " ";

			if (!IsLeaf(n->children->Read(it)))
			{
				Node u = FirstChild(n);
				ListP<Node>::iterator brother = u->children->begin();

				std::cout << "[ ";
				while (!u->children->end(brother))
				{

					if (!IsLeaf(u->children->Read(brother)))
						SubPrint(u->children->Read(brother));
					else
						std::cout << ReadNode(u->children->Read(brother)) << " ";

					brother = u->children->Next(brother);
				}
				std::cout << "] ";
			}


			it = n->children->Next(it);
		}
	}
	else
		std::cout << ReadNode(n) << " ";
	// 	if (!LastSibling(n))
	// 	{
	// 		N p = parent(n);
	// 		ListP<N>::iterator brother = p->children->begin();
	// 
	// 		while (!p->children->end(brother))
	// 		{
	// 			std::cout << ReadNode(n->children->Read(brother)) << " ";
	// 			brother = n->children->Next(brother);
	// 		}
	// 		
	// 	}

	std::cout << "] ";
}

#endif
