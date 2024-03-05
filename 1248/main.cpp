#include "bits/stdc++.h"
using namespace std;
int arr[1005][1005], dp[1005][1005];

int main() {
    cin.tie(0)->sync_with_stdio(0);
    int N, M; cin >> N >> M;
    for (int i = 0; i < N; i++) {
        string S; cin >> S;
        for (int j = 0; j < M; j++) {
            arr[i][j] = S[j] - '0';
        }
    }
    int ans = 0;
    for (int i = 0; i < N; i++) dp[i][0] = arr[i][0], ans = max(ans, dp[i][0]);
    for (int j = 0; j < M; j++) dp[0][j] = arr[0][j], ans = max(ans, dp[0][j]);
    for (int i = 1; i < N; i++) {
        for (int j = 1; j < M; j++) {
            if (arr[i][j] == 0) dp[i][j] = 0;
            else dp[i][j] = min({dp[i][j-1], dp[i-1][j], dp[i-1][j-1]}) + 1;
            ans = max(ans, dp[i][j]);
        }
    }
    cout << ans * ans << "\n";
}