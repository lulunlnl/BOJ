#include <bits/stdc++.h>
using namespace std;
int color[205], dp[205][205];

int solve(int s, int e) {
    if (s == e) return 0;
    int &ret = dp[s][e];
    if (ret != -1) return ret;
    ret = 1e9;
    for (int i = s; i < e; i++) {
        ret = min(ret, solve(s, i) + solve(i + 1, e) + (color[s] != color[i + 1]));
    }
    return ret;
}

int main() {
    int n, k; cin >> n >> k;
    for (int i = 0; i < n; i++) cin >> color[i];
    memset(dp, -1, sizeof dp);
    cout << solve(0, n - 1);
}