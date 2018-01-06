#include "stdafx.h"
#include <iostream>
#include <vector>
#include <algorithm>
#include <string>
using namespace std;


int main()
{
	int T;
	cin >> T;

	for(auto i = 0; i < T; i++)
	{
		int N;
		cin >> N;

		vector<int> v;
		for(auto j = 0; j < N; j++)
		{
			int tmp;
			cin >> tmp;
			v.push_back(tmp);
		}

		sort(begin(v), end(v));
		int total_ways = 0, current_index = 0, heaviest_element_index = v.size() - 1;
		for (auto k = 0; k < v.size(); k++)
		{
			auto total_sum = 0;
			// get the element that weights the most
			const auto heaviest_element = v[heaviest_element_index];
			total_sum += heaviest_element;
			auto invalid = false;
			while (total_sum < 50)
			{
				if (current_index < heaviest_element_index)
				{
					total_sum += heaviest_element;
					current_index++;
				}
				else
				{
					invalid = true;
					break;
				}
			}
			if (invalid) break;

			if(total_sum >= 50) total_ways++;
			heaviest_element_index--;
		}
		cout << "Case #" << i + 1 << ": " << total_ways << '\n';
	}
    return 0;
}
