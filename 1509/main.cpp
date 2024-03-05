#include "bits/stdc++.h"
using namespace std;
int dp[2505][2505], dp2[2505];

int main() {
    cin.tie(0)->sync_with_stdio(0);
    string S; cin >> S;
    int N = S.size();
    for (int d = 0; d < N; d++) {
        for (int i = 0; i < N; i++) {
            if (d == 0) {
                dp[i][i] = 1;
                continue;
            }
            if (d == 1) {
                dp[i][i+1] = (S[i] == S[i+1]);
                continue;
            }
            int j = i + d;
            if (j >= N) break;
            dp[i][j] = ((S[i] == S[j]) && dp[i+1][j-1]);
        }
    }

    for (int i = 0; i < N; i++) {
        if (dp[0][i]) {
            dp2[i] = 1;
            continue;
        }
        dp2[i] = dp2[i-1] + 1;
        for (int j = 1; j < i; j++) {
            if (dp[j][i]) dp2[i] = min(dp2[i], dp2[j-1] + 1);
        }
    }
    cout << dp2[N-1] << "\n";
}