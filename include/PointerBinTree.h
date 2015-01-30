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

#ifndef _POINTER_BIN_TREE_HEADER_
#define  _POINTER_BIN_TREE_HEADER_

#include "Bin_Tree.h"
#include "exceptions.h"

template <typename T>
struct INode
{
	INode* parent;
	INode* left;
	INode* right;
	T e;
};

template<typename T>
class PointerBinTree : public Bin_tree < T,INode<T>* >
{
	
	public:
		using Node = INode<T>*;

		PointerBinTree();
		PointerBinTree(const PointerBinTree&);
		~PointerBinTree();

		void create();
		bool empty() const;
		Node root() const;
		Node parent(Node) const;
		Node left(Node) const;
		Node right(Node) const;
		bool EmptyLeft(Node) const;
		bool EmptyRight(Node) const;
		void erase(Node);
		T read(Node) const;
		void write(Node, T);
		void AddRoot();
		void AddLeft(Node);
		void AddRight(Node);

		int Depth(Node) const;

	private:
		int m_nodes; //number of nodes
		Node m_root;


};

template<typename T>
PointerBinTree<T>::PointerBinTree()
{
	create();
}

template<typename T>
PointerBinTree<T>::PointerBinTree(const PointerBinTree&)
{

}

template<typename T>
PointerBinTree<T>::~PointerBinTree()
{
	erase(root());
	delete m_root;
}

template<typename T>
void PointerBinTree<T>::create()
{
	m_root = new INode<T>;
	m_root->parent = m_root;
	m_root->left = NULL;
	m_root->right = NULL;
	m_nodes = 0;
}

template<typename T>
bool PointerBinTree<T>::empty() const
{
	return (m_nodes == 0);
}

template<typename T>
typename PointerBinTree<T>::Node PointerBinTree<T>::root() const
{
	return left(m_root);
}

template<typename T>
typename PointerBinTree<T>::Node PointerBinTree<T>::parent(Node n) const
{
	return n->parent != NULL ? n->parent : throw NullNode();
}

template<typename T>
typename PointerBinTree<T>::Node PointerBinTree<T>::left(Node n) const
{
	return !EmptyLeft(n) ? n->left : NULL;
}

template<typename T>
typename PointerBinTree<T>::Node PointerBinTree<T>::right(Node n) const
{
	return !EmptyRight(n) ? n->right : NULL;
}

template<typename T>
bool PointerBinTree<T>::EmptyLeft(Node n) const
{
	return (n->left == NULL);
}

template<typename T>
bool PointerBinTree<T>::EmptyRight(Node n) const
{
	return (n->right == NULL);
}

template<typename T>
void PointerBinTree<T>::erase(Node n)
{
	if (n)
	{
		if (!EmptyLeft(n))
			erase(n->left);
		if (!EmptyRight(n))
			erase(n->right);
		if (n != this->root())
		{
			Node p = parent(n);
			if (p->left == n)
			{
				delete p->left;
				p->left = NULL;
			}
				
			else
			{
				delete p->right;
				p->right = NULL;
			}
				
		}
		else
		{
			delete m_root->left;
			m_root->left = NULL;
		}
			

		m_nodes--;
	}
	
}

template<typename T>
T PointerBinTree<T>::read(Node n ) const
{
	return n != NULL ? n->e : throw NullNode();
}

template<typename T>
void PointerBinTree<T>::write(Node n, T e)
{
	if (n != NULL)
		n->e = e;
	else
		throw NullNode();
}

template<typename T>
void PointerBinTree<T>::AddRoot()
{
	if (m_root->left == NULL)
	{
		PointerBinTree<T>::Node n = new INode<T>;
		n->left = NULL;
		n->right = NULL;
		n->parent = n;
		m_root->left = n;
		m_nodes++;
	}
	else
		throw RootExists();
}

template<typename T>
void PointerBinTree<T>::AddLeft(Node n)
{
	if (root() == NULL)
		throw EmptyTree();
	if (n == NULL)
		throw NullNode();
	if (n->left != NULL)
		throw NodeExists();
	else
	{
		Node tmp = new INode<T>;

		n->left = tmp;
		tmp->parent = n;
		tmp->left = NULL;
		tmp->right = NULL;
		m_nodes++;
	}
}

template<typename T>
void PointerBinTree<T>::AddRight(Node n)
{
	if (root() == NULL)
		throw EmptyTree();
	if (n == NULL)
		throw NullNode();
	if (n->right != NULL)
		throw NodeExists();
	else
	{
		Node tmp = new INode<T>;

		n->right = tmp;
		tmp->parent = n;
		tmp->left = NULL;
		tmp->right = NULL;
		m_nodes++;
	}
}


template<typename T>
int PointerBinTree<T>::Depth(Node u) const
{
	int max = 0, current = 0;
	Node v;

	if (EmptyLeft(u) && EmptyRight(u))
		return 0;
	else
	{
		v = left(u);
		max = Depth(v);

		if (!EmptyLeft(v))
			current = Depth(left(v));
		else if (!EmptyRight(v))
			current = Depth(right(v));

		if (max <= current)
			max = current;

		max++;
	}

	return max;
}

#endif