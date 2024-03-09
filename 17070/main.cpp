#include "bits/stdc++.h"
using namespace std;
int arr[20][20], dp[20][20][3];

int main() {
    cin.tie(0)->sync_with_stdio(0);
    int N; cin >> N;
    for (int i = 1; i <= N; i++) {
        for (int j = 1; j <= N; j++) {
            cin >> arr[i][j];
        }
    }
    for (int i = 1; i <= N; i++) {
        for (int j = 1; j <= N; j++) {
            if (i == 1 && j == 2) {
                dp[i][j][0] = 1;
                continue;
            }
            if (!arr[i][j]) {
                dp[i][j][0] = dp[i][j-1][0] + dp[i][j-1][2];
                dp[i][j][1] = dp[i-1][j][1] + dp[i-1][j][2];
                if (!arr[i-1][j] && !arr[i][j-1]) dp[i][j][2] = dp[i-1][j-1][0] + dp[i-1][j-1][1] + dp[i-1][j-1][2];
            }
        }
    }
    cout << dp[N][N][0] + dp[N][N][1] + dp[N][N][2];
}