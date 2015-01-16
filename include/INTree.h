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

#ifndef _INTREE_HEADER_
#define _INTREE_HEADER_

template <typename T, typename N>
class INTree
{
	public:
		virtual void create() = 0;
		virtual bool IsEmpty() const = 0;
		virtual void AddRoot() = 0;
		virtual N root() const = 0;
		virtual N parent(N) const = 0;
		virtual bool IsLeaf(N) const = 0;
		virtual N FirstChild(N) const = 0;
		virtual bool LastSibling(N) const = 0;
		virtual N NextSibling(N) const = 0;
		virtual void AddFirstSubTree(N, INTree&) = 0;
		virtual void AddSubTree(N, INTree&) = 0;
		virtual void RemoveSubTree(N) = 0;
		virtual void WriteNode(N,T) = 0;
		virtual T ReadNode(N) const = 0;
		virtual void Print() const;

	private:
		virtual void SubPrint(const N&) const = 0;

};

template <typename T, typename N>
void INTree<T, N>::Print() const
{
	if (!IsEmpty())
		SubPrint(root());
	else
		std::cout << "[]" << std::endl;

	std::cout << std::endl;
}



template <typename T, typename N>
std::ostream& operator<<(std::ostream &os, const INTree<T, N> &t)
{
	t.Print();
	return os;
}

#endif