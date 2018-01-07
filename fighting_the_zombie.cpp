#include <fstream>
#include <vector>
#include <iostream>
#include <regex>
#include <iomanip>
#include <numeric>
using namespace std;

int main()
{
	regex e("(\\d+)d(\\d+)([+-])?(\\d+)?");
	ofstream fout;
	fout.open("result.txt", ofstream::out | ofstream::app);
	fout << fixed << setprecision(6);
	ifstream fin("fighting_the_zombie.txt");
	int T;
	fin >> T;

	vector<vector<long double>> dp(21, vector<long double>(401));
	for (auto i = 0; i < T; i++)
	{
		int H, S;
		fin >> H >> S;

		long double best_result = 0;
		for (auto j = 0; j < S; j++)
		{
			// set all elements of the vector to 0 before continuing
			for_each(dp.begin(), dp.end(), [](auto &v) {
				for_each(v.begin(), v.end(), [](auto &v1) { v1 = 0; });
			});

			smatch m;
			string tmp{};
			fin >> tmp;
			regex_match(tmp, m, e);
			auto x{ 0 }, y{ 0 }, z{ 0 };
			x = stoi(m[1]);
			y = stoi(m[2]);
			if(m[3] != "")
			{
				z = stoi(m[4]);
				if (m[3] == '-')
				{
					z = -z;
				}
			}

			dp[0][0] = 1.0;
			for(auto a {0}; a < x; a++)
			{
				for(auto b {a}; b <= a * y; b++)
				{
					for(auto c {1}; c <= y; c++)
					{
						dp[a + 1][b + c] += dp[a][b] / y;
					}
				}
			}

			if(max(x, H - z) < dp[x].size())
			{
				best_result = max(best_result, static_cast<long double>(accumulate(dp[x].begin() + max(x, H - z), dp[x].end(), 0.0)));
			}
		}
		fout << "Case #" << i + 1 << ": " << best_result << '\n';
	}
    return 0;
}

