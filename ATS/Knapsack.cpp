#include <iostream>
#include "Knapsack.h"

Knapsack::Knapsack(int dimension)
{
	m_size = dimension;
	m_free = 0;
	m_profit = 0;
	m_buffer = new IData[m_size];
}

Knapsack::~Knapsack()
{
	delete[] m_buffer;
}


void Knapsack::KnapsackGreedy( int budget)
{
	int* temp = new int[m_size];
	int* solution = new int[m_size];
	int cost = 0;

	PrintInit();

	Sort(m_buffer, temp, m_size);

	for (int i = 0; i < m_size; i++)
	{
		if (m_buffer[temp[i]].Cost() + cost <= budget)
		{
			solution[temp[i]] = 1;
			cost += m_buffer[temp[i]].Cost();
			m_profit += m_buffer[temp[i]].Profit();
		}
		else
			solution[i] = 0;
	}

	
	PrintSolution(solution, budget);

	delete[] temp;

}



void Knapsack::AddItem(IData& e)
{
	if (m_free < m_size)
		m_buffer[m_free++] = e;
}


void Knapsack::Sort(IData* source,int* elements,int size)
{
	int max = 0;

	for (int i = 0; i < size; i++)
		elements[i] = i;
	
	
	
		for (int i = 0; i < size; i++)
		{
			max = i;

			for (int j = i; j < size; j++)
				if (source[elements[max]].Ratio() < source[elements[j]].Ratio())
					max = j;

			Swap(elements[i], elements[max]);
		
		}

		
	
}

void Knapsack::Swap(int& a, int& b)
{
	int temp = b;
	b = a;
	a = temp;
}



void Knapsack::PrintInit() const
{

	std::cout << "//KNAPSACK RESOLVER//" << std::endl << std::endl;

	std::cout << "Elementi disponibili : " << std::endl;
	for (int i = 0; i < m_size; i++)
		std::cout << "Item(" << i << ") Profit(" << m_buffer[i].Profit() << ") Cost(" << m_buffer[i].Cost() << ") " << "P/C("
		<< m_buffer[i].Ratio() << ") " << std::endl;

	std::cout << std::endl;
}


void Knapsack::PrintSolution(int* solution,int budget) const
{
	std::cout << "La soluzione e' (con budget = " << budget << " e ProfittoTotale = "  << m_profit << " ) :"<< std::endl << std::endl;

	for (int i = 0; i < m_size; i++)
		if (solution[i] == 1)
			std::cout << "Item(" << i << ") Profit(" << m_buffer[i].Profit() << ") Cost(" << m_buffer[i].Cost() << ")" << std::endl;


	std::cout << std::endl << std::endl;
}




