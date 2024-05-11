#include <bits/stdc++.h>
using namespace std;
int chk[105][105], dp[105][105];

int main() {
    int N; cin >> N;
    for (int i = 0; i < N; i++) {
        int a, b; cin >> a >> b;
        chk[a][b] = 1;
        chk[b][a] = 1;
    }
    for (int i = 1; i <= 100; i++) {
        for (int j = i; j >= 1; j--) {
            for (int k = j; k < i; k++) {
                dp[j][i] = max(dp[j][i], dp[j][k] + dp[k][i] + chk[i][j]);
            }
        }
    }
    cout << dp[1][100];
}