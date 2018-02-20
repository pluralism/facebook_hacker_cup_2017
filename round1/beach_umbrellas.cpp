#include <iostream>
#include <numeric>
#include <map>
#include <vector>
#include <fstream>
using namespace std;

const long long MOD = static_cast<const long long>(1000000007);
map<pair<long long, long long>, long long> dp_results;

long long add(long long x, long long y) {
    return (x + y) % MOD;
}

long long mul(long long x, long long y) {
    return (x * y) % MOD;
}

// For reference: https://en.wikipedia.org/wiki/Modular_exponentiation#Right-to-left_binary_method
long long pow(long long x, long long y) {
    long long result = 1;
    while (y > 0) {
        if(y & 1) {
            result = mul(result, x);
        }
        y >>= 1;
        x = mul(x, x);
    }
    return result;
}

long long div2(long long x, long long y) {
    return mul(x, pow(y, MOD - 2));
}

long long C(long long n, long long k) {
    pair<long long, long long> tmp_pair(n, k);
    if(dp_results.find(tmp_pair) != dp_results.end()) {
        return dp_results[tmp_pair];
    }

    long long result = 1;
    for(long long i = 1; i <= k; i++) {
        result = div2(mul(result, n - i + 1), i);
    }

    dp_results[tmp_pair] = result;
    return result;
}

long long calculate(long long N, long long M, vector<long long> &radius) {
    long long radius_sum = accumulate(begin(radius), end(radius), 0, [](long long acc, long long current) {
        return acc + (current * 2);
    });

    long long factorial = 1LL;
    for(long long i = 1LL; i <= N - 2; ++i) {
        factorial = mul(factorial, i);
    }

    long long result = 0LL;
    for(int i = 0; i < N - 1; i++) {
        for(int j = i + 1; j < N; j++) {
            long long tmp = M - 1 + radius[i] + radius[j] - radius_sum;
            if(tmp < 0) {
                continue;
            }
            result = add(result, C(tmp + N, N));
        }
    }

    result = mul(result, factorial);
    return mul(result, 2);
}

int main(int argc, char *argv[]) {
    ifstream fin("beach_umbrellas.txt");

    if(fin.is_open()) {
        int T;
        fin >> T;
        for(int test_case = 0; test_case < T; test_case++) {
            long long N, M;
            fin >> N >> M;
            vector<long long> radius(N);

            for(long long i = 0; i < N; i++) {
                fin >> radius[i];
            }

            if(N == 1) {
                cout << "Case #" << test_case + 1 << ": " <<  M % MOD << '\n';
                continue;
            }

            cout << "Case #" << test_case + 1 << ": " <<  calculate(N, M, radius) << '\n';
        }
    }
    return 0;
}
