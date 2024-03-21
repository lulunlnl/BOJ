#include "bits/stdc++.h"
using namespace std;
typedef long long ll;
ll dp[10005][1 << 4];

int main() {
    dp[1][0] = dp[1][3] = dp[1][6] = dp[1][12] = dp[1][15] = 1;
    for (int i = 2; i <= 10000; i++) {
        for (int j = 0; j < 16; j++) {
            dp[i][j] += dp[i-1][15 - j];
        }
        dp[i][3] += dp[i][0];
        dp[i][7] += dp[i][4];
        dp[i][11] += dp[i][8];
        dp[i][15] += dp[i][12];

        dp[i][6] += dp[i][0];
        dp[i][7] += dp[i][1];
        dp[i][14] += dp[i][8];
        dp[i][15] += dp[i][9];

        dp[i][12] += dp[i][0];
        dp[i][13] += dp[i][1];
        dp[i][14] += dp[i][2];
        dp[i][15] += dp[i][3];
    }
    int T; cin >> T;
    while (T--) {
        int x; cin >> x;
        cout << dp[x][15] << "\n";
    }
}