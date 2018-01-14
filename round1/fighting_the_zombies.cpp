#include <iostream>
#include <fstream>
#include <vector>
#include <utility>
#include <algorithm>
using namespace std;

int main()
{
	ifstream fin("fighting_the_zombies.txt");
	int t, n, r;
	fin >> t;

	for (auto i{ 0 }; i < t; i++)
	{
		auto best = 0;
		fin >> n >> r;

		vector<pair<int, int>> zombies;
		vector<pair<int, int>> points;
		for (auto j{ 0 }; j < n; j++)
		{
			auto xi = 0, yi = 0;
			fin >> xi >> yi;
			zombies.push_back(make_pair(xi, yi));
		}

		for (auto j{ 0 }; j < zombies.size(); j++)
		{
			for (auto k{ j }; k < zombies.size(); k++)
			{
				points.push_back(make_pair(min(zombies[j].first, zombies[k].first), min(zombies[j].second, zombies[k].second)));
			}
		}

		auto is_inside([&](auto element, auto cx, auto cy)
		{
			return element.first >= cx && element.first <= cx + r && element.second >= cy && element.second <= cy + r;
		});

		for (const auto point : points)
		{
			for (const auto point2 : points)
			{
				auto zombie_count{ 0 };
				for (const auto zombie : zombies)
				{
					if (is_inside(zombie, point.first, point.second) || is_inside(zombie, point2.first, point2.second))
					{
						zombie_count++;
					}
				}
				best = max(best, zombie_count);
			}
		}
		cout << "Case #" << i + 1 << ": " << best << '\n';
	}
	return 0;
}
