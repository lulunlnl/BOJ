#include "bits/stdc++.h"
using namespace std;
typedef long long ll;
ll dp[22][22][22];

int main() {
    dp[1][1][1] = 1;
    for (int i = 2; i <= 20; i++) {
        for (int j = 1; j <= 20; j++) {
            for (int k = 1; k <= 20; k++) {
                if (j + k > i + 1) continue;
                dp[i][j][k] = dp[i-1][j-1][k] + dp[i-1][j][k-1] + (i - 2) * dp[i-1][j][k];
            }
        }
    }
    int T; cin >> T;
    while (T--) {
        int n, l, r; cin >> n >> l >> r;
        cout << dp[n][l][r] << "\n";
    }
}