#pragma once

#include "ListGraph.h"
#include "QueueP.h"
#include "StackP.h"

template <typename T, typename W>
class Helper
{
public:
	typedef typename ListGraph<T,W>::Node Node;
	typedef typename ListGraph<T, W>::ListNode ListNode;
	typedef typename ListGraph<T, W>::Weight Weight;
	void minpath(Node, Node, Node, ListGraph<T, W>&);
	ListNode GetPath(Node, Node, ListGraph<T,W>&);
};

template <typename T, typename W>
typename Helper<T,W>::ListNode Helper<T, W>::GetPath(Node a, Node b,ListGraph<T, W>& _graph)
{
	int size = _graph.NodesCount();
	ListNode path;
	ListNode visited;
	QueueP<Node> next;


	next.Push(a);

	while (!next.IsEmpty() && next.Head() != b)
	{
		auto e = next.Pop();
		auto neighbour = _graph.Neighbours(e);

		for (auto it = neighbour.begin(); !neighbour.end(it); it = neighbour.Next(it) )
		{
			if (!visited.Contains(neighbour.Read(it)))
			{
				visited.Add(neighbour.Read(it));
				next.Push(neighbour.Read(it));
				path.Add(e);
				path.Add(neighbour.Read(it));
			}
		}
	}

	

	return path;
}

template <typename T, typename W>
void Helper<T, W>::minpath(Node a, Node b, Node c, ListGraph<T, W>& _graph)
{
	StackP<T> _stack;

	if (!_graph.ExistNode(a) && !_graph.ExistNode(b) && !_graph.ExistNode(c))
		return;

	auto firstpath = GetPath(a, c, _graph);
	auto secondpath = GetPath(c, b, _graph);

	if (!firstpath.Contains(c) || !secondpath.Contains(b) || !secondpath.Contains(c))
		return;

	auto i = b;
	auto it = secondpath.begin();

	while (i != c)
	{
		if (secondpath.Read(secondpath.Next(it)) == i)
		{
			_stack.Push(i->Value());
			i = secondpath.Read(it);
		}
		
		it = secondpath.Next(it);
	} 

	i = c;
	it = firstpath.begin();

	while (i != a)
	{
		if (firstpath.Read(firstpath.Next(it)) == i)
		{
			_stack.Push(i->Value());
			i = firstpath.Read(it);
		}
		

		it = firstpath.Next(it);
		
	}

	_stack.Push(a->Value());

	

	std::cout << _stack;
	
	
}


