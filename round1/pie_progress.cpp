#include <iostream>
#include <fstream>
#include <algorithm>
#include <numeric>
#include <vector>
using namespace std;

int main()
{
	ifstream fin("pie_progress.txt");
	int T;
	fin >> T;

	for (auto i{ 0 }; i < T; i++)
	{
		int N, M;
		fin >> N >> M;

		vector<vector<int>> values(N, vector<int>(M, 0));
		for (auto j{ 0 }; j < N; j++)
		{
			for (auto k{ 0 }; k < M; k++)
			{
				fin >> values[j][k];
			}
		}

		for_each(begin(values), end(values), [](auto &v) { sort(begin(v), end(v)); });

		vector<vector<int>> precomputed_values;
		for (auto a{ 0 }; a < N; a++)
		{
			vector<int> row_values{ 0 };
			accumulate(begin(values[a]), end(values[a]), 0, [&](auto accum, auto val) {
				row_values.push_back(accum + val);
				return accum + val;
			});
			precomputed_values.push_back(row_values);
		}

		vector<vector<int>> dp(300 + 1, vector<int>(300 + 1, INT_MAX));
		for (auto j{ 1 }; j <= M; j++)
		{
			dp[1][j] = precomputed_values[0][j] + (int)pow(j, 2);
		}

		for (auto k{ 2 }; k <= N; k++)
		{
			for (auto l{ k }; l <= min((k - 1) * M, N); l++)
			{
				dp[k][l] = dp[k - 1][l];
			}

			for (auto l{ 1 }; l <= min(M, N); l++)
			{
				for (auto h{ k - 1 }; h <= (k - 1) * M && l + h <= N; h++)
				{
					dp[k][l + h] = min(
						dp[k][l + h],
						dp[k - 1][h] + precomputed_values[k - 1][l] + (int)pow(l, 2)
					);
				}
			}
		}
		cout << "Case #" << i + 1 << ": " << dp[N][N] << '\n';
	}
	return 0;
}
