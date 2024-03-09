#include "bits/stdc++.h"
using namespace std;
int chk[105][105], dp[105][105];

int main() {
    cin.tie(0)->sync_with_stdio(0);
    int N; cin >> N;
    for (int i = 0; i < N; i++) {
        int a, b; cin >> a >> b;
        a--; b--;
        chk[a][b] = 1;
        chk[b][a] = 1;
    }
    for (int d = 1; d <= 99; d++) {
        for (int i = 0; i < 100; i++) {
            for (int k = i; k <= i+d; k++) {
                dp[i][(i+d)%100] = max(dp[i][(i+d)%100], dp[i][k%100] + dp[k%100][(i+d)%100] + chk[i][(i+d)%100]);
            }
            dp[(i+d)%100][i] = dp[i][(i+d)%100];
        }
    }
    cout << dp[0][99];
}