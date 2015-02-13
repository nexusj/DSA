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


#pragma  once

struct IData
{
private:
	int profit;
	int cost;
	float ratio;
	
public:
	IData() : profit(1), cost(1), ratio(static_cast<float>(profit) / cost) {}
	IData(int _profit, int _cost) : profit(_profit), cost(_cost), ratio(static_cast<float>(profit) / cost) {}
	int Profit() const { return profit; }
	void Profit(int val) { profit = val; }
	int Cost() const { return cost; }
	void Cost(int val) { cost = val; }
	float Ratio() const { return ratio; }
	
};

class Knapsack
{

public:
	Knapsack(int dimension);
	~Knapsack();
	void KnapsackGreedy(int);
	void AddItem(IData&);

private:
	IData* m_buffer;
	int m_size;
	int m_free;
	void Sort(IData*,int*,int);
	void Swap(int&, int&);
	void PrintInit() const;
	void PrintSolution(int*,int) const;
	


};