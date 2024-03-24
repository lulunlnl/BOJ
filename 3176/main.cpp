#include "bits/stdc++.h"
#define ft first
#define sd second
using namespace std;
tuple<int, int, int> dp[100005][30];
int dep[100005];

int main() {
    cin.tie(0)->sync_with_stdio(0);
    int n; cin >> n;
    vector<vector<pair<int, int>>> g(n+1);
    for (int i = 1; i < n; i++) {
        int a, b, c; cin >> a >> b >> c;
        g[a].push_back({b, c});
        g[b].push_back({a, c});
    }
    auto dfs = [&](auto self, int now, int par, int d) -> void {
        dep[now] = d;
        for (auto& next: g[now]) {
            if (next.ft == par) continue;
            dp[next.ft][0] = make_tuple(now, next.sd, next.sd);
            self(self, next.ft, now, d + 1);
        }
    };
    dfs(dfs, 1, 0, 0);
    for (int j = 1; j < 30; j++) {
        for (int i = 1; i <= n; i++) {
            get<1>(dp[i][j]) = numeric_limits<int>::max();
            get<2>(dp[i][j]) = numeric_limits<int>::min();
            auto [par1, mn1, mx1] = dp[i][j-1];
            auto [par2, mn2, mx2] = dp[par1][j-1];
            dp[i][j] = make_tuple(par2, min(mn1, mn2), max(mx1, mx2));
        }
    }
    auto lca = [&](int u, int v) {
        if (dep[u] < dep[v]) swap(u, v);
        int diff = dep[u] - dep[v];
        int mn = numeric_limits<int>::max(), mx = numeric_limits<int>::min();
        for (int i = 0; diff; i++) {
            if (diff & 1) {
                auto [a, b, c] = dp[u][i];
                tie(u, mn, mx) = make_tuple(a, min(mn, b), max(mx, c));
            }
            diff >>= 1;
        }
        if (u == v) return make_tuple(u, mn, mx);
        for (int i = 29; i >= 0; i--) {
            if (get<0>(dp[u][i]) != get<0>(dp[v][i])) {
                auto [a, b, c] = dp[u][i];
                tie(u, mn, mx) = make_tuple(a, min(mn, b), max(mx, c));
                tie(a, b, c) = dp[v][i];
                tie(v, mn, mx) = make_tuple(a, min(mn, b), max(mx, c));
            }
        }
        mn = min({mn, get<1>(dp[u][0]), get<1>(dp[v][0])}), mx = max({mx, get<2>(dp[u][0]), get<2>(dp[v][0])});
        return make_tuple(get<0>(dp[u][0]), mn, mx);
    };
    int K; cin >> K;
    while (K--) {
        int a, b; cin >> a >> b;
        int par, mn, mx;
        tie(par, mn, mx) = lca(a, b);
        cout << mn << " " << mx << "\n";
    }
}