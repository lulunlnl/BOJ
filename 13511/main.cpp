#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
vector<pair<int, ll>> g[100005];
int dep[100005], dp[100005][20];
ll dist[100005];

int lca(int u, int v) {
    if (dep[u] < dep[v]) swap(u, v);
    int diff = dep[u] - dep[v];
    for (int i = 0; diff; i++) {
        if (diff & 1) u = dp[u][i];
        diff >>= 1;
    }
    if (u == v) return u;
    for (int i = 19; i >= 0; i--) {
        if (dp[u][i] != dp[v][i]) u = dp[u][i], v = dp[v][i];
    }
    return dp[u][0];
}

int main() {
    cin.tie(0)->sync_with_stdio(0);
    int n; cin >> n;
    for (int i = 1; i < n; i++) {
        int u, v, w; cin >> u >> v >> w;
        g[u].push_back({v, w});
        g[v].push_back({u, w});
    }
    {
        auto dfs = [&](auto self, int now = 1, int par = 0, int d = 0, ll l = 0) -> void {
            dep[now] = d, dist[now] = l;
            for (auto next: g[now]) {
                if (next.first == par) continue;
                dp[next.first][0] = now;
                self(self, next.first, now, d + 1, l + next.second);
            }
        };
        dfs(dfs);
    }
    for (int j = 1; j < 20; j++) {
        for (int i = 1; i <= n; i++) {
            dp[i][j] = dp[dp[i][j - 1]][j - 1];
        }
    }

    int m; cin >> m;
    while (m--) {
        int op; cin >> op;
        if (op == 1) {
            int u, v; cin >> u >> v;
            int w = lca(u, v);
            cout << dist[u] + dist[v] - 2 * dist[w] << "\n";
        }
        else {
            int u, v, k; cin >> u >> v >> k;
            int w = lca(u, v), l = dep[u] + dep[v] - 2 * dep[w];
            k--;
            if (k > dep[u] - dep[w]) k = l - k, swap(u, v);
            for (int i = 0; k; i++) {
                if (k & 1) u = dp[u][i];
                k >>= 1;
            }
            cout << u << "\n";
        }
    }
}