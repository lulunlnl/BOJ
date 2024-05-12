#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
vector<int> g[250005];
int dp[250005][2], chk[250005][2];
int cnt;

void solve(int now, int par) {
    dp[now][1] = 1;
    for (auto &next: g[now]) {
        if (next == par) continue;
        solve(next, now);
        dp[now][1] += dp[next][0];
        dp[now][0] += max(dp[next][0], dp[next][1]);
    }
}

void track(int now, int par, bool x) {
    if (chk[now][x]) return;
    chk[now][x] = 1;
    if (x == 0) cnt--;
    for (auto &next: g[now]) {
        if (next == par ) continue;
        if (x || dp[next][0] >= dp[next][1]) track(next, now, 0);
        if (!x && dp[next][1] >= dp[next][0]) track(next, now, 1);
    }
}

int main() {
    int n; cin >> n;
    for (int i = 1; i < n; i++) {
        int u, v; cin >> u >> v;
        g[u].push_back(v);
        g[v].push_back(u);
    }
    cnt = n;
    solve(1, 0);
    if (dp[1][0] >= dp[1][1]) track(1, 0, 0);
    if (dp[1][0] <= dp[1][1]) track(1, 0, 1);
    ll ans = (ll)n * (n - 1) / 2 - (ll)cnt * (cnt - 1) / 2;
    cout << ans;
}