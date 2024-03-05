#include "bits/stdc++.h"
using namespace std;
int cost[3][1005], dp[3][1005];

int main() {
    int N; cin >> N;
    for (int i = 0; i < N; i++) {
        for (int j = 0; j < 3; j++) cin >> cost[j][i];
    }
    int ans = 1e9;
    for (int t = 0; t < 3; t++) {
        dp[t][0] = cost[t][0];
        dp[(t+1)%3][0] = 1e9;
        dp[(t+2)%3][0] = 1e9;
        for (int i = 1; i < N; i++) {
            for (int j = 0; j < 3; j++) {
                dp[j][i] = min(dp[(j + 1) % 3][i - 1], dp[(j + 2) % 3][i - 1]) + cost[j][i];
            }
        }
        ans = min({ans, dp[(t+1)%3][N-1], dp[(t+2)%3][N-1]});
    }
    cout << ans << "\n";
}