#include <iostream>
#include "N-Queens.h"

NQueens::NQueens(int size)
{
	m_size = size;
	m_vector = new int[m_size];

	for (int i = 0; i < m_size; i++)
		m_vector[i] = 0;
}

NQueens::~NQueens()
{
	delete[] m_vector;
}

bool NQueens::Verify(int k)
{
	for (int i = 0; i < k; i++)
			if (m_vector[i] == m_vector[k] || m_vector[i] == m_vector[k] - (k - i) || m_vector[i] == m_vector[k] + (k - i))
				return true;

	return false;
}

bool NQueens::Start()
{
	bool success = false,
		b = false;
	int k = 1;
	m_vector[k] = 1;

	do 
	{
		if (Verify(k))
		{
			do
			{
				if (m_vector[k] < m_size-1)
				{
					b = true;
					m_vector[k]++;
				}
				else
				{
					b = false;
					k--;
				}
			} while (!b || k == 0);
		}
		else if (k == m_size-1)
			return success = true;
		else
		{
			k++;
			m_vector[k] = 1;
		}
	} while (!success || k== 0);

	return success;
}

void NQueens::Print()
{
	int column = 0;

	std::cout << "La soluzione e' la seguente (" << m_size << " queens in " << m_size*m_size << " cells) : " << std::endl;
	
	for (int column = 0; column < m_size; column++)
	{
		for (int row = 0; row < m_size; row++)
		{
			if (row % m_size == 0)
			{
				std::cout << std::endl;
			}

			if (m_vector[column] == row)
				std::cout << "Q ";
			else
				std::cout << "- ";
		}
		
		
		
	}
		
}

