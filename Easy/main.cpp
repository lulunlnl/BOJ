#include "bits/stdc++.h"
using namespace std;
typedef long long ll;
constexpr ll MOD = 1e9+9;
ll dp[100005][4];

int main() {
    cin.tie(0)->sync_with_stdio(0);
    dp[1][1] = dp[2][2] = dp[3][3] = 1;
    dp[3][2] = dp[3][1] = 1;
    for (int i = 4; i <= 100000; i++) {
        for (int j = 1; j <= 3; j++)
            for (int k = 1; k <= 3; k++)
                if (j != k) {
                    dp[i][j] += dp[i-j][k];
                    dp[i][j] %= MOD;
                }
    }
    int T; cin >> T;
    while (T--) {
        int n; cin >> n;
        cout << dp[n][1] + dp[n][2] + dp[n][3] << "\n";
    }
}