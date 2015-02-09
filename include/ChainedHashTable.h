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

#ifndef _CHAINEDHASH_TABLE_H
#define _CHAINEDHASH_TABLE_H


#include "Dictionary.h"
#include "ListP.h"


template<class K, class E>
struct mypair;

template<class K, class E>
class ChainedHashTable: public dictionary<K,E> {
public:
	ChainedHashTable(int);
	~ChainedHashTable();

	 bool empty() const
	 {
	   return (dsize == 0);
	 };	
	 
	 int size() const
	 {
	   return dsize;
	 };		
	 
	 void Remove(const K& k);	
	 void Modify(const K& k, const E& e);
	 void create(){};
	 int search(const K& ) const;
	 mypair< K, E>* find(const K& ) const;
	 void Add( mypair< K, E>& );
	 bool Contains(const E&);
	 ListP<E> Values();
	 ListP<K> Keys();

private:
	ListP<mypair<K, E> >** table;    
	hash<K> hashm;		      		          
	int divisor;
	int dsize;
};

template<class K, class E>
ChainedHashTable<K,E>::ChainedHashTable(int the_divisor)
{
  divisor = the_divisor;
  dsize = 0;
  
  
  table = new ListP<mypair<K, E>>*[divisor];

  for (int i = 0; i < divisor; i++)
	  table[i] = new ListP<mypair<K, E> >;

  
}


template<class K, class E>
ChainedHashTable<K, E>::~ChainedHashTable()
{
	for (int i = 0; i < divisor; i++)
		delete table[i];
	delete[] table;
}




template<class K, class E>
int ChainedHashTable<K,E>::search(const K& the_key) const
{
	int i = (int)hashm(the_key) % divisor;   // the home bucket
	int j = i;
	ListP<mypair<K, E>>::iterator it = table[j]->begin();
	
	do {
		if (table[j]->IsEmpty() || table[j]->Read(it).first == the_key)
			return j;
		j = (j + 1) % divisor;                    // the next bucket
	} while (j != i);

	return j;
	
}



template<class K, class E>
mypair< K, E>* ChainedHashTable<K,E>::find(const K& the_key) const
{
  
	// search the table
	int b = search(the_key);
	ListP<mypair<K, E>>::iterator it = table[b]->begin();
	
	if (!table[b]->IsEmpty())
	{
		while (table[b]->Read(it).first != the_key)
		{
			it = table[b]->Next(it);
		}
	}else
		return NULL;  

	return &table[b]->Read(it); 
}



template<class K, class E>
void ChainedHashTable<K,E>::Add( mypair<K, E>& the_pair)
{
  
  int b = search(the_pair.first);

 
  ListP<mypair<K, E>>::iterator it = table[b]->begin();
	  table[b]->Add(the_pair, it);
    dsize++;
 
}

template<class K, class E>
void ChainedHashTable<K,E>::Remove(const K& k){

	int b = search(k);
	ListP<mypair<K, E>>::iterator it = table[b]->begin();

	if (!table[b]->IsEmpty())
	{
		while (table[b]->Read(it).first != k && !table[b]->end(it))
		{
			it = table[b]->Next(it);
		}

		if (table[b]->Read(it).first == k)
		{
			table[b]->RemoveAt(it);
			dsize--;
		}
			
	}

     
}

template<class K, class E>
void ChainedHashTable<K,E>::Modify(const K& k, const E& e){

	mypair<K, E>* pair = this->find(k);

	if (pair != NULL)
		pair->second = e;

}



template<class K, class E>
bool ChainedHashTable<K, E>::Contains(const E& e)
{
	ListP<mypair<K, E>>::iterator it;
	for (int i = 0; i < divisor; i++)
	{
		it = table[i]->begin();

		if (!table[i]->IsEmpty())
		{
			while (table[i]->Read(it).second != e && !table[i]->end(it))
			{
				it = table[i]->Next(it);
			}

			if (table[i]->Read(it).second == e)
			{
				return true;
			}
		}

	}

	return false;
}


template<class K, class E>
ListP<E> ChainedHashTable<K, E>::Values()
{
	ListP<E> _values;
	ListP<mypair<K, E>>::iterator it;

	for (int i = 0; i < divisor; i++)
	{
		it = table[i]->begin();

		if (!table[i]->IsEmpty())
		{
			while (!table[i]->end(it))
			{
				_values.Add(table[i]->Read(it).second);
				it = table[i]->Next(it);
			}
			
		}
	}

	return _values;


}


template<class K, class E>
ListP<K> ChainedHashTable<K, E>::Keys()
{
	ListP<K> _keys;
	ListP<mypair<K, E>>::iterator it;

	for (int i = 0; i < divisor; i++)
	{
		it = table[i]->begin();

		if (!table[i]->IsEmpty())
		{
			while (!table[i]->end(it))
			{
				_keys.Add(table[i]->Read(it).first);
				it = table[i]->Next(it);
			}

		}
	}


	return _keys;
}


#endif