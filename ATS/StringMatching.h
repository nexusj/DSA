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

#ifndef _STRINGMATCHING_HEADER_
#define _STRINGMATCHING_HEADER_
#include <string>

int CompareStrings(std::string pattern, std::string text)
{
	int i = 1, j = 1, k = 0;

	while ( i <= text.length() && j <= pattern.length() )
	{
		if (text.at(i-1) == pattern.at(j-1))
		{
			i++;
			j++;
		}
		else
		{
			k++;
			i = k;
			j = 1;
		}
	}

	if (j > pattern.length())
		return k;
	else
		return i;
}
#endif