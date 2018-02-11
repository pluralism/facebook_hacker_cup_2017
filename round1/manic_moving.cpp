#include <iostream>
#include <vector>
#include <fstream>
#include <climits>
using namespace std;

int main(int argc, char **argv) {
    ifstream fin("manic_moving.txt");
    int t;
    fin >> t;
    for(int i = 0; i < t; i++)
    {
        int n, m, k;
        fin >> n >> m >> k;

        vector<pair<int, int>> requests;
        vector<vector<int>> dist(100, vector<int>(100, INT_MAX >> 1));

        for(int j = 0; j < n; j++)
        {
            dist[j][j] = 0;
        }

        for(int j = 0; j < m; j++)
        {
            int a, b, g;
            fin >> a >> b >> g;
            a--; b--;
            dist[a][b] = dist[b][a] = min(g, dist[a][b]);
        }

        for(int j = 0; j < k; j++)
        {
            int s, d;
            fin >> s >> d;
            s--; d--;
            requests.emplace_back(make_pair(s, d));
        }

        for(int a = 0; a < n; a++)
        {
            for(int b = 0; b < n; b++)
            {
                for(int c = 0; c < n; c++)
                {
                    dist[b][c] = min(dist[b][c], dist[b][a] + dist[a][c]);
                }
            }
        }

        vector<vector<int>> dp(5001, vector<int>(4, INT_MAX >> 1));
        dp[0][0] = dist[0][requests[0].first];
        dp[0][3] = dp[0][0] + dist[requests[0].first][requests[0].second];
        
        for(int j = 1; j < k; j++)
        {
            pair<int, int> request = requests[j];
            pair<int, int> prevRequest = requests[j - 1];
            dp[j][0] = min(dp[j][0], dp[j - 1][3] + dist[prevRequest.second][request.first]);
            dp[j][1] = min(dp[j][1], dp[j - 1][0] + dist[prevRequest.first][request.first]);
            dp[j - 1][2] = min(dp[j - 1][2], dp[j][1] + dist[request.first][prevRequest.second]);
            dp[j][3] = min(dp[j][3], dp[j][0] + dist[request.first][request.second]);
            dp[j][3] = min(dp[j][3], dp[j - 1][2] + dist[prevRequest.second][request.second]);
            dp[j + 1][1] = j < k - 1 ? min(dp[j + 1][1], dp[j - 1][2] + dist[prevRequest.second][requests[j + 1].first]) : dp[j + 1][1];
        }

        cout << "Case #" << i + 1 << ": " << (dp[k - 1][3] >= (INT_MAX >> 1) ? -1 : dp[k - 1][3]) << '\n';
    }

    return 0;
}
