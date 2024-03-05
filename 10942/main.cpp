#include "bits/stdc++.h"
using namespace std;
int dp[2005][2005];

int main() {
    cin.tie(0)->sync_with_stdio(0);
    int N; cin >> N;
    vector<int> a(N);
    for (int i = 0; i < N; i++) cin >> a[i];
    for (int d = 0; d < N; d++) {
        for (int i = 0; i < N; i++) {
            if (d == 0) {
                dp[i][i] = 1;
                continue;
            }
            if (d == 1) {
                dp[i][i+1] = (a[i] == a[i+1]);
                continue;
            }
            int j = i + d;
            if (j >= N) break;
            dp[i][j] = ((a[i] == a[j]) && dp[i+1][j-1]);
        }
    }
    int M; cin >> M;
    while (M--) {
        int s, e; cin >> s >> e;
        s--; e--;
        cout << dp[s][e] << "\n";
    }
}