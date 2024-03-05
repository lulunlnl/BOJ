#include "bits/stdc++.h"
using namespace std;
typedef long long ll;
const ll MOD = 10007;
ll dp[1005][1005];

int main() {
    cin.tie(0)->sync_with_stdio(0);
    string S; cin >> S;
    int N = S.size();
    for (int d = 0; d < N; d++) {
        for (int i = 0; i < N; i++) {
            int j = i + d;
            if (j >= N) break;
            if (d == 0) dp[i][i] = 1;
            else if (d == 1) dp[i][i+1] = (S[i] == S[j] ? 3 : 2);
            else dp[i][j] = dp[i][j-1] + dp[i+1][j] - dp[i+1][j-1] + (S[i] == S[j] ? 1 + dp[i+1][j-1] : 0);
            while (dp[i][j] >= MOD) dp[i][j] -= MOD;
            if (dp[i][j] < 0) dp[i][j] += MOD;
        }
    }
    cout << dp[0][N-1] << "\n";
}