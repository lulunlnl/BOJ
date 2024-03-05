#include "bits/stdc++.h"
using namespace std;
const int INF = 1e9;
int dp[105][105];

int main() {
    cin.tie(0)->sync_with_stdio(0);
    int N, M, R; cin >> N >> M >> R;
    vector<int> item(N+1);
    for (int i = 1; i <= N; i++) {
        cin >> item[i];
    }
    for (int i = 1; i <= N; i++){
        for (int j = 1; j <= N; j++) {
            dp[i][j] = (i == j) ? 0 : INF;
        }
    }
    for (int i = 0; i < R; i++) {
        int a, b, l; cin >> a >> b >> l;
        dp[a][b] = min(l, dp[a][b]);
        dp[b][a] = min(l, dp[b][a]);
    }
    for (int k = 1; k <= N; k++) {
        for (int i = 1; i <= N; i++) {
            for (int j = 1; j <= N; j++) {
                dp[i][j] = min(dp[i][j], dp[i][k] + dp[k][j]);
            }
        }
    }
    int ans = 0;
    for (int i = 1; i <= N; i++) {
        int tmp = 0;
        for (int j = 1; j <= N; j++) {
            if (dp[i][j] <= M) tmp += item[j];
        }
        ans = max(ans, tmp);
    }
    cout << ans << "\n";
}